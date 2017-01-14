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
#include "Gruntling.h"

#define LOCTEXT_NAMESPACE "EtherealText"

AGruntling::AGruntling(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/InfinityBladeAdversaries/Enemy/Enemy_Gruntling/SK_Exodus_Gruntling.SK_Exodus_Gruntling'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/InfinityBladeAdversaries/Enemy/Enemy_Gruntling/Anim_EggGrunt.Anim_EggGrunt_C'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> AppearAudioObject(TEXT("SoundCue'/Game/Audio/Gruntling/Gruntling_Appear_Cue.Gruntling_Appear_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> CastAudioObject(TEXT("SoundCue'/Game/Audio/Gruntling/Gruntling_Cast_Cue.Gruntling_Cast_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DeathAudioObject(TEXT("SoundCue'/Game/Audio/Gruntling/Gruntling_Death_Cue.Gruntling_Death_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> HitAudioObject(TEXT("SoundCue'/Game/Audio/Gruntling/Gruntling_Hit_Cue.Gruntling_Hit_Cue'"));
	static ConstructorHelpers::FObjectFinder<UClass> BombBlueprintObject(TEXT("Blueprint'/Game/Blueprints/Characters/Enemy/2-VulcanShrine/GruntlingDrop.GruntlingDrop_C'"));

	// Set Default Objects
	S_AppearAudio = AppearAudioObject.Object;
	S_CastAudio = CastAudioObject.Object;
	S_DeathAudio = DeathAudioObject.Object;
	S_HitAudio = HitAudioObject.Object;	
	FirebombBP = BombBlueprintObject.Object; 
	
	// Default Config
	Name = EEnemyNames::EN_Gruntling;
	NameText = LOCTEXT("GruntlingText", "Gruntling");
	Realm = ERealms::R_Vulcan;
	BattleType = EBattleTypes::BT_Standard;
	CommonDrop = EMasterGearList::GL_None;
	UncommonDrop = EMasterGearList::GL_HiEther;
	RareDrop = EMasterGearList::GL_Adrenaline;
	AttackDelay = 2.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	GetCharacterMovement()->MaxAcceleration = 60;
	
	// Pawn A.I. config
	PawnSensing->HearingThreshold = 150;
	PawnSensing->LOSHearingThreshold = 200;
	PawnSensing->SightRadius = 250;
	PawnSensing->SetPeripheralVisionAngle(40.0f);
	AcceptanceRadius = 25.0f;
	RunAI = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(2, 2, 2));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(100);
	MeleeRadius->SetRelativeLocation(FVector(15, 0, 0));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 130));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	
	// Death FX Config
	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
	
	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Enemy-Specific Object Config
	AppearAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("AppearAudio"));
	AppearAudio->Sound = S_AppearAudio;
	AppearAudio->bAutoActivate = false;
	AppearAudio->SetupAttachment(RootComponent);
	
	CastAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("CastAudio"));
	CastAudio->Sound = S_CastAudio;
	CastAudio->bAutoActivate = false;
	CastAudio->SetupAttachment(RootComponent);
	
	DeathAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DeathAudio"));
	DeathAudio->Sound = S_DeathAudio;
	DeathAudio->bAutoActivate = false;
	DeathAudio->SetupAttachment(RootComponent);
	
	HitAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("HitAudio"));
	HitAudio->Sound = S_HitAudio;
	HitAudio->bAutoActivate = false;
	HitAudio->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGruntling::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &AGruntling::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &AGruntling::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &AGruntling::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &AGruntling::MeleeAttack);  // bind the attack function to the OnReachedTarget event
}

// Called every frame
void AGruntling::Tick(float DeltaTime)
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

// Melee Attack function
void AGruntling::MeleeAttack()
{
	if (!Attack)
	{
		EnemyDealDamage(25);
		Attack = true;

		// Firebomb the Player!
		AActor* Firebomb = UCommonLibrary::SpawnBP(GetWorld(), FirebombBP, Target->GetActorLocation(), Target->GetActorRotation());
	}	
}

// Death function
void AGruntling::Death()
{
	DeathAudio->Play();  // Play death audio
	//Target->EtherealPlayerState->EnemyKillReward(Level, CommonDrop, UncommonDrop, RareDrop);  // reward the player for killing this enemy
}

// A.I. Hearing
void AGruntling::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
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
void AGruntling::OnSeePawn(APawn* Pawn)
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
