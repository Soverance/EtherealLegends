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
#include "NPCs/Objects/ReturnPortal.h"
#include "Eternal.h"
#include "Zhan.h"

#define LOCTEXT_NAMESPACE "EtherealText"

AZhan::AZhan(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/MixamoAnimPack/Mixamo_Ganfault/Mesh/Mixamo_Ganfault_Aure.Mixamo_Ganfault_Aure'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/MixamoAnimPack/Mixamo_Ganfault/Anims/Zhan_Anim.Zhan_Anim_C'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> LaughterAudioObject(TEXT("SoundCue'/Game/Audio/Party/voice_evil_laugh_01_Cue.voice_evil_laugh_01_Cue'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BladeMesh(TEXT("SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_HeroSword10/SK_Blade_HeroSword10.SK_Blade_HeroSword10'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> EyeParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Chicken/Souleater_Statue_EyeIdle.Souleater_Statue_EyeIdle'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> BuildUpParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Elemental/Fire/P_Beam_Laser_Fire_BuildUP.P_Beam_Laser_Fire_BuildUP'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PowerBlastParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Elemental/Fire/P_Beam_Laser_Fire.P_Beam_Laser_Fire'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> SpinAtkParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Skill_TeleCharge/Zhan_SpinAtkFX.Zhan_SpinAtkFX'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> PowerBlastAudioObject(TEXT("SoundCue'/Game/Audio/Party/Zhan_PowerBlast_Cue.Zhan_PowerBlast_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> SpinAtkAudioObject(TEXT("SoundCue'/Game/Audio/Party/Zhan_SpinAtk_Cue.Zhan_SpinAtk_Cue'"));
	static ConstructorHelpers::FObjectFinder<UClass> InitAggroBlueprintObject(TEXT("Blueprint'/Game/Blueprints/Characters/Enemy/6-CelestialNexus/Zhan_AggroDrop.Zhan_AggroDrop_C'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> EscapePortalObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Ausar/Zhan_EscapePortal.Zhan_EscapePortal'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> EscapeBurstPortalObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Combat_Base/WeaponCombo/P_Cube_Mesh_Test.P_Cube_Mesh_Test'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> PortalExplosionAudioObject(TEXT("SoundCue'/Game/Audio/Impacts/Zhan_PortalExplosion_Cue.Zhan_PortalExplosion_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> EscapeAudioObject(TEXT("SoundCue'/Game/Audio/Impacts/Zhan_Escape_Cue.Zhan_Escape_Cue'"));
	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/Blueprints/Characters/Enemy/6-CelestialNexus/Curve_ZhanEscape.Curve_ZhanEscape'"));

	// Set Default Objects
	AggroDropBP = InitAggroBlueprintObject.Object;
	S_LaughterAudio = LaughterAudioObject.Object;
	SK_Blade = BladeMesh.Object;
	P_EyeFX = EyeParticleObject.Object;
	P_BuildUpFX = BuildUpParticleObject.Object;
	P_PowerBlastFX = PowerBlastParticleObject.Object;
	P_SpinAtkFX = SpinAtkParticleObject.Object;
	S_PowerBlastAudio = PowerBlastAudioObject.Object;
	S_SpinAtkAudio = SpinAtkAudioObject.Object;
	P_EscapeFX = EscapePortalObject.Object;
	P_EscapeBurstFX = EscapeBurstPortalObject.Object;
	S_PortalExplosionAudio = PortalExplosionAudioObject.Object;
	S_EscapeAudio = EscapeAudioObject.Object;
	JumpCurve = Curve.Object;

	/////////////////////////////////////
	// DEFAULTS

	Name = EEnemyNames::EN_Zhan;
	NameText = LOCTEXT("ZhanText", "Zhan");
	Realm = ERealms::R_Celestial;
	BattleType = EBattleTypes::BT_Boss;
	CommonDrop = EMasterGearList::GL_Elixer;
	UncommonDrop = EMasterGearList::GL_Haste;
	RareDrop = EMasterGearList::GL_Excalibur;
	AttackDelay = 3.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	GetCharacterMovement()->MaxAcceleration = 0;	

	// A.I. Config
	PawnSensing->HearingThreshold = 300;
	PawnSensing->LOSHearingThreshold = 400;
	PawnSensing->SightRadius = 750;
	PawnSensing->SetPeripheralVisionAngle(50.0f);
	AcceptanceRadius = 50.0f;
	RunAI = false;

	Targetable = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(1, 1, 1));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// Melee Radius Config
	MeleeRadius->SetSphereRadius(300);
	MeleeRadius->SetRelativeLocation(FVector(0, 0, 0));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 180));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	// Hit & Death Effect Config
	HitFX->SetRelativeLocation(FVector(40, 0, 10));
	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(1, 1, 1));
	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Laughter attack audio
	LaughterAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("LaughterAudio"));
	LaughterAudio->SetupAttachment(RootComponent);
	LaughterAudio->Sound = S_LaughterAudio;
	LaughterAudio->bAutoActivate = false;

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

	// Blade skeletal mesh
	Blade = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Blade"));
	Blade->SetupAttachment(GetMesh(), FName(TEXT("R_Weapon")));
	Blade->SkeletalMesh = SK_Blade;

	// Glowing Eye Particle Effect
	EyeFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("EyeFX"));
	EyeFX->SetupAttachment(GetMesh(), FName(TEXT("EyeSocket")));
	EyeFX->Template = P_EyeFX;
	EyeFX->bAutoActivate = false;

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
	SpinAtkFX->SetRelativeLocation(FVector(300, 0, 0));

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

	// PortalExplosion audio
	PortalExplosionAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("PortalExplosionAudio"));
	PortalExplosionAudio->SetupAttachment(RootComponent);
	PortalExplosionAudio->Sound = S_PortalExplosionAudio;
	PortalExplosionAudio->bAutoActivate = false;

	// Escape audio
	EscapeAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("EscapeAudio"));
	EscapeAudio->SetupAttachment(RootComponent);
	EscapeAudio->Sound = S_EscapeAudio;
	EscapeAudio->bAutoActivate = false;

	// Escape Timeline
	JumpTimeline = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("JumpTimeline"));
	InterpFunction.BindUFunction(this, FName{ TEXT("TimelineFloatReturn") });

	///////////////////////////////////////////
	// STARTING HEIGHT MOD

	StartHeightOffset = 200.0f;
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, (GetActorLocation().Z + StartHeightOffset)));  // places Zhan in the air, so he can burst out all awesome during his aggro sequence
	GetCharacterMovement()->GravityScale = 0; // turn off Gravity so he stays in the air
}

