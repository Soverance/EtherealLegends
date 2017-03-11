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
#include "Daemon.h"

#define LOCTEXT_NAMESPACE "EtherealText"

ADaemon::ADaemon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/EtherealParty/Daemon/Daemon.Daemon'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/Daemon/Anim_Daemon.Anim_Daemon_C'"));

	// Set Default Objects
	
	// Default Config
	Name = EEnemyNames::EN_Daemon;
	NameText = LOCTEXT("DaemonText", "Daemon");
	Realm = ERealms::R_Arcadia;
	BattleType = EBattleTypes::BT_Signet;
	CommonDrop = EMasterGearList::GL_Potion;
	UncommonDrop = EMasterGearList::GL_Potion;
	RareDrop = EMasterGearList::GL_Potion;
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
	AcceptanceRadius = 55.0f;
	RunAI = false;
	BaseEyeHeight = 0;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(25);
	MeleeRadius->SetRelativeLocation(FVector(15, 0, -85));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 250));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	
	HitFX->SetRelativeLocation(FVector(0, 0, -50));
	DeathFX->SetRelativeLocation(FVector(0, 0, -88));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));	
	DisappearFX->SetRelativeLocation(FVector(0, 0, -60));
	DisappearFX->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));

	// Enemy-Specific Object Config

	
}

// Called when the game starts or when spawned
void ADaemon::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &ADaemon::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &ADaemon::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &ADaemon::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &ADaemon::AttackRound);  // bind the attack function to the OnReachedTarget event 
}

// Called every frame
void ADaemon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Melee Attack function
void ADaemon::AttackRound()
{
	// Reset all attack anims when starting a new round...
	DoAtk1 = false;
	DoAtk2 = false;
	DoAtk3 = false;
	DoJump = false;

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
						int32 RandomAtk = FMath::RandRange(0, 8);  // get a random int

						if (!IsDead)
						{
							if (RandomAtk <= 2)
							{
								DoAtk1 = true;
							}
							if (RandomAtk > 2 && RandomAtk <= 5)
							{
								DoAtk2 = true;
							}
							if (RandomAtk > 5)
							{
								DoAtk3 = true;
							}
						}
					}
				}
			}

			if (Overlapping.Num() == 0)
			{
				if (!IsDead)
				{
					EnemyDealDamage(15);
					DoJump = true;
				}
			}

			// Restart the Attack Cycle after a short delay
			FTimerHandle EndTimer;
			GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
		}
	}
}

void ADaemon::Death()
{
	IsDead = true;	
}

// A.I. Hearing
void ADaemon::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
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
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 3.5f, false);
		}
	}
}

// A.I. Sight
void ADaemon::OnSeePawn(APawn* Pawn)
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
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 3.5f, false);
		}
	}
}

#undef LOCTEXT_NAMESPACE
