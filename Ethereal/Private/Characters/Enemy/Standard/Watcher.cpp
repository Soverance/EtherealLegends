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
#include "Watcher.h"

#define LOCTEXT_NAMESPACE "EtherealText"

AWatcher::AWatcher(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/EtherealParty/Watcher/Watcher.Watcher'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/Watcher/Anim_Watcher.Anim_Watcher_C'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> EyeBlastParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Elemental/Fire/Watcher_EyeBlast.Watcher_EyeBlast'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> BeamAudioObject(TEXT("SoundCue'/Game/EtherealParty/Watcher/Audio/Watcher_Beam_Cue.Watcher_Beam_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> PreAtkAudioObject(TEXT("SoundCue'/Game/EtherealParty/Watcher/Audio/Watcher-PreAtk_Cue.Watcher-PreAtk_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DeathAudioObject(TEXT("SoundCue'/Game/EtherealParty/Watcher/Audio/Watcher_Death_Cue.Watcher_Death_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> FlapAudioObject(TEXT("SoundCue'/Game/EtherealParty/Watcher/Audio/Watcher_Flap_Cue.Watcher_Flap_Cue'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> BeamDecalObject(TEXT("Material'/Game/Materials/AreaEffectDecals/M_Watcher_BarDecal.M_Watcher_BarDecal'"));

	// Set Default Objects
	P_EyeBeamBlast = EyeBlastParticleObject.Object;
	S_BeamAudio = BeamAudioObject.Object;
	S_PreAtkAudio = PreAtkAudioObject.Object;
	S_DeathAudio = DeathAudioObject.Object;
	S_FlapAudio = FlapAudioObject.Object;

	Name = EEnemyNames::EN_Watcher;
	NameText = LOCTEXT("WatcherText", "Watcher");
	Realm = ERealms::R_Shiitake;
	BattleType = EBattleTypes::BT_Standard;
	CommonDrop = EMasterGearList::GL_None;
	UncommonDrop = EMasterGearList::GL_HiPotion;
	RareDrop = EMasterGearList::GL_Reraise;
	BaseEyeHeight = 16;
	AttackDelay = 2.0f;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	GetCharacterMovement()->MaxAcceleration = 30;
	GetCharacterMovement()->RotationRate = FRotator(0, 90, 0);

	// Pawn A.I. config
	PawnSensing->HearingThreshold = 150;
	PawnSensing->LOSHearingThreshold = 200;
	PawnSensing->SightRadius = 500;
	PawnSensing->SetPeripheralVisionAngle(40.0f);
	AcceptanceRadius = 25.0f;
	RunAI = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(2, 2, 2));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -100));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// Melee Radius Config
	MeleeRadius->SetSphereRadius(70);
	MeleeRadius->SetRelativeLocation(FVector(15, 0, 0));

	// Targeting Reticle Config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 140));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	// Hit & Death Effect Config
	HitFX->SetRelativeLocation(FVector(0, 0, -60));
	DeathFX->SetRelativeLocation(FVector(0, 0, -85));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Create and Configure
	EyeBeamBlast = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("EyeBeamBlast"));
	EyeBeamBlast->SetupAttachment(GetMesh(), "EyeSocket");
	EyeBeamBlast->Template = P_EyeBeamBlast;
	EyeBeamBlast->bAutoActivate = false;

	BeamAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BeamAudio"));
	BeamAudio->SetupAttachment(GetMesh());
	BeamAudio->Sound = S_BeamAudio;
	BeamAudio->bAutoActivate = false;

	PreAtkAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("PreAtkAudio"));
	PreAtkAudio->SetupAttachment(GetMesh());
	PreAtkAudio->Sound = S_PreAtkAudio;
	PreAtkAudio->bAutoActivate = false;

	DeathAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DeathAudio"));
	DeathAudio->SetupAttachment(GetMesh());
	DeathAudio->Sound = S_DeathAudio;
	DeathAudio->bAutoActivate = false;

	FlapAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("FlapAudio"));
	FlapAudio->SetupAttachment(GetMesh());
	FlapAudio->Sound = S_FlapAudio;
	FlapAudio->bAutoActivate = false;

	BeamBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BeamBox"));
	BeamBox->SetupAttachment(RootComponent);
	BeamBox->SetRelativeLocation(FVector(260, 0, 0));
	BeamBox->SetBoxExtent(FVector(250, 100, 150));

	BeamDecal = ObjectInitializer.CreateDefaultSubobject<UDecalComponent>(this, TEXT("BeamDecal"));
	BeamDecal->SetupAttachment(RootComponent);
	BeamDecal->SetMaterial(0, BeamDecalObject.Object);  // set the Beam Decal material
	BeamDecal->SetRelativeRotation(FRotator(90, 0, -90));
	BeamDecal->SetRelativeScale3D(FVector(2, 2, 2));
	BeamDecal->SetVisibility(false);
}

