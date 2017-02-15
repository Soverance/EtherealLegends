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
#include "Goblin.h"

#define LOCTEXT_NAMESPACE "EtherealText"

AGoblin::AGoblin(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/EtherealParty/Goblin/ShortGoblin.ShortGoblin'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/Goblin/Goblin_AnimBP.Goblin_AnimBP_C'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> AttackAudioObject(TEXT("SoundCue'/Game/Audio/Party/Goblin_Atk_Cue.Goblin_Atk_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DeathAudioObject(TEXT("SoundCue'/Game/Audio/Party/Goblin_Death_Cue.Goblin_Death_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> HitAudioObject(TEXT("SoundCue'/Game/Audio/Party/Goblin_hit_Cue.Goblin_hit_Cue'"));

	// Set Default Objects
	S_AttackAudio = AttackAudioObject.Object;
	S_DeathAudio = DeathAudioObject.Object;
	S_HitAudio = HitAudioObject.Object;
	
	// Default Config
	Name = EEnemyNames::EN_Goblin;
	NameText = LOCTEXT("GoblinText", "Goblin");
	Realm = ERealms::R_Vulcan;
	BattleType = EBattleTypes::BT_Standard;
	CommonDrop = EMasterGearList::GL_None;
	UncommonDrop = EMasterGearList::GL_HiPotion;
	RareDrop = EMasterGearList::GL_SentinelBrew;
	AttackDelay = 2.0f;
	BaseEyeHeight = 10;
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
	MeleeRadius->SetRelativeLocation(FVector(75, 0, 0));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 100));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	
	// Death FX Config
	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
	
	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Enemy-Specific Object Config
	AttackAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("AttackAudio"));
	AttackAudio->Sound = S_AttackAudio;
	AttackAudio->bAutoActivate = false;
	AttackAudio->SetupAttachment(RootComponent);
	
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
void AGoblin::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &AGoblin::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &AGoblin::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &AGoblin::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &AGoblin::MeleeAttack);  // bind the attack function to the OnReachedTarget event
}

// Called every frame
void AGoblin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Melee Attack function
void AGoblin::MeleeAttack()
{
	EnemyDealDamage(25);
	Attack = true;
}

void AGoblin::Death()
{
	DeathAudio->Play();  // Play death audio
	//Target->EtherealPlayerState->EnemyKillReward(Level, CommonDrop, UncommonDrop, RareDrop);  // reward the player for killing this enemy
}

// A.I. Hearing
void AGoblin::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
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
void AGoblin::OnSeePawn(APawn* Pawn)
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