// Called when the game starts or when spawned
void AZhan::BeginPlay()
{
	Super::BeginPlay();

	Targetable = false;
	GetCapsuleComponent()->SetVisibility(false, true); // hide root object and propagate to all children

	PawnSensing->OnHearNoise.AddDynamic(this, &AZhan::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &AZhan::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &AZhan::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &AZhan::AttackCycle);  // bind the attack function to the OnReachedTarget event

	// We collected this reference in the EnemyMaster class
	if (EtherealGameInstance)
	{
		// Set all Volume Controls
		EtherealGameInstance->SetAudioVolume(LaughterAudio, EAudioTypes::AT_SoundEffect);
		EtherealGameInstance->SetAudioVolume(PowerBlastAudio, EAudioTypes::AT_SoundEffect);
		EtherealGameInstance->SetAudioVolume(SpinAtkAudio, EAudioTypes::AT_SoundEffect);
		EtherealGameInstance->SetAudioVolume(PortalExplosionAudio, EAudioTypes::AT_SoundEffect);
		EtherealGameInstance->SetAudioVolume(EscapeAudio, EAudioTypes::AT_SoundEffect);
	}
}

// Called every frame
void AZhan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsDead)
	{
		// Draw Debug Cylinder on Map
		if (Target->MapControl)
		{
			FVector DebugStart = GetActorLocation();
			FVector DebugEnd = FVector(DebugStart.X, DebugStart.Y, (DebugStart.Z + 1500));

			DrawDebugCylinder(GetWorld(), DebugStart, DebugEnd, 10, 12, FColor::Yellow, false, 0, 0);
		}
	}	
}

