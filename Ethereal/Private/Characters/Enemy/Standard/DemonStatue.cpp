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
#include "SoulEater.h"
#include "DemonStatue.h"

#define LOCTEXT_NAMESPACE "EtherealText"

ADemonStatue::ADemonStatue(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Asset, Reference Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UDestructibleMesh> DestructibleMeshObject(TEXT("DestructibleMesh'/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Statues/StaticMesh/SM_Plains_Castle_DemonDoor_01_DM.SM_Plains_Castle_DemonDoor_01_DM'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> FlareRParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Elemental/ICE/Souleater_Statue_EyeFlare.Souleater_Statue_EyeFlare'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> FlareLParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Elemental/ICE/Souleater_Statue_EyeFlare.Souleater_Statue_EyeFlare'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> IdleRParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Chicken/Souleater_Statue_EyeIdle.Souleater_Statue_EyeIdle'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> IdleLParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Chicken/Souleater_Statue_EyeIdle.Souleater_Statue_EyeIdle'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> StompBlastParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/SoulEater-Statue-StompBlast.SoulEater-Statue-StompBlast'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> SoulSpawnParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/Fire/combat/SoulEaterSpawn.SoulEaterSpawn'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> StompDecalObject(TEXT("Material'/Game/Materials/AreaEffectDecals/M_SoulEater-Statue-StompDecal.M_SoulEater-Statue-StompDecal'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> JumpAudioObject(TEXT("SoundCue'/Game/Audio/Rocks/SoulEater_Statue_Jump_Cue.SoulEater_Statue_Jump_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> StompAudioObject(TEXT("SoundCue'/Game/Audio/Rocks/SoulEater_Statue_Stomp_Cue.SoulEater_Statue_Stomp_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ExplosionAudioObject(TEXT("SoundCue'/Game/Audio/Impacts/Rock_Explo_Slowed02_L_Cue.Rock_Explo_Slowed02_L_Cue'"));
	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/Blueprints/Characters/Enemy/1-ShiitakeTemple/Curve_DemonStatueJump.Curve_DemonStatueJump'"));

	// Set Default Objects
	DM_DemonDoor = DestructibleMeshObject.Object;
	P_EyeFlareFX_R = FlareRParticleObject.Object;
	P_EyeFlareFX_L = FlareLParticleObject.Object;
	P_EyeIdleFX_R = IdleRParticleObject.Object;
	P_EyeIdleFX_L = IdleRParticleObject.Object;
	P_SoulSpawnFX_L = SoulSpawnParticleObject.Object;
	P_SoulSpawnFX_R = SoulSpawnParticleObject.Object;
	P_StompBlastFX = StompBlastParticleObject.Object;
	S_JumpAudio = JumpAudioObject.Object;
	S_StompAudio = StompAudioObject.Object;
	S_ExplosionAudio = ExplosionAudioObject.Object;
	JumpCurve = Curve.Object;

	// Default Config
	Name = EEnemyNames::EN_DemonStatue;
	NameText = LOCTEXT("DemonStatueText", "Demon Statue");
	Realm = ERealms::R_Shiitake;
	BattleType = EBattleTypes::BT_Standard;
	CommonDrop = EMasterGearList::GL_None;
	UncommonDrop = EMasterGearList::GL_Potion;
	RareDrop = EMasterGearList::GL_HiEther;
	BaseEyeHeight = 16;
	AttackDelay = 2.0f;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	GetCharacterMovement()->MaxAcceleration = 20;
	GetCharacterMovement()->RotationRate = FRotator(0, 90, 0);

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 160));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	// Hit & Death Effect Config
	HitFX->SetRelativeScale3D(FVector(0.6f, 0.6f, 0.6f));
	DeathFX->SetRelativeLocation(FVector(0, 0, -88));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
	DisappearFX->SetRelativeLocation(FVector(0, 0, -75));
	DisappearFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));

	// Pawn A.I. config
	PawnSensing->HearingThreshold = 150;
	PawnSensing->LOSHearingThreshold = 200;
	PawnSensing->SightRadius = 250;
	PawnSensing->SetPeripheralVisionAngle(40.0f);
	AcceptanceRadius = 25.0f;
	RunAI = false;

	// Create and configure other components
	StompRadius = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("StompRadius"));
	StompRadius->SetupAttachment(RootComponent);
	StompRadius->SetSphereRadius(280.0f);
	StompRadius->bHiddenInGame = true;

	StompDecal = ObjectInitializer.CreateDefaultSubobject<UDecalComponent>(this, TEXT("StompDecal"));
	StompDecal->SetupAttachment(RootComponent);
	StompDecal->SetMaterial(0, StompDecalObject.Object);  // set the Stomp Decal material
	StompDecal->SetRelativeRotation(FRotator(90, 0, 0));
	StompDecal->SetRelativeScale3D(FVector(1.3f, 1.3f, 1.3f));
	StompDecal->SetVisibility(false);

	DemonDoor = ObjectInitializer.CreateDefaultSubobject<UDestructibleComponent>(this, TEXT("DemonDoor"));
	DemonDoor->SetupAttachment(RootComponent);
	DemonDoor->SetDestructibleMesh(DM_DemonDoor);
	//DemonDoor->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	//DemonDoor->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	DemonDoor->SetRelativeLocation(FVector(0, 0, -90));
	DemonDoor->SetRelativeRotation(FRotator(0, -90, 0));

	EyeFlareFX_R = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("EyeFlareFX_R"));
	EyeFlareFX_R->SetupAttachment(DemonDoor);
	EyeFlareFX_R->Template = P_EyeFlareFX_R;
	EyeFlareFX_R->SetRelativeLocation(FVector(14, 28, 168));
	EyeFlareFX_R->bAutoActivate = false;

	EyeFlareFX_L = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("EyeFlareFX_L"));
	EyeFlareFX_L->SetupAttachment(DemonDoor);
	EyeFlareFX_L->Template = P_EyeFlareFX_L;
	EyeFlareFX_L->SetRelativeLocation(FVector(-14, 28, 168));
	EyeFlareFX_L->bAutoActivate = false;

	EyeIdleFX_R = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("EyeIdleFX_R"));
	EyeIdleFX_R->SetupAttachment(DemonDoor);
	EyeIdleFX_R->Template = P_EyeIdleFX_R;
	EyeIdleFX_R->SetRelativeLocation(FVector(10, 28, 168));
	EyeIdleFX_R->bAutoActivate = false;

	EyeIdleFX_L = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("EyeIdleFX_L"));
	EyeIdleFX_L->SetupAttachment(DemonDoor);
	EyeIdleFX_L->Template = P_EyeIdleFX_L;
	EyeIdleFX_L->SetRelativeLocation(FVector(-10, 28, 168));
	EyeIdleFX_L->bAutoActivate = false;

	SoulSpawnFX_L = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("SoulSpawnFX_L"));
	SoulSpawnFX_L->SetupAttachment(RootComponent);
	SoulSpawnFX_L->Template = P_SoulSpawnFX_L;
	SoulSpawnFX_L->SetRelativeLocation(FVector(0, -150, 0));
	SoulSpawnFX_L->SetRelativeRotation(FRotator(0, -90, 0));
	SoulSpawnFX_L->SetWorldScale3D(FVector(3, 3, 3));
	SoulSpawnFX_L->bAutoActivate = false;

	SoulSpawnFX_R = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("SoulSpawnFX_R"));
	SoulSpawnFX_R->SetupAttachment(RootComponent);
	SoulSpawnFX_R->Template = P_SoulSpawnFX_R;
	SoulSpawnFX_R->SetRelativeLocation(FVector(0, 150, 0));
	SoulSpawnFX_R->SetRelativeRotation(FRotator(0, -90, 0));
	SoulSpawnFX_R->SetWorldScale3D(FVector(3, 3, 3));
	SoulSpawnFX_R->bAutoActivate = false;

	StompBlastFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("StompBlast"));
	StompBlastFX->SetupAttachment(RootComponent);
	StompBlastFX->Template = P_StompBlastFX;
	StompBlastFX->SetRelativeLocation(FVector(0, 0, -132));
	StompBlastFX->SetRelativeScale3D(FVector(3, 3, 3));
	StompBlastFX->bAutoActivate = false;

	JumpAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("JumpAudio"));
	JumpAudio->SetupAttachment(RootComponent);
	JumpAudio->Sound = S_JumpAudio;
	JumpAudio->bAutoActivate = false;

	StompAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("StompAudio"));
	StompAudio->SetupAttachment(RootComponent);
	StompAudio->Sound = S_StompAudio;
	StompAudio->bAutoActivate = false;

	ExplosionAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("ExplosionAudio"));
	ExplosionAudio->SetupAttachment(RootComponent);
	ExplosionAudio->Sound = S_ExplosionAudio;
	ExplosionAudio->bAutoActivate = false;

	JumpTimeline = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("JumpTimeline"));
	InterpFunction.BindUFunction(this, FName{ TEXT("TimelineFloatReturn") });

	AreSpawned = false;
}