// Called when the game starts or when spawned
void AWatcher::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &AWatcher::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &AWatcher::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &AWatcher::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &AWatcher::EyeBeamAttack);  // bind the attack function to the OnReachedTarget event
}

// Called every frame
void AWatcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Draw Debug Cylinder on Map
	if (Target->MapControl)
	{
		FVector DebugStart = GetActorLocation();
		FVector DebugEnd = FVector(DebugStart.X, DebugStart.Y, (DebugStart.Z + 500));

		DrawDebugCylinder(GetWorld(), DebugStart, DebugEnd, 10, 12, FColor::Red, false, 0, 0);
	}
}

// Eye Beam Attack
void AWatcher::EyeBeamAttack()
{
	if (!IsDead)
	{
		if (!Target->IsDead)
		{
			RunAI = false;
			Attack = true; // this triggers the watcher's attack animation
			PreAtkAudio->Play();
			BeamDecal->SetVisibility(true);
			EnemyDealDamage(35);

			FTimerHandle DestroyTimer;
			GetWorldTimerManager().SetTimer(DestroyTimer, this, &AWatcher::StartBlast, 2.4f, false);	
		}
	}
}

// Start Eye Beam Blast
void AWatcher::StartBlast()
{
	EyeBeamBlast->Activate();  // activate the beam blast
	Blasting = true;
	BeamAudio->Play();

	TArray<AActor*> Overlapping;  // define a local array to store hits
	BeamBox->GetOverlappingActors(Overlapping, AEtherealPlayerMaster::StaticClass()); // check for overlapping players within the blast radius

	for (AActor* Actor : Overlapping) // for each actor found overlapping
	{
		AEtherealPlayerMaster* Player = Cast<AEtherealPlayerMaster>(Actor);  // cast to Player Master

		if (Player) // if succeeded
		{
			Player->PlayerTakeDamage(DamageOutput);  // have the player take damage
			Player->EtherealPlayerController->ActivateStatus_Burn();  // BURN STATUS
		}
	}

	FTimerHandle DestroyTimer;
	GetWorldTimerManager().SetTimer(DestroyTimer, this, &AWatcher::StopBlast, 1.0f, false);
}

// Stop Eye Beam Blast
void AWatcher::StopBlast()
{
	EyeBeamBlast->Deactivate();
	Blasting = false;
	BeamDecal->SetVisibility(false);

	// Restart the Attack Cycle after a short delay
	FTimerHandle DestroyTimer;
	GetWorldTimerManager().SetTimer(DestroyTimer, this, &AEtherealEnemyMaster::RunToTarget, AttackDelay, false);
}

void AWatcher::Death()
{
	DeathAudio->Play();
	//Target->EtherealPlayerState->EnemyKillReward(Level, CommonDrop, UncommonDrop, RareDrop);  // reward the player for killing this enemy
}

void AWatcher::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
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

void AWatcher::OnSeePawn(APawn* Pawn)
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