void AZhan::InitAggro()
{
	EtherealGameInstance->BlackBox->HasEngagedBoss = true;  // Engage Boss
	Aggro(Target);  // AGGRO
	// Spawn Zhan's Aggro Drop at current location - StartHeightOffset on Z
	AActor* AggroDrop = UCommonLibrary::SpawnBP(GetWorld(), AggroDropBP, FVector(GetActorLocation().X, GetActorLocation().Y, (GetActorLocation().Z - StartHeightOffset)), GetActorRotation());
	AudioManager->Play_Zhan_Intro();
	// Start the fall process
	FTimerHandle AggroTimer;
	GetWorldTimerManager().SetTimer(AggroTimer, this, &AZhan::FallToAggro, 9.8f, false);
}

void AZhan::FallToAggro()
{
	this->GetCharacterMovement()->GravityScale = 0.1f;  // make him fall in slow motion
	this->GetCapsuleComponent()->SetVisibility(true, true);  // this will also turn on the Targeting Reticle
	DoFallAggro = true;

	UGameplayStatics::PlayWorldCameraShake(GetWorld(), Target->LevelUpCamShake, Target->GetActorLocation(), 0, 10000, 1, false);  // level up cam shake 
	// TO DO : Client Play Force Feedback FF_ZhanSpawn

	// earlier code in BeginPlay() sets the reticle visible, be sure to turn it off.
	if (TargetingReticle->IsVisible())
	{
		TargetingReticle->SetVisibility(false);
	}

	// Start the attack cycle
	FTimerHandle AttackTimer;
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AZhan::StartAttacking, 7.0f, false);
}

void AZhan::StartAttacking()
{
	Targetable = true;
	
	GetCharacterMovement()->GravityScale = 1.0f;
	GetCharacterMovement()->MaxAcceleration = 30;
	RunToTarget();
	AudioManager->Play_Zhan_Battle();
}

void AZhan::Death()
{
	IsDead = true;
}

// Melee Attack function
void AZhan::AttackCycle()
{
	if (!Target->IsDead)
	{
		if (!IsAttacking)
		{
			// we set all these to false at the beginning of his attack cycle, just to be certain he never gets locked in an attack anim
			DoPowerBlast = false;
			DoSpinAtk = false;
			DoRadialBlast = false;

			IsAttacking = true;
			RunAI = false;

			int32 RandomAtk = FMath::RandRange(0, 7);  // get a random int

			if (!IsDead)
			{
				if (RandomAtk <= 2)
				{
					PowerBlast();
				}
				if (RandomAtk > 2 && RandomAtk <= 4)
				{
					RadialBlast();
				}
				if (RandomAtk > 4)
				{
					SpinAttack();
				}
			}
		}
	}
}

