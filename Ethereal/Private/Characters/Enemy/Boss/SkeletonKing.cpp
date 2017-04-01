// Â© 2014 - 2017 Soverance Studios
// http://www.soverance.com

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Ethereal.h"
#include "Widgets/Tutorial.h"
#include "SkeletonKing.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
ASkeletonKing::ASkeletonKing(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/SkeletonSorcerer/Character/SM_SkeletonSorcerer.SM_SkeletonSorcerer'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/SkeletonSorcerer/Character/SkeletonKing_AnimBP.SkeletonKing_AnimBP_C'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObject(TEXT("StaticMesh'/Game/SkeletonSorcerer/Meshes/SM_SorcererStaff.SM_SorcererStaff'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DeathAudioObject(TEXT("SoundCue'/Game/Audio/Party/SoulEater_Death_Cue.SoulEater_Death_Cue'"));

	S_DeathAudio = DeathAudioObject.Object;
	SM_WeaponStaticMesh = StaticMeshObject.Object;

	// Default Config
	Name = EEnemyNames::EN_SkeletonKing;
	NameText = LOCTEXT("SkeletonKingText", "Skeleton King");
	Realm = ERealms::R_Arcadia;
	BattleType = EBattleTypes::BT_Boss;
	CommonDrop = EMasterGearList::GL_Elixer;
	UncommonDrop = EMasterGearList::GL_Blizzard;
	RareDrop = EMasterGearList::GL_Barrier;
	AttackDelay = 3.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	GetCharacterMovement()->MaxAcceleration = 30;
	GetCharacterMovement()->RotationRate = FRotator(0, 5, 0);  // seems to do nothing?

	MapMarkerFX->SetColorParameter(FName(TEXT("BeamColor")), FLinearColor::Yellow);

	// Pawn A.I. config
	PawnSensing->HearingThreshold = 400;
	PawnSensing->LOSHearingThreshold = 500;
	PawnSensing->SightRadius = 500;
	PawnSensing->SetPeripheralVisionAngle(40.0f);
	AcceptanceRadius = 250.0f;
	RunAI = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(1, 1, 1));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	WeaponStaticMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Weapon Static Mesh"));
	WeaponStaticMesh->SetStaticMesh(SM_WeaponStaticMesh);
	UCommonLibrary::SetupSMComponentsWithCollision(WeaponStaticMesh);
	WeaponStaticMesh->SetupAttachment(GetMesh(), FName(TEXT("WeaponRight_Socket")));
	WeaponStaticMesh->SetRelativeScale3D(FVector(1, 1, 1));
	WeaponStaticMesh->SetRelativeLocation(FVector(0, 0, 0));
	WeaponStaticMesh->SetRelativeRotation(FRotator(0, 0, 0));

	// Melee Radius Config
	MeleeRadius->SetSphereRadius(120);
	MeleeRadius->SetRelativeLocation(FVector(80, 0, 0));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 215));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	// Death FX Config
	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));

	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Enemy-Specific Object Config
	DeathAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DeathAudio"));
	DeathAudio->Sound = S_DeathAudio;
	DeathAudio->bAutoActivate = false;
	DeathAudio->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASkeletonKing::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &ASkeletonKing::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &ASkeletonKing::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &ASkeletonKing::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &ASkeletonKing::AttackCycle);  // bind the attack function to the OnReachedTarget event

	// Get the Gatekeeper actor, so this enemy has a reference to it for tutorial progression
	for (TActorIterator<AGatekeeper> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Gatekeeper = *ActorItr; // get the instance of the Gatekeeper actor
	}
}

// Called every frame
void ASkeletonKing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASkeletonKing::AttackCycle()
{
	if (!Target->IsDead)
	{
		if (!IsAttacking)
		{
			IsAttacking = true;

			TArray<AActor*> Overlapping;  // define a local array to store hits
			MeleeRadius->GetOverlappingActors(Overlapping, AEtherealPlayerMaster::StaticClass()); // check for overlapping players within the stomp radius

			if (Overlapping.Num() > 0)
			{
				for (AActor* Actor : Overlapping) // for each actor found overlapping
				{
					AEtherealPlayerMaster* Player = Cast<AEtherealPlayerMaster>(Actor);  // cast to Player Master

					if (Player) // if succeeded
					{
						Target = Player;
						EnemyDealDamage(15);
						Attack = true;  // if the player is inside the melee radius, do the melee bite attack
					}
				}
			}

			if (Overlapping.Num() == 0)
			{
				EnemyDealDamage(15);
				int32 RandomAtk = FMath::RandRange(0, 5);  // get a random int

				// To make this guy harder, he'll use the Firestorm attack on rare occasions
				if (!IsDead)
				{
					if (RandomAtk <= 4)
					{
						CastFireball();
					}
					if (RandomAtk > 4)
					{
						CastFirestorm();  // Cast Firestorm
					}
				}
			}

			// Restart the Attack Cycle after a short delay
			FTimerHandle EndTimer;
			GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
		}
	}
}

void ASkeletonKing::Death()
{
	DeathAudio->Play();  // Play death audio
	

	if (!Target->EtherealPlayerState->HasCompletedTutorial)  // don't bother running this code if the player has already completed the tutorial
	{
		if (Gatekeeper)  // be sure Gatekeeper reference isn't NULL
		{
			if (Gatekeeper->Tutorial)  // be sure the Tutorial widget isn't NULL
			{
				Gatekeeper->Tutorial->TutorialIndex = 3;  // when this enemy dies, force tutorial index to 3.  We don't care if you somehow skipped the other tutorial screens.

				if (Gatekeeper->Tutorial->TutorialIndex == 3)  // you killed this enemy while on the proper TutorialIndex, so we progress the Tutorial
				{
					FTimerHandle ConvoTimer;
					GetWorldTimerManager().SetTimer(ConvoTimer, this, &ASkeletonKing::ShowTutorialConvo, 2.5f, false);
				}
			}			
		}
	}
	
}

void ASkeletonKing::ShowTutorialConvo()
{
	Gatekeeper->Tutorial->ShowConversation_06();  // show the Casting Magic tutorial panel
}

void ASkeletonKing::CastFirestorm()
{
	Firestorm = true;
}

void ASkeletonKing::CastFireball()
{
	Fireball = true;
}

void ASkeletonKing::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			//Aggro(PawnInstigator);

			IsAggroed = true;

			// Delay Aggro so the skeleton can get up from the ground
			FTimerDelegate DelegateAggro;
			DelegateAggro.BindUFunction(this, FName("Aggro"), PawnInstigator);
			FTimerHandle AggroTimer;
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 2.5f, false);
		}
	}
}

void ASkeletonKing::OnSeePawn(APawn* Pawn)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			//Aggro(Pawn);

			IsAggroed = true;

			// Delay Aggro so the skeleton can get up from the ground
			FTimerDelegate DelegateAggro;
			DelegateAggro.BindUFunction(this, FName("Aggro"), Pawn);
			FTimerHandle AggroTimer;
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 2.5f, false);
		}
	}
}

#undef LOCTEXT_NAMESPACE