// Called when the game starts or when spawned
void ADemonStatue::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &ADemonStatue::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &ADemonStatue::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &ADemonStatue::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &ADemonStatue::StompAttack);  // bind the attack function to the OnReachedTarget event
}

// Called every frame
void ADemonStatue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Show the statue's glowing red eyes
void ADemonStatue::ToggleEyes(bool ShowEyes)
{
	if (ShowEyes)
	{
		EyeFlareFX_R->Activate();
		EyeFlareFX_L->Activate();
		EyeIdleFX_R->Activate();
		EyeIdleFX_L->Activate();
	}
	else
	{
		EyeFlareFX_R->Deactivate();
		EyeFlareFX_L->Deactivate();
		EyeIdleFX_R->Deactivate();
		EyeIdleFX_L->Deactivate();
	}
}

// DEATH
void ADemonStatue::Death()
{
	DemonDoor->ApplyRadiusDamage(100, this->GetActorLocation(), 100, 100, true);  // Destroy the door
	ToggleEyes(false);
	//Target->EtherealPlayerState->EnemyKillReward(Level, CommonDrop, UncommonDrop, RareDrop);  // reward the player for killing this enemy
	FinalDeath(true, false);
}

// SPAWN SOUL EATERS
void ADemonStatue::SpawnSoulEaters()
{
	if (!AreSpawned)
	{
		AreSpawned = true; // set AreSpawned true, so that SoulEaters cannot be spawned again from this Statue.

		ExplosionAudio->Play();
		SoulSpawnFX_L->Activate();
		SoulSpawnFX_R->Activate();

		AEtherealEnemyMaster* SoulEaterL = GetWorld()->SpawnActor<ASoulEater>(SoulSpawnFX_L->GetComponentLocation(), FRotator(0, -90, 0));
		if (SoulEaterL)
		{
			SoulEaterL->SpawnDefaultController();
			SoulEaterL->Level = Level;
			SoulEaterL->SetBaseStats();
		}

		AEtherealEnemyMaster* SoulEaterR = GetWorld()->SpawnActor<ASoulEater>(SoulSpawnFX_R->GetComponentLocation(), FRotator(0, -90, 0));
		if (SoulEaterR)
		{
			SoulEaterR->SpawnDefaultController();
			SoulEaterR->Level = Level;
			SoulEaterR->SetBaseStats();
		}
	}	
}

