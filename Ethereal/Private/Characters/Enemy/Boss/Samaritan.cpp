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
#include "Samaritan.h"

#define LOCTEXT_NAMESPACE "EtherealText"

ASamaritan::ASamaritan(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/Character/Samaritan_bot/SkeletalMesh/SK_Samaritan_Bot_GDC.SK_Samaritan_Bot_GDC'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/Character/Samaritan_bot/SkeletalMesh/Anim_Samaritan.Anim_Samaritan_C'"));

	// Set Default Objects
	
	// Default Config
	Name = EEnemyNames::EN_Samaritan;
	NameText = LOCTEXT("SamaritanText", "Samaritan");
	Realm = ERealms::R_Empyrean;
	BattleType = EBattleTypes::BT_Boss;
	CommonDrop = EMasterGearList::GL_SkySignet;
	UncommonDrop = EMasterGearList::GL_ExoPlate;
	RareDrop = EMasterGearList::GL_Annihilator;
	AttackDelay = 2.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	GetCharacterMovement()->MaxAcceleration = 30;

	MapMarkerFX->SetColorParameter(FName(TEXT("BeamColor")), FLinearColor::Yellow);

	// Pawn A.I. config
	PawnSensing->HearingThreshold = 600;
	PawnSensing->LOSHearingThreshold = 1200;
	PawnSensing->SightRadius = 1000;
	PawnSensing->SetPeripheralVisionAngle(40.0f);
	AcceptanceRadius = 300.0f;
	RunAI = false;
	BaseEyeHeight = -100;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(60);
	MeleeRadius->SetRelativeLocation(FVector(25, 0, -85));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 750));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
	
	HitFX->SetRelativeLocation(FVector(0, 0, -50));
	DeathFX->SetRelativeLocation(FVector(0, 0, -88));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));	
	DisappearFX->SetRelativeLocation(FVector(0, 0, -60));
	DisappearFX->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));

	// Enemy-Specific Object Config
}

// Called when the game starts or when spawned
void ASamaritan::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &ASamaritan::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &ASamaritan::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &ASamaritan::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &ASamaritan::AttackRound);  // bind the attack function to the OnReachedTarget event 
}

// Called every frame
void ASamaritan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Melee Attack function
void ASamaritan::AttackRound()
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

						if (!IsDead)
						{
							EnemyDealDamage(15);
							DoCharge = true;
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
						DoFireCannons = true;
					}
					if (RandomAtk > 3)
					{
						DoLaserBlast = true;
					}
				}
			}

			// Restart the Attack Cycle after a short delay
			FTimerHandle EndTimer;
			GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
		}
	}
}

void ASamaritan::Death()
{
	IsDead = true;

	// SIGNET RING
	//EMasterGearList SignetRing = EMasterGearList::GL_SkySignet;  // Players get the Signet Ring at a 100% drop rate
	//Target->EtherealPlayerState->EnemyKillReward(0, SignetRing, SignetRing, SignetRing);  // reward the player with the appropriate signet ring, but give no EXP
}

// A.I. Hearing
void ASamaritan::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			AudioManager->Play_BattleMusic(EBattleTypes::BT_Boss);  // play the boss battle music
			EtherealGameInstance->BlackBox->HasEngagedBoss = true;  // Engage Boss
			// Delay Aggro so this guy can finish his aggro animation
			FTimerDelegate DelegateAggro;
			DelegateAggro.BindUFunction(this, FName("Aggro"), PawnInstigator);
			FTimerHandle AggroTimer;
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 7.5f, false);
		}
	}
}

// A.I. Sight
void ASamaritan::OnSeePawn(APawn* Pawn)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			AudioManager->Play_BattleMusic(EBattleTypes::BT_Boss);  // play the boss battle music
			EtherealGameInstance->BlackBox->HasEngagedBoss = true;  // Engage Boss
			// Delay Aggro so this guy can finish his aggro animation
			FTimerDelegate DelegateAggro;
			DelegateAggro.BindUFunction(this, FName("Aggro"), Pawn);
			FTimerHandle AggroTimer;
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 3.5f, false);
		}
	}
}

#undef LOCTEXT_NAMESPACE
