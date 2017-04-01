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
#include "Nightshade.h"

#define LOCTEXT_NAMESPACE "EtherealText"

ANightshade::ANightshade(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/MixamoAnimPack/Mixamo_Nightshade/Nightshade_J_Friedrich.Nightshade_J_Friedrich'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/MixamoAnimPack/Mixamo_Nightshade/Anim_Nightshade.Anim_Nightshade_C'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> BuildUpParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Elemental/Fire/P_Beam_Laser_Poison_BuildUP.P_Beam_Laser_Poison_BuildUP'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PowerBlastParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Elemental/Fire/P_Beam_Laser_Poison.P_Beam_Laser_Poison'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> SpinAtkParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Combat_Base/WeaponCombo/P_Nightshade_Slash.P_Nightshade_Slash'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> PowerBlastAudioObject(TEXT("SoundCue'/Game/MixamoAnimPack/Mixamo_Nightshade/Audio/Nightshade_PowerBlast_Cue.Nightshade_PowerBlast_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> SpinAtkAudioObject(TEXT("SoundCue'/Game/MixamoAnimPack/Mixamo_Nightshade/Audio/Nightshade_Slash_Cue.Nightshade_Slash_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DeathAudioObject(TEXT("SoundCue'/Game/MixamoAnimPack/Mixamo_Nightshade/Audio/Nightshade_Death_Cue.Nightshade_Death_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> HitAudioObject(TEXT("SoundCue'/Game/MixamoAnimPack/Mixamo_Nightshade/Audio/Nightshade_Hit_Cue.Nightshade_Hit_Cue'"));

	// Set Default Objects
	P_BuildUpFX = BuildUpParticleObject.Object;
	P_PowerBlastFX = PowerBlastParticleObject.Object;
	P_SpinAtkFX = SpinAtkParticleObject.Object;
	S_PowerBlastAudio = PowerBlastAudioObject.Object;
	S_SpinAtkAudio = SpinAtkAudioObject.Object;
	S_DeathAudio = DeathAudioObject.Object;
	S_HitAudio = HitAudioObject.Object;
	
	// Default Config
	Name = EEnemyNames::EN_Nightshade;
	NameText = LOCTEXT("NightshadeText", "Nightshade");
	Realm = ERealms::R_Empyrean;
	BattleType = EBattleTypes::BT_Standard;
	CommonDrop = EMasterGearList::GL_Antidote;
	UncommonDrop = EMasterGearList::GL_ExoBoots;
	RareDrop = EMasterGearList::GL_ExoGages;
	AttackDelay = 2.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	GetCharacterMovement()->MaxAcceleration = 30;

	// A.I. Config
	PawnSensing->HearingThreshold = 300;
	PawnSensing->LOSHearingThreshold = 400;
	PawnSensing->SightRadius = 750;
	PawnSensing->SetPeripheralVisionAngle(50.0f);
	AcceptanceRadius = 50.0f;
	RunAI = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(300);
	MeleeRadius->SetRelativeLocation(FVector(0, 0, 0));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 240));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	// Hit & Death Effect Config
	HitFX->SetRelativeLocation(FVector(40, 0, 10));
	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(1, 1, 1));
	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));
	DisappearFX->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.7f));

	// Enemy-Specific Object Config

	SpotLight = ObjectInitializer.CreateDefaultSubobject<USpotLightComponent>(this, TEXT("SpotLight"));
	SpotLight->SetupAttachment(GetMesh());
	SpotLight->SetRelativeLocation(FVector(0, 0, 500));
	SpotLight->SetRelativeRotation(FRotator(-90, 0, 0));
	SpotLight->Intensity = 500;
	SpotLight->LightColor = FColorList::LimeGreen;

	// Power Blast Box
	PowerBlastBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("PowerBlastBox"));
	PowerBlastBox->SetupAttachment(RootComponent);
	PowerBlastBox->SetRelativeLocation(FVector(600, 0, 0));
	PowerBlastBox->SetBoxExtent(FVector(600, 60, 60));

	// Spin Attack Box
	SpinAtkBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("SpinAtkBox"));
	SpinAtkBox->SetupAttachment(RootComponent);
	SpinAtkBox->SetRelativeLocation(FVector(300, 0, 0));
	SpinAtkBox->SetBoxExtent(FVector(300, 80, 80));

	// Build Up Effect (for him teleporting away)
	BuildUpFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("BuildUpFX"));
	BuildUpFX->SetupAttachment(RootComponent);
	BuildUpFX->Template = P_BuildUpFX;
	BuildUpFX->bAutoActivate = false;
	BuildUpFX->SetRelativeLocation(FVector(60, 0, 0));
	BuildUpFX->SetRelativeRotation(FRotator(0, 0, 180));
	BuildUpFX->SetRelativeScale3D(FVector(2, 2, 2));

	// Power Blast attack effect
	PowerBlastFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("PowerBlastFX"));
	PowerBlastFX->SetupAttachment(RootComponent);
	PowerBlastFX->Template = P_PowerBlastFX;
	//PowerBlastFX->bAutoManageAttachment = true;
	PowerBlastFX->bAutoActivate = false;
	PowerBlastFX->SetRelativeLocation(FVector(40, 0, 0));
	PowerBlastFX->SetRelativeRotation(FRotator(0, 0, 180));
	PowerBlastFX->SetRelativeScale3D(FVector(2, 2, 2));

	// Spin Attack effect
	SpinAtkFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("SpinAtkFX"));
	SpinAtkFX->SetupAttachment(RootComponent);
	SpinAtkFX->Template = P_SpinAtkFX;
	SpinAtkFX->bAutoActivate = false;
	SpinAtkFX->SetRelativeLocation(FVector(100, 0, 0));

	// Power Blast attack audio
	PowerBlastAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("PowerBlastAudio"));
	PowerBlastAudio->SetupAttachment(RootComponent);
	PowerBlastAudio->Sound = S_PowerBlastAudio;
	PowerBlastAudio->bAutoActivate = false;

	// Spin Attack audio
	SpinAtkAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SpinAtkAudio"));
	SpinAtkAudio->SetupAttachment(RootComponent);
	SpinAtkAudio->Sound = S_SpinAtkAudio;
	SpinAtkAudio->bAutoActivate = false;

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
}

// Called when the game starts or when spawned
void ANightshade::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &ANightshade::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &ANightshade::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &ANightshade::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &ANightshade::AttackCycle);  // bind the attack function to the OnReachedTarget event
}

// Called every frame
void ANightshade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Melee Attack function
void ANightshade::AttackCycle()
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
				if (RandomAtk <= 3)
				{
					PowerBlast();
				}
				if (RandomAtk > 3)
				{
					SpinAttack();
				}
			}
		}
	}
}

void ANightshade::PowerBlast()
{
	DoPowerBlast = true;
	EnemyDealDamage(50);
	PowerBlastAudio->Play();
	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void ANightshade::SpinAttack()
{
	DoSpinAtk = true;
	EnemyDealDamage(45);
	SpinAtkAudio->Play();
	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void ANightshade::RadialBlast()
{
	// This attack is imcomplete and unused for the Nightshade enemy

	DoRadialBlast = true;
	EnemyDealDamage(60);
	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void ANightshade::Death()
{
	IsDead = true;
	DeathAudio->Play();
}

// A.I. Hearing
void ANightshade::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
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
void ANightshade::OnSeePawn(APawn* Pawn)
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
