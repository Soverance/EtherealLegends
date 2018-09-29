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
#include "IceKnight.h"

#define LOCTEXT_NAMESPACE "EtherealText"

AIceKnight::AIceKnight(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/EtherealParty/IceKnight/Mixamo/IceKnight.IceKnight'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/IceKnight/Mixamo/Anim_IceKnight.Anim_IceKnight_C'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> HammerMesh(TEXT("SkeletalMesh'/Game/EtherealParty/LavaKnight/Mesh/GDC2012_IceKnightHammer.GDC2012_IceKnightHammer'"));
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> EyeParticleObject(TEXT("ParticleSystem'/Game/EtherealParty/IceKnight/FX/P_FrostGiant_EyeFlare.P_FrostGiant_EyeFlare'"));
	
	// Set Default Objects
	SK_Hammer = HammerMesh.Object;
	//P_Eye1FX = EyeParticleObject.Object;
	//P_Eye2FX = EyeParticleObject.Object;
	
	// Default Config
	Name = EEnemyNames::EN_IceKnight;
	NameText = LOCTEXT("IceKnightText", "IceKnight");
	Realm = ERealms::R_Arcadia;
	BattleType = EBattleTypes::BT_Signet;
	CommonDrop = EMasterGearList::GL_RuneBow;
	UncommonDrop = EMasterGearList::GL_HuntersGloves;
	RareDrop = EMasterGearList::GL_CrimsonGauntlets;
	AttackDelay = 2.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	GetCharacterMovement()->MaxAcceleration = 30;

	MapMarkerFX->SetColorParameter(FName(TEXT("BeamColor")), FLinearColor::Yellow);

	// Pawn A.I. config
	PawnSensing->HearingThreshold = 600;
	PawnSensing->LOSHearingThreshold = 1200;
	PawnSensing->SightRadius = 1000;
	PawnSensing->SetPeripheralVisionAngle(40.0f);
	AcceptanceRadius = 250.0f;
	RunAI = false;
	BaseEyeHeight = 50;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -89));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(80);
	MeleeRadius->SetRelativeLocation(FVector(60, 0, -85));

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

	// Blade skeletal mesh
	Hammer = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Hammer"));
	Hammer->SetupAttachment(GetMesh(), FName(TEXT("RightHand")));
	Hammer->SkeletalMesh = SK_Hammer;
	Hammer->SetRelativeScale3D(FVector(2, 2, 2));
	Hammer->SetRelativeRotation(FRotator(90, 0, 0));
	Hammer->bReceivesDecals = false;

	// Glowing Eye Particle Effect
	//Eye1FX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("Eye1FX"));
	//Eye1FX->SetupAttachment(GetMesh(), FName(TEXT("LeftEye")));
	//Eye1FX->Template = P_Eye1FX;
	//Eye1FX->bAutoActivate = true;
	//Eye1FX->SetRelativeScale3D(FVector(0.15f, 0.15f, 0.15f));

	// Glowing Eye Particle Effect
	//Eye2FX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("Eye2FX"));
	//Eye2FX->SetupAttachment(GetMesh(), FName(TEXT("RightEye")));
	//Eye2FX->Template = P_Eye2FX;
	//Eye2FX->bAutoActivate = true;
	//Eye2FX->SetRelativeScale3D(FVector(0.15f, 0.15f, 0.15f));
}

// Called when the game starts or when spawned
void AIceKnight::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &AIceKnight::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &AIceKnight::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &AIceKnight::CustomDeath); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &AIceKnight::AttackRound);  // bind the attack function to the OnReachedTarget event 
}

// Called every frame
void AIceKnight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Melee Attack function
void AIceKnight::AttackRound()
{
	if (!Target->IsDead)
	{
		if (!IsAttacking)
		{
			DoFrostHammer = false;
			DoIceBlast = false;
			DoFrostSpike = false;

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
							DoFrostHammer = true;
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
						DoIceBlast = true;
					}
					if (RandomAtk > 3)
					{
						DoFrostSpike = true;
					}
				}
			}

			// Restart the Attack Cycle after a short delay
			FTimerHandle EndTimer;
			GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
		}
	}
}

void AIceKnight::CustomDeath()
{
	IsDead = true;	
}

// A.I. Hearing
void AIceKnight::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
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
void AIceKnight::OnSeePawn(APawn* Pawn)
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
