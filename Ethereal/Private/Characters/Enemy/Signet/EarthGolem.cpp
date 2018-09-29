// © 2014 - 2017 Soverance Studios
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
#include "EarthGolem.h"

#define LOCTEXT_NAMESPACE "EtherealText"

AEarthGolem::AEarthGolem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/EtherealParty/EarthGolem/EarthGolem.EarthGolem'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/EarthGolem/Anim_EarthGolem.Anim_EarthGolem_C'"));

	// Set Default Objects
	
	// Default Config
	Name = EEnemyNames::EN_EarthGolem;
	NameText = LOCTEXT("EarthGolemText", "Earth Golem");
	Realm = ERealms::R_Arcadia;
	BattleType = EBattleTypes::BT_Signet;
	CommonDrop = EMasterGearList::GL_DefendingRing;
	UncommonDrop = EMasterGearList::GL_HuntersHood;
	RareDrop = EMasterGearList::GL_CrimsonHelm;
	AttackDelay = 2.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	GetCharacterMovement()->MaxAcceleration = 30;

	MapMarkerFX->SetColorParameter(FName(TEXT("BeamColor")), FLinearColor::Yellow);

	// Pawn A.I. config
	PawnSensing->HearingThreshold = 600;
	PawnSensing->LOSHearingThreshold = 1200;
	PawnSensing->SightRadius = 1000;
	PawnSensing->SetPeripheralVisionAngle(40.0f);
	AcceptanceRadius = 200.0f;
	RunAI = false;
	BaseEyeHeight = 0;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -125));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(60);
	MeleeRadius->SetRelativeLocation(FVector(25, 0, -85));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 85));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	
	HitFX->SetRelativeLocation(FVector(0, 0, -50));
	DeathFX->SetRelativeLocation(FVector(0, 0, -88));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));	
	DisappearFX->SetRelativeLocation(FVector(0, 0, -60));
	DisappearFX->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));

	// Enemy-Specific Object Config

	// Twirl Box
	TwirlBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("TwirlBox"));
	TwirlBox->SetupAttachment(RootComponent);
	TwirlBox->SetRelativeLocation(FVector(100, 0, 0));
	TwirlBox->SetBoxExtent(FVector(120, 50, 150));
}

// Called when the game starts or when spawned
void AEarthGolem::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &AEarthGolem::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &AEarthGolem::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &AEarthGolem::CustomDeath); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &AEarthGolem::AttackRound);  // bind the attack function to the OnReachedTarget event 
}

// Called every frame
void AEarthGolem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Melee Attack function
void AEarthGolem::AttackRound()
{
	if (!Target->IsDead)
	{
		if (!IsAttacking)
		{
			DoSwing = false;
			DoTwirl = false;
			DoPunch = false;

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
							EnemyDealDamage(15);
							DoSwing = true;
						}
					}
				}
			}

			if (Overlapping.Num() == 0)
			{
				EnemyDealDamage(15);
				int32 RandomAtk = FMath::RandRange(0, 5);  // get a random int

				if (!IsDead)
				{
					if (RandomAtk <= 3)
					{
						DoTwirl = true;
					}
					if (RandomAtk > 3)
					{
						DoPunch = true;
					}
				}
			}

			// Restart the Attack Cycle after a short delay
			FTimerHandle EndTimer;
			GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
		}
	}
}

void AEarthGolem::TwirlHitCheck()
{
	DoSwing = false;
	DoTwirl = false;
	DoPunch = false;

	TArray<AActor*> Overlapping;  // define a local array to store hits
	TwirlBox->GetOverlappingActors(Overlapping, AEtherealPlayerMaster::StaticClass()); // check for overlapping players within the blast radius

	for (AActor* Actor : Overlapping) // for each actor found overlapping
	{
		AEtherealPlayerMaster* Player = Cast<AEtherealPlayerMaster>(Actor);  // cast to Player Master

		if (Player) // if succeeded
		{
			Player->PlayerTakeDamage(DamageOutput);  // have the player take damage
			Player->EtherealPlayerController->ActivateStatus_Confuse();  // CONFUSE STATUS
		}
	}
}

void AEarthGolem::CustomDeath()
{
	IsDead = true;	
}

// A.I. Hearing
void AEarthGolem::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
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

// A.I. Sight
void AEarthGolem::OnSeePawn(APawn* Pawn)
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
