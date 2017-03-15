// © 2014 - 2016 Soverance Studios
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
#include "NPCs/Objects/ReturnPortal.h"
#include "Eternal.h"
#include "ProtoZhan.h"

#define LOCTEXT_NAMESPACE "EtherealText"

AProtoZhan::AProtoZhan(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/EtherealParty/ProtoZhan/ProtoZhan.ProtoZhan'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/ProtoZhan/Anim_ProtoZhan.Anim_ProtoZhan_C'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> LaughterAudioObject(TEXT("SoundCue'/Game/EtherealParty/Genie/Audio/Eternal_Laugh_Cue.Eternal_Laugh_Cue'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BladeMesh(TEXT("StaticMesh'/Game/EtherealParty/ProtoZhan/ProtoZhan_Sword.ProtoZhan_Sword'"));
	
	// Set Default Objects
	S_LaughterAudio = LaughterAudioObject.Object;
	SK_Blade = BladeMesh.Object;

	/////////////////////////////////////
	// DEFAULTS

	Name = EEnemyNames::EN_ProtoZhan;
	NameText = LOCTEXT("ProtoZhanText", "Proto Zhan");
	Realm = ERealms::R_Arcadia;
	BattleType = EBattleTypes::BT_Signet;
	CommonDrop = EMasterGearList::GL_Potion;
	UncommonDrop = EMasterGearList::GL_Potion;
	RareDrop = EMasterGearList::GL_Potion;
	AttackDelay = 1.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	GetCharacterMovement()->MaxAcceleration = 30;	

	// A.I. Config
	PawnSensing->HearingThreshold = 300;
	PawnSensing->LOSHearingThreshold = 400;
	PawnSensing->SightRadius = 1000;
	PawnSensing->SetPeripheralVisionAngle(50.0f);
	AcceptanceRadius = 50.0f;
	RunAI = false;

	MapMarkerFX->SetColorParameter(FName(TEXT("BeamColor")), FLinearColor::Yellow);
	
	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(3, 3, 3));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// Melee Radius Config
	MeleeRadius->SetSphereRadius(175);
	MeleeRadius->SetRelativeLocation(FVector(90, 0, -90));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 100));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, -180));
	TargetingReticle->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));

	// Hit & Death Effect Config
	HitFX->SetRelativeLocation(FVector(40, 0, 10));
	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(1, 1, 1));
	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Laughter attack audio
	LaughterAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("LaughterAudio"));
	LaughterAudio->SetupAttachment(RootComponent);
	LaughterAudio->Sound = S_LaughterAudio;
	LaughterAudio->bAutoActivate = false;

	// Blade skeletal mesh
	Blade = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Blade"));
	Blade->SetupAttachment(GetMesh(), FName(TEXT("SwordSocket")));
	Blade->SetStaticMesh(SK_Blade);
	Blade->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

// Called when the game starts or when spawned
void AProtoZhan::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &AProtoZhan::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &AProtoZhan::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &AProtoZhan::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &AProtoZhan::AttackCycle);  // bind the attack function to the OnReachedTarget event

	// We collected this reference in the EnemyMaster class
	if (EtherealGameInstance)
	{
		// Set all Volume Controls
		EtherealGameInstance->SetAudioVolume(LaughterAudio, EAudioTypes::AT_SoundEffect);
	}
}

// Called every frame
void AProtoZhan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProtoZhan::Death()
{
	IsDead = true;
}

// Melee Attack function
void AProtoZhan::AttackCycle()
{
	if (!Target->IsDead)
	{
		if (!IsAttacking)
		{
			// Reset all anims
			DoAtk1 = false;
			DoAtk2 = false;
			DoAtk3 = false;
			DoAtk4 = false;
			DoBurst = false;

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

						if (!IsDead)
						{
							EnemyDealDamage(20);
							int32 RandomAtk = FMath::RandRange(0, 10);  // get a random int

							// proto zhan basically does variations of basic attacks, unless he casts Burst.  
							// Burst is pretty heavy damage
							switch (RandomAtk)
							{
								case 0:
								case 1:
									DoAtk1 = true;
									break;
								case 2:
								case 3:
									DoAtk2 = true;
									break;
								case 4:
								case 5:
									DoAtk3 = true;
									break;
								case 6:
								case 7:
									DoAtk4 = false;
									break;
								case 8:
								case 9:
								case 10:
									EnemyDealDamage(30);
									DoBurst = false;
									break;
							}
						}
					}
				}
			}

			if (Overlapping.Num() == 0)
			{
				if (!IsDead)
				{
					EnemyDealDamage(30);
					DoBurst = true;
				}
			}

			// Restart the Attack Cycle after a short delay
			FTimerHandle EndTimer;
			GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
		}
	}
}

void AProtoZhan::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			//AudioManager->Play_BattleMusic(EBattleTypes::BT_Boss);  // play the boss battle music
			//EtherealGameInstance->BlackBox->HasEngagedBoss = true;  // Engage Boss
			// Delay Aggro so this guy can finish his aggro animation
			FTimerDelegate DelegateAggro;
			DelegateAggro.BindUFunction(this, FName("Aggro"), PawnInstigator);
			FTimerHandle AggroTimer;
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 1.5f, false);
		}
	}
}

void AProtoZhan::OnSeePawn(APawn* Pawn)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			//AudioManager->Play_BattleMusic(EBattleTypes::BT_Boss);  // play the boss battle music
			//EtherealGameInstance->BlackBox->HasEngagedBoss = true;  // Engage Boss
			// Delay Aggro so this guy can finish his aggro animation
			FTimerDelegate DelegateAggro;
			DelegateAggro.BindUFunction(this, FName("Aggro"), Pawn);
			FTimerHandle AggroTimer;
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 1.5f, false);
		}
	}
}

#undef LOCTEXT_NAMESPACE
