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
#include "Kismet/KismetMathLibrary.h"
#include "PowerDrone.h"

#define LOCTEXT_NAMESPACE "EtherealText"

APowerDrone::APowerDrone(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/Vehicles/Infil1/Minibot01/Mesh/SK_Minibot.SK_Minibot'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/Vehicles/Infil1/Minibot01/Mesh/Anim_PowerDrone.Anim_PowerDrone_C'"));
	static ConstructorHelpers::FObjectFinder<UClass> LaserBlueprintObject(TEXT("Blueprint'/Game/Blueprints/Characters/Enemy/5-EmpyreanGardens/PowerDrone_LaserBlast.PowerDrone_LaserBlast_C'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> FireAudioObject(TEXT("SoundCue'/Game/Sounds/Stingers/Mono/StingerPickup_Health01_Cue.StingerPickup_Health01_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DeathAudioObject(TEXT("SoundCue'/Game/Audio/Robot/Robot_Gunfire_Cue.Robot_Gunfire_Cue'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> DroneHitParticleObject(TEXT("ParticleSystem'/Game/Effects/Sparks/P_WeldSparks.P_WeldSparks'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionParticleObject(TEXT("ParticleSystem'/Game/Particles/P_Explosion.P_Explosion'"));

	// Set Default Objects
	S_FireAudio = FireAudioObject.Object;
	S_DeathAudio = DeathAudioObject.Object;
	P_ExplosionFX = ExplosionParticleObject.Object;

	LaserBlastBP = LaserBlueprintObject.Object;
	
	// Default Config
	Name = EEnemyNames::EN_PowerDrone;
	NameText = LOCTEXT("PowerDroneText", "Power Drone");
	Realm = ERealms::R_Empyrean;
	BattleType = EBattleTypes::BT_Standard;
	CommonDrop = EMasterGearList::GL_EchoHerb;
	UncommonDrop = EMasterGearList::GL_Reraise;
	RareDrop = EMasterGearList::GL_ExoHelmet;
	AttackDelay = 2.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	GetCharacterMovement()->MaxAcceleration = 30;

	// Pawn A.I. config
	PawnSensing->HearingThreshold = 150;
	PawnSensing->LOSHearingThreshold = 200;
	PawnSensing->SightRadius = 500;
	PawnSensing->SetPeripheralVisionAngle(40.0f);
	AcceptanceRadius = 350.0f;
	RunAI = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));
	GetMesh()->SetRelativeLocation(FVector(-50, 0, 20));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(100);
	MeleeRadius->SetRelativeLocation(FVector(20, 0, -75));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 120, 180));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	
	// FX Config
	HitFX->SetRelativeLocation(FVector(0, 0, 0));
	HitFX->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	
	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Enemy-Specific Object Config
	// Melee audio
	FireAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("FireAudio"));
	FireAudio->SetupAttachment(RootComponent);
	FireAudio->Sound = S_FireAudio;
	FireAudio->bAutoActivate = false;

	// Death audio
	DeathAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DeathAudio"));
	DeathAudio->SetupAttachment(RootComponent);
	DeathAudio->Sound = S_DeathAudio;
	DeathAudio->bAutoActivate = false;

	// Explosion Effect
	ExplosionFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("ExplosionFX"));
	ExplosionFX->SetupAttachment(RootComponent);
	ExplosionFX->Template = P_ExplosionFX;
	ExplosionFX->bAutoActivate = false;
	ExplosionFX->SetRelativeLocation(FVector(0, 0, 0));
	ExplosionFX->SetRelativeRotation(FRotator(0, 0, 0));
	ExplosionFX->SetRelativeScale3D(FVector(2, 2, 2));

	// hit fx override
	P_HitFX = DroneHitParticleObject.Object;
	HitFX->Template = P_HitFX;
}

// Called when the game starts or when spawned
void APowerDrone::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &APowerDrone::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &APowerDrone::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &APowerDrone::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &APowerDrone::MeleeAttack);  // bind the attack function to the OnReachedTarget event
}

// Called every frame
void APowerDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LookAtTarget();
}

// Melee Attack function
void APowerDrone::MeleeAttack()
{
	if (!Target->IsDead)
	{
		if (!IsAttacking)
		{
			IsAttacking = true;
			RunAI = false;
			FireLaser();
		}
	}
}

void APowerDrone::FireLaser()
{
	EnemyDealDamage(35);
	FireAudio->Play();
	// Blast the Player!
	AActor* LaserBlast = UCommonLibrary::SpawnBP(GetWorld(), LaserBlastBP, GetMesh()->GetComponentLocation(), GetMesh()->GetComponentRotation());

	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void APowerDrone::LookAtTarget()
{
	FVector DroneLocation = GetActorLocation(); // GetFlytrap rotation
	FVector PlayerLocation = Target->GetActorLocation();  // get player location
	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(DroneLocation, PlayerLocation);  // find look at rotation
	FRotator CorrectedRot = FRotator(LookAtRot.Pitch, LookAtRot.Yaw, LookAtRot.Roll);  // correct rotation
	SetActorRotation(CorrectedRot); // set rotation to the corrected rotation
}

void APowerDrone::Death()
{
	ExplosionFX->Activate();
	DeathAudio->Play();
	GetMesh()->SetVisibility(false);

	// wait a bit before adding EXP (delays the UI display for readability).
	FTimerDelegate DelegateDeath;
	DelegateDeath.BindUFunction(this, FName("FinalDeath"), true, false);
	FTimerHandle DeathTimer;
	GetWorldTimerManager().SetTimer(DeathTimer, DelegateDeath, 1.0f, false);
}

// A.I. Hearing
void APowerDrone::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			Aggro(PawnInstigator);
			RunToTarget();
		}
	}
}

// A.I. Sight
void APowerDrone::OnSeePawn(APawn* Pawn)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			Aggro(Pawn);
			RunToTarget();
		}
	}	
}

#undef LOCTEXT_NAMESPACE