void AZhan::PowerBlast()
{
	DoPowerBlast = true;
	EnemyDealDamage(50);
	PowerBlastAudio->Play();
	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void AZhan::SpinAttack()
{
	DoSpinAtk = true;
	EnemyDealDamage(45);
	SpinAtkAudio->Play();
	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void AZhan::RadialBlast()
{
	DoRadialBlast = true;
	EnemyDealDamage(60);
	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void AZhan::Escape()
{
	///////////////////////////////
	// ACHIEVEMENTS
	switch (Target->EtherealGameInstance->CurrentRealm)
	{
		case ERealms::R_Arcadia:
			Target->EtherealPlayerController->Achievement_Realm_Shiitake();  // give this player the Achievement for clearing this realm
			break;
		case ERealms::R_Vulcan:
			Target->EtherealPlayerController->Achievement_Realm_Vulcan();  // give this player the Achievement for clearing this realm
			break;
		case ERealms::R_Boreal:
			Target->EtherealPlayerController->Achievement_Realm_Boreal();  // give this player the Achievement for clearing this realm
			break;
		case ERealms::R_Yggdrasil:
			Target->EtherealPlayerController->Achievement_Realm_Yggdrasil();  // give this player the Achievement for clearing this realm
			break;
		case ERealms::R_Empyrean:
			Target->EtherealPlayerController->Achievement_Realm_Empyrean();  // give this player the Achievement for clearing this realm
			break;
		case ERealms::R_Celestial:
			Target->EtherealPlayerController->Achievement_Realm_Celestial();  // give this player the Achievement for clearing this realm
			break;

	}

	//////////////////////////////
	// Spawn the Escape Portal
	EscapeFX = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), P_EscapeFX, this->GetActorLocation(), this->GetActorRotation(), true);  

	GetCharacterMovement()->GravityScale = 0; // turn off Gravity so he stays in the air
	
	PortalExplosionAudio->Play();
	EscapeAudio->Play();

	// 4 second timeline, slowly rising Zhan into the air. Timeline simply adds 0.5 to his Z every update cycle.
	JumpTimeline->AddInterpFloat(JumpCurve, InterpFunction, FName{ TEXT("Float") });
	JumpTimeline->PlayFromStart();

	// Explode after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AZhan::Explode, 4.0f, false);
}

void AZhan::Explode()
{
	EscapeBurstFX = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), P_EscapeBurstFX, GetMesh()->GetComponentLocation(), this->GetActorRotation(), true);
	GetCapsuleComponent()->SetVisibility(false, true); // hide root object and propagate to all children
	
	// Spawn the Arcadia Return Portal after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AZhan::DropPortal, 0.5f, false);
}

void AZhan::DropPortal()
{
	EscapeBurstFX->Deactivate();  // deactivate the EscapeBurst	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);  // disable zhan's collision

	// if Zhan dies within the Celestial Nexus...
	if (Target->EtherealGameInstance->CurrentRealm == ERealms::R_Celestial)
	{
		AEternal* Eternal = NULL;  // create null reference

		// Find the Eternal enemy and call Init Aggro
		for (TActorIterator<AEternal> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			Eternal= *ActorItr; // store the instance of The Eternal
		}

		if (Eternal)
		{
			Eternal->InitAggro();  // Init Aggro on Eternal
		}		
	}
	else
	{
		AudioManager->Play_BGM(Target->EtherealGameInstance->CurrentRealm);  // Play CurrentRealm BGM
		AudioManager->Play_SFX_LevelUp();  // Play LevelUp SFX to congratulate player.  It should probably be a different, distinct sound, but I haven't found a good one yet.

		// In all other realms, spawn the Arcadia Return Portal wherever Zhan died
		AReturnPortal* ReturnPortal = GetWorld()->SpawnActor<AReturnPortal>(GetActorLocation(), GetActorRotation());
	}
	
}

// Jump Timeline
void AZhan::TimelineFloatReturn(float val)
{
	GetMesh()->SetRelativeLocation(FVector(0, 0, FMath::Lerp(0, 650, val))); // lerps from the starting Z location to end location
}

void AZhan::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			// This functionality is removed because Zhan does not aggro in a traditional manner
			//Aggro(PawnInstigator);
		}
	}
}

void AZhan::OnSeePawn(APawn* Pawn)
{
	if (!IsAggroed)
	{
		// This functionality is removed because Zhan does not aggro in a traditional manner
		//Aggro(Pawn);
	}
}

#undef LOCTEXT_NAMESPACE
