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
#include "Spider.h"

#define LOCTEXT_NAMESPACE "EtherealText"

ASpider::ASpider(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/InfinityBladeAdversaries/Enemy/Enemy_Creature_Spider/SK_EXO_Creature_Spider02.SK_EXO_Creature_Spider02'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/InfinityBladeAdversaries/Enemy/Enemy_Creature_Spider/Anim_Spider.Anim_Spider_C'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DeathAudioObject(TEXT("SoundCue'/Game/Audio/Party/Spider_Death_Cue.Spider_Death_Cue'"));

	// Set Default Objects
	S_DeathAudio = DeathAudioObject.Object;
	
	// Default Config
	Name = EEnemyNames::EN_Spider;
	NameText = LOCTEXT("SpiderText", "Spider");
	Realm = ERealms::R_Boreal;
	BattleType = EBattleTypes::BT_Standard;
	CommonDrop = EMasterGearList::GL_None;
	UncommonDrop = EMasterGearList::GL_Potion;
	RareDrop = EMasterGearList::GL_HiPotion;
	AttackDelay = 2.0f;
	BaseEyeHeight = -50;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(1, 1, 1));
	GetCharacterMovement()->MaxAcceleration = 30;

	// Pawn A.I. config
	PawnSensing->HearingThreshold = 300;
	PawnSensing->LOSHearingThreshold = 400;
	PawnSensing->SightRadius = 300;
	PawnSensing->SetPeripheralVisionAngle(40.0f);
	AcceptanceRadius = 40.0f;
	RunAI = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(50);
	MeleeRadius->SetRelativeLocation(FVector(30, 0, -85));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 100));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	
	// Death FX Config
	HitFX->SetRelativeLocation(FVector(0, 0, -60));
	HitFX->SetRelativeScale3D(FVector(0.6f, 0.6f, 0.6f));

	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	
	DisappearFX->SetRelativeLocation(FVector(0, 0, -60));
	DisappearFX->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	// Enemy-Specific Object Config
	DeathAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DeathAudio"));
	DeathAudio->Sound = S_DeathAudio;
	DeathAudio->bAutoActivate = false;
	DeathAudio->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpider::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &ASpider::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &ASpider::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &ASpider::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &ASpider::MeleeAttack);  // bind the attack function to the OnReachedTarget event
}

// Called every frame
void ASpider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Melee Attack function
void ASpider::MeleeAttack()
{
	EnemyDealDamage(25);
	DoAttack = true;
}

void ASpider::Death()
{
	IsDead = true;
	DeathAudio->Play();
}

// A.I. Hearing
void ASpider::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
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
void ASpider::OnSeePawn(APawn* Pawn)
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
