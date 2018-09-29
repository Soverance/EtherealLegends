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
#include "SkyDragon.h"

#define LOCTEXT_NAMESPACE "EtherealText"

ASkyDragon::ASkyDragon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/DragonBeast/Character/SK_SkyDragon.SK_SkyDragon'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/DragonBeast/Character/Anim_SkyDragon.Anim_SkyDragon_C'"));

	// Set Default Objects
	
	// Default Config
	Name = EEnemyNames::EN_SkyDragon;
	NameText = LOCTEXT("SkyDragonText", "Sky Dragon");
	Realm = ERealms::R_Arcadia;
	BattleType = EBattleTypes::BT_Signet;
	CommonDrop = EMasterGearList::GL_DragonShield;
	UncommonDrop = EMasterGearList::GL_HuntersCoat;
	RareDrop = EMasterGearList::GL_CrimsonBreastplate;
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
	AcceptanceRadius = 150.0f;
	RunAI = false;
	BaseEyeHeight = -100;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(30);
	MeleeRadius->SetRelativeLocation(FVector(25, 0, -85));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 300));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));
	
	HitFX->SetRelativeLocation(FVector(0, 0, -50));
	DeathFX->SetRelativeLocation(FVector(0, 0, -88));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));	
	DisappearFX->SetRelativeLocation(FVector(0, 0, -60));
	DisappearFX->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));

	// Enemy-Specific Object Config

	// Twirl Box
	TwirlBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("TwirlBox"));
	TwirlBox->SetupAttachment(RootComponent);
	TwirlBox->SetRelativeLocation(FVector(75, 0, 0));
	TwirlBox->SetBoxExtent(FVector(60, 50, 100));
}

// Called when the game starts or when spawned
void ASkyDragon::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &ASkyDragon::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &ASkyDragon::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &ASkyDragon::CustomDeath); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &ASkyDragon::AttackRound);  // bind the attack function to the OnReachedTarget event 
}

// Called every frame
void ASkyDragon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Melee Attack function
void ASkyDragon::AttackRound()
{
	if (!Target->IsDead)
	{
		if (!IsAttacking)
		{
			// Reset all anims
			DoRightPaw = false;
			DoLeftPaw = false;
			DoBite = false;
			DoFlamethrower = false;
			DoCombo = false;

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
							int32 RandomAtk = FMath::RandRange(0, 8);  // get a random int

							if (RandomAtk <= 2)
							{
								DoRightPaw = true;
							}
							if (RandomAtk > 2 && RandomAtk <= 5)
							{
								DoLeftPaw = true;
							}
							if (RandomAtk > 5)
							{
								DoBite = true;
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
					int32 RandomAtk = FMath::RandRange(0, 5);  // get a random int

					if (RandomAtk <= 3)
					{
						DoFlamethrower= true;
					}
					if (RandomAtk > 3)
					{
						DoCombo = true;
					}
				}
			}

			// Restart the Attack Cycle after a short delay
			FTimerHandle EndTimer;
			GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
		}
	}
}

void ASkyDragon::TwirlHitCheck(bool DoConfuse, bool DoBurn)
{
	DoRightPaw = false;
	DoLeftPaw = false;
	DoBite = false;
	DoFlamethrower = false;
	DoCombo = false;

	TArray<AActor*> Overlapping;  // define a local array to store hits
	TwirlBox->GetOverlappingActors(Overlapping, AEtherealPlayerMaster::StaticClass()); // check for overlapping players within the blast radius

	for (AActor* Actor : Overlapping) // for each actor found overlapping
	{
		AEtherealPlayerMaster* Player = Cast<AEtherealPlayerMaster>(Actor);  // cast to Player Master

		if (Player) // if succeeded
		{
			Player->PlayerTakeDamage(DamageOutput);  // have the player take damage
			if (DoConfuse)
			{
				Player->EtherealPlayerController->ActivateStatus_Confuse();  // CONFUSE STATUS
			}
			if (DoBurn)
			{
				Player->EtherealPlayerController->ActivateStatus_Burn();  // BURN STATUS
			}			
		}
	}
}

void ASkyDragon::CustomDeath()
{
	IsDead = true;	
}

// A.I. Hearing
void ASkyDragon::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
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
void ASkyDragon::OnSeePawn(APawn* Pawn)
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
