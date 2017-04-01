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
#include "Golem.h"

#define LOCTEXT_NAMESPACE "EtherealText"

AGolem::AGolem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/InfinityBladeAdversaries/Enemy/Enemy_Golem/SK_Fire_Golem.SK_Fire_Golem'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/InfinityBladeAdversaries/Enemy/Enemy_Golem/Anim_Golem.Anim_Golem_C'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> AggroAudioObject(TEXT("SoundCue'/Game/Audio/Robot/Robot_Right_Arm_Cue.Robot_Right_Arm_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> StompAudioObject(TEXT("SoundCue'/Game/Audio/Robot/Robot_Gunfire_Cue.Robot_Gunfire_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> MeleeAudioObject(TEXT("SoundCue'/Game/Audio/Robot/Robot_Left_Arm_Cue.Robot_Left_Arm_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DeathAudioObject(TEXT("SoundCue'/Game/Audio/Robot/Robot_Final_Scream_Cue.Robot_Final_Scream_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> HitAudioObject(TEXT("SoundCue'/Game/Sounds/CarPhysics/Mono/ImpactObstacle_Generic_Cue.ImpactObstacle_Generic_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> LightningAudioObject(TEXT("SoundCue'/Game/Sounds/CarPhysics/Mono/ImpactObstacle_Generic_Cue.ImpactObstacle_Generic_Cue'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> LightningParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Gruntling/Lightning/P_Golem_Lightning.P_Golem_Lightning'"));

	// Set Default Objects
	S_AggroAudio = AggroAudioObject.Object;
	S_StompAudio = StompAudioObject.Object;
	S_MeleeAudio = MeleeAudioObject.Object;
	S_DeathAudio = DeathAudioObject.Object;
	S_HitAudio = HitAudioObject.Object;
	S_LightningAudio = LightningAudioObject.Object;
	P_LightningFX = LightningParticleObject.Object;
	
	// Default Config
	Name = EEnemyNames::EN_Golem;
	NameText = LOCTEXT("GolemText", "Golem");
	Realm = ERealms::R_Empyrean;
	BattleType = EBattleTypes::BT_Standard;
	CommonDrop = EMasterGearList::GL_Potion;
	UncommonDrop = EMasterGearList::GL_HiEther;
	RareDrop = EMasterGearList::GL_ExoBreeches;
	AttackDelay = 3.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));
	GetCharacterMovement()->MaxAcceleration = 30;

	// Pawn A.I. config
	PawnSensing->HearingThreshold = 150;
	PawnSensing->LOSHearingThreshold = 200;
	PawnSensing->SightRadius = 250;
	PawnSensing->SetPeripheralVisionAngle(40.0f);
	AcceptanceRadius = 45.0f;
	RunAI = false;

	DoHide = false;
	DoMelee1 = false;
	DoMelee2 = false;
	DoStomp = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(1, 1, 1));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(100);
	MeleeRadius->SetRelativeLocation(FVector(50, 0, -75));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 190));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	
	// Death FX Config
	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
	
	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Enemy-Specific Object Config

	// Aggro audio
	AggroAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("AggroAudio"));
	AggroAudio->SetupAttachment(RootComponent);
	AggroAudio->Sound = S_AggroAudio;
	AggroAudio->bAutoActivate = false;
	
	// Stomp Attack audio
	StompAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("StompAudio"));
	StompAudio->SetupAttachment(RootComponent);
	StompAudio->Sound = S_StompAudio;
	StompAudio->bAutoActivate = false;

	// Melee audio
	MeleeAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("MeleeAudio"));
	MeleeAudio->SetupAttachment(RootComponent);
	MeleeAudio->Sound = S_MeleeAudio;
	MeleeAudio->bAutoActivate = false;

	// Death audio
	DeathAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DeathAudio"));
	DeathAudio->SetupAttachment(RootComponent);
	DeathAudio->Sound = S_DeathAudio;
	DeathAudio->bAutoActivate = false;

	// Hit audio
	HitAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("HitAudio"));
	HitAudio->SetupAttachment(RootComponent);
	HitAudio->Sound = S_HitAudio;
	HitAudio->bAutoActivate = false;

	// Lightning audio
	LightningAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("LightningAudio"));
	LightningAudio->SetupAttachment(RootComponent);
	LightningAudio->Sound = S_LightningAudio;
	LightningAudio->bAutoActivate = false;

	// Lightning Effect (for stomp attack)
	LightningFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("LightningFX"));
	LightningFX->SetupAttachment(RootComponent);
	LightningFX->Template = P_LightningFX;
	LightningFX->bAutoActivate = false;
	LightningFX->SetRelativeLocation(FVector(60, 0, 0));
	LightningFX->SetRelativeRotation(FRotator(0, 0, 180));
	LightningFX->SetRelativeScale3D(FVector(2, 2, 2));
}

// Called when the game starts or when spawned
void AGolem::BeginPlay()
{
	Super::BeginPlay();

	GolemDeaggro();  // Go into Hide mode

	PawnSensing->OnHearNoise.AddDynamic(this, &AGolem::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &AGolem::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &AGolem::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &AGolem::MeleeAttack);  // bind the attack function to the OnReachedTarget event
}

// Called every frame
void AGolem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGolem::GolemAggro()
{
	DoHide = false;
	//Targetable = true;
	// Run To Target after a short delay
	FTimerHandle RunTimer;
	GetWorldTimerManager().SetTimer(RunTimer, this, &AEtherealEnemyMaster::RunToTarget, 4.0f, false);	
}

void AGolem::GolemDeaggro()
{
	DoHide = true;
}

// Melee Attack function
void AGolem::MeleeAttack()
{
	if (!Target->IsDead)
	{
		if (!IsAttacking)
		{
			IsAttacking = true;
			RunAI = false;

			int32 RandomAtk = FMath::RandRange(0, 7);  // get a random int

			if (!IsDead)
			{
				if (RandomAtk <= 2)
				{
					Stomp();
				}
				if (RandomAtk > 2 && RandomAtk <= 4)
				{
					Melee2();
				}
				if (RandomAtk > 4)
				{
					Melee1();
				}
			}
		}
	}
}

void AGolem::Melee1()
{
	DoMelee1 = true;
	EnemyDealDamage(50);
	//PowerBlastAudio->Play();
	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void AGolem::Melee2()
{
	DoMelee2 = true;
	EnemyDealDamage(50);
	//SpinAtkAudio->Play();
	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void AGolem::Stomp()
{
	DoStomp = true;
	EnemyDealDamage(60);
	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void AGolem::Death()
{
	//IsDead = true;
}

// A.I. Hearing
void AGolem::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			Aggro(PawnInstigator);
			GolemAggro();
		}
	}
}

// A.I. Sight
void AGolem::OnSeePawn(APawn* Pawn)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			Aggro(Pawn);
			GolemAggro();
		}
	}	
}

#undef LOCTEXT_NAMESPACE
