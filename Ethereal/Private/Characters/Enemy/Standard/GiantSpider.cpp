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
#include "GiantSpider.h"

#define LOCTEXT_NAMESPACE "EtherealText"

AGiantSpider::AGiantSpider(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/InfinityBladeAdversaries/Enemy/Enemy_Great_Spider/SK_Greater_Spider.SK_Greater_Spider'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/InfinityBladeAdversaries/Enemy/Enemy_Great_Spider/Anim_GiantSpider.Anim_GiantSpider_C'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> SpiderVomitParticle(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Troll/Poison/P_Troll_Poison_Vomit_01.P_Troll_Poison_Vomit_01'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> VomitAudioObject(TEXT("SoundCue'/Game/Audio/Party/GiantSpider_AtkSpit_Cue.GiantSpider_AtkSpit_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DeathAudioObject(TEXT("SoundCue'/Game/Audio/Party/GiantSpider_Death_Cue.GiantSpider_Death_Cue'"));

	// Set Default Objects
	P_SpiderVomit = SpiderVomitParticle.Object;
	S_VomitAudio = VomitAudioObject.Object;
	S_DeathAudio = DeathAudioObject.Object;

	// Default Config
	Name = EEnemyNames::EN_GiantSpider;
	NameText = LOCTEXT("GiantSpiderText", "Giant Spider");
	Realm = ERealms::R_Boreal;
	BattleType = EBattleTypes::BT_Standard;
	CommonDrop = EMasterGearList::GL_Ether;
	UncommonDrop = EMasterGearList::GL_HiEther;
	RareDrop = EMasterGearList::GL_SentinelBrew;
	AttackDelay = 2.0f;
	BaseEyeHeight = -50;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(1, 1, 1));
	GetCharacterMovement()->MaxAcceleration = 30;

	IsAttacking = false;
	DoSpit = false;
	DoMelee1 = false;
	DoMelee2 = false;

	// Pawn A.I. config
	PawnSensing->HearingThreshold = 300;
	PawnSensing->LOSHearingThreshold = 350;
	PawnSensing->SightRadius = 450;
	PawnSensing->SetPeripheralVisionAngle(40.0f);
	AcceptanceRadius = 100.0f;
	RunAI = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(75);
	MeleeRadius->SetRelativeLocation(FVector(50, 0, -75));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 200));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	
	// FX Config
	HitFX->SetRelativeLocation(FVector(0, 0, -40));

	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	
	DisappearFX->SetRelativeLocation(FVector(0, 0, -40));
	DisappearFX->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));

	// Enemy-Specific Object Config
	SpiderVomit = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("SpiderVomit"));
	SpiderVomit->Template = P_SpiderVomit;
	SpiderVomit->bAutoActivate = false;
	SpiderVomit->bAutoManageAttachment = true;
	SpiderVomit->SetupAttachment(GetMesh(), FName("VomitSocket"));
	SpiderVomit->SetRelativeLocation(FVector(0, 0, 0));

	VomitAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("VomitAudio"));
	VomitAudio->Sound = S_VomitAudio;
	VomitAudio->bAutoActivate = false;
	VomitAudio->SetupAttachment(RootComponent);
	
	DeathAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DeathAudio"));
	DeathAudio->Sound = S_DeathAudio;	
	DeathAudio->bAutoActivate = false;
	DeathAudio->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGiantSpider::BeginPlay()
{
	Super::BeginPlay();

	SpiderVomit->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("VomitSocket"));

	PawnSensing->OnHearNoise.AddDynamic(this, &AGiantSpider::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &AGiantSpider::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &AGiantSpider::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &AGiantSpider::MeleeAttack);  // bind the attack function to the OnReachedTarget event
}

// Called every frame
void AGiantSpider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Melee Attack function
void AGiantSpider::MeleeAttack()
{
	if (!Target->IsDead)
	{
		if (!IsAttacking)
		{
			IsAttacking = true;

			int32 RandomAtk = FMath::RandRange(0, 7);  // get a random int

			if (!IsDead)
			{
				if (RandomAtk <= 2)
				{
					EnemyDealDamage(45);
					DoMelee1 = true;
				}
				if (RandomAtk > 2 && RandomAtk <= 4)
				{
					EnemyDealDamage(45);
					DoMelee2 = true;
				}
				if (RandomAtk > 4)
				{
					EnemyDealDamage(25);
					DoSpit = true;
				}
			}

			// Restart the Attack Cycle after a short delay
			FTimerHandle EndTimer;
			GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
		}
	}	
}

void AGiantSpider::Death()
{
	IsDead = true;
	DeathAudio->Play();
}

// A.I. Hearing
void AGiantSpider::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
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
void AGiantSpider::OnSeePawn(APawn* Pawn)
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