// STOMP ATTACK
void ADemonStatue::StompAttack()
{
	RunAI = false; // stop AI movement
	JumpAudio->Play();
	StompDecal->SetVisibility(true);

	JumpTimeline->AddInterpFloat(JumpCurve, InterpFunction, FName{ TEXT("Float") });
	JumpTimeline->PlayFromStart();

	// Do the stomp blast after the timeline completes
	FTimerHandle BlastTimer;
	GetWorldTimerManager().SetTimer(BlastTimer, this, &ADemonStatue::StompBlast, 2.0f, false);
}

// Jump Timeline
void ADemonStatue::TimelineFloatReturn(float val)
{
	DemonDoor->SetRelativeLocation(FVector(0, 0, FMath::Lerp(-90, 0, val))); // lerps from the door's starting Z location to Z location plus 90
}

// Stomp Blast Attack
void ADemonStatue::StompBlast()
{
	if (!IsDead)  // don't run this function if dead
	{
		EnemyDealDamage(40);  // set damage output
		StompBlastFX->Activate();
		StompDecal->SetVisibility(false);
		StompAudio->Play();
		RunAI = true;

		TArray<AActor*> Overlapping;  // define a local array to store hits
		StompRadius->GetOverlappingActors(Overlapping, AEtherealPlayerMaster::StaticClass()); // check for overlapping players within the stomp radius

		for (AActor* Actor : Overlapping) // for each actor found overlapping
		{
			AEtherealPlayerMaster* Player = Cast<AEtherealPlayerMaster>(Actor);  // cast to Player Master

			if (Player) // if succeeded
			{
				Player->PlayerTakeDamage(DamageOutput);  // have the player take damage
			}
		}
	}	
}

void ADemonStatue::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			Aggro(PawnInstigator);
			ToggleEyes(true);
			SpawnSoulEaters();
			RunToTarget();
		}
	}
}

// SAW PLAYER
void ADemonStatue::OnSeePawn(APawn* Pawn)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			ToggleEyes(true);
			Aggro(Pawn);
			SpawnSoulEaters();
			RunToTarget();
		}
	}	
}

#undef LOCTEXT_NAMESPACE
