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
#include "GaiaTitan.h"

#define LOCTEXT_NAMESPACE "EtherealText"

AGaiaTitan::AGaiaTitan(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/EarthTitan/Meshes/EARTH_TITAN.EARTH_TITAN'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EarthTitan/Meshes/EarthTitan_AnimBP.EarthTitan_AnimBP_C'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> AggroAudioObject(TEXT("SoundCue'/Game/Audio/Party/FrostGiant_Aggro_Cue.FrostGiant_Aggro_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> HitAudioObject(TEXT("SoundCue'/Game/Audio/Party/FrostGiant_Aggro_Cue.FrostGiant_Aggro_Cue'"));

	// Set Default Objects
	
	// Default Config
	Name = EEnemyNames::EN_GaiaTitan;
	NameText = LOCTEXT("GaiaTitanText", "Gaia Titan");
	Realm = ERealms::R_Yggdrasil;
	BattleType = EBattleTypes::BT_Boss;
	CommonDrop = EMasterGearList::GL_EarthSignet;
	UncommonDrop = EMasterGearList::GL_EurytosBow;
	RareDrop = EMasterGearList::GL_Temperance;
	AttackDelay = 4.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	GetCharacterMovement()->MaxAcceleration = 30;

	MapMarkerFX->SetColorParameter(FName(TEXT("BeamColor")), FLinearColor::Yellow);

	// Pawn A.I. config
	PawnSensing->HearingThreshold = 1200;
	PawnSensing->LOSHearingThreshold = 1500;
	PawnSensing->SightRadius = 1200;
	PawnSensing->SetPeripheralVisionAngle(50.0f);
	AcceptanceRadius = 150.0f;
	RunAI = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// Melee Radius Config
	MeleeRadius->SetSphereRadius(50);
	MeleeRadius->SetRelativeLocation(FVector(50, 0, -80));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 1200));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

	// Death FX Config
	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));

	HitFX->SetRelativeLocation(FVector(0, 0, 30));

	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	SpotLight = ObjectInitializer.CreateDefaultSubobject<USpotLightComponent>(this, TEXT("SpotLight"));
	SpotLight->SetupAttachment(GetMesh());
	SpotLight->SetRelativeLocation(FVector(0, 0, 2000));
	SpotLight->SetRelativeRotation(FRotator(-90, 0, 0));
	SpotLight->Intensity = 150000;
	SpotLight->LightColor = FColorList::ForestGreen;
}

// Called when the game starts or when spawned
void AGaiaTitan::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &AGaiaTitan::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &AGaiaTitan::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &AGaiaTitan::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &AGaiaTitan::AttackRound);  // bind the attack function to the OnReachedTarget event 
}

// Called every frame
void AGaiaTitan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Melee Attack function
void AGaiaTitan::AttackRound()
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
						int32 RandomAtk = FMath::RandRange(0, 5);  // get a random int

						// To make this guy harder, he'll use the Stomp attack on rare occasions
						if (!IsDead)
						{
							if (RandomAtk <= 2)
							{
								DoOneHit = true;
							}
							if (RandomAtk > 2 && RandomAtk < 4)
							{
								DoTwoHit = true;
							}
							if (RandomAtk > 4)
							{
								DoThreeHit = true;
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
					DoSmash = true;
				}
			}

			// Restart the Attack Cycle after a short delay
			FTimerHandle EndTimer;
			GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
		}
	}
}

void AGaiaTitan::Death()
{
	IsDead = true;
}

// A.I. Hearing
void AGaiaTitan::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			IsAggroed = true;
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
void AGaiaTitan::OnSeePawn(APawn* Pawn)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			IsAggroed = true;
			AudioManager->Play_BattleMusic(EBattleTypes::BT_Boss);  // play the boss battle music
			EtherealGameInstance->BlackBox->HasEngagedBoss = true;  // Engage Boss
			// Delay Aggro so this guy can finish his aggro animation
			FTimerDelegate DelegateAggro;
			DelegateAggro.BindUFunction(this, FName("Aggro"), Pawn);
			FTimerHandle AggroTimer;
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 7.5f, false);
		}
	}
}

#undef LOCTEXT_NAMESPACE
