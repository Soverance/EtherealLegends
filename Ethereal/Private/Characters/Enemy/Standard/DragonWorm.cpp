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
#include "Kismet/KismetMathLibrary.h"
#include "DragonWorm.h"

#define LOCTEXT_NAMESPACE "EtherealText"

ADragonWorm::ADragonWorm(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/EtherealParty/DragonWorm/DragonWorm.DragonWorm'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/DragonWorm/Worm_Anim.Worm_Anim_C'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> RockBaseMesh(TEXT("StaticMesh'/Game/SenzaPeso/MASTERALL/StaticMeshes/SK_LavaPillar_03.SK_LavaPillar_03'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> LavaBlobMesh(TEXT("StaticMesh'/Game/SenzaPeso/MASTERALL/StaticMeshes/SM_LavaBlob_01.SM_LavaBlob_01'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AggroFlareParticle(TEXT("ParticleSystem'/Game/Elemental/Effects/Fx_Magic/Effects/DragonWorm_AggroFlare.DragonWorm_AggroFlare'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> AggroAudioObject(TEXT("SoundCue'/Game/Audio/Party/DragonWorm_Aggro_Cue.DragonWorm_Aggro_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> SpitAudioObject(TEXT("SoundCue'/Game/Audio/Party/DragonWorm_Spit_Cue.DragonWorm_Spit_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DeathAudioObject(TEXT("SoundCue'/Game/Audio/Party/DragonWorm_Death_Cue.DragonWorm_Death_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> HitAudioObject(TEXT("SoundCue'/Game/Audio/Party/DragonWorm_Hit_Cue.DragonWorm_Hit_Cue'"));

	// Set Default Objects
	SM_RockBase = RockBaseMesh.Object;
	SM_LavaBlob = LavaBlobMesh.Object;
	P_AggroFlare = AggroFlareParticle.Object;
	S_AggroAudio = AggroAudioObject.Object;
	S_SpitAudio = SpitAudioObject.Object;
	S_DeathAudio = DeathAudioObject.Object;
	S_HitAudio = HitAudioObject.Object;

	// Default Config
	Name = EEnemyNames::EN_DragonWorm;
	NameText = LOCTEXT("DragonWormText", "Dragon Worm");
	Realm = ERealms::R_Vulcan;
	BattleType = EBattleTypes::BT_Standard;
	CommonDrop = EMasterGearList::GL_Potion;
	UncommonDrop = EMasterGearList::GL_Ether;
	RareDrop = EMasterGearList::GL_Reraise;
	AttackDelay = 2.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	GetCharacterMovement()->MaxAcceleration = 0;

	IsAttacking = false;
	DoSpit = false;
	DoSwing = false;
	
	// Pawn A.I. config
	PawnSensing->HearingThreshold = 300;
	PawnSensing->LOSHearingThreshold = 400;
	PawnSensing->SightRadius = 400;
	PawnSensing->SetPeripheralVisionAngle(50.0f);
	AcceptanceRadius = 200.0f;
	RunAI = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(2, 2, 2));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(400);
	MeleeRadius->SetRelativeLocation(FVector(0, 0, -90));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 160));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	
	HitFX->SetRelativeLocation(FVector(0, 0, 300));

	// Death FX Config
	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(1.4f, 1.4f, 1.4f));
	
	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Enemy-Specific Object Config
	// configure Custom Hit Radius - this is here so the player can hit the RockBase and still score damage on the enemy
	CustomHitRadius = CreateDefaultSubobject<USphereComponent>(TEXT("CustomHitRadius"));
	CustomHitRadius->SetupAttachment(GetMesh());
	CustomHitRadius->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//CustomHitRadius->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	CustomHitRadius->SetSphereRadius(180);
	CustomHitRadius->SetRelativeLocation(FVector(0, 0, -90));

	RockBase = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("RockBase"));
	RockBase->SetStaticMesh(SM_RockBase);
	RockBase->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RockBase->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	RockBase->SetRelativeRotation(FRotator(180, 0, 0));
	RockBase->SetupAttachment(RootComponent);
	
	LavaBlob = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("LavaBlob"));
	LavaBlob->SetStaticMesh(SM_LavaBlob);
	LavaBlob->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LavaBlob->SetupAttachment(RockBase);
	LavaBlob->SetRelativeScale3D(FVector(15, 15, 15));
	LavaBlob->SetRelativeRotation(FRotator(0, 0, 180));
	LavaBlob->SetVisibility(false);
	
	AggroFlare = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("AggroFlare"));
	AggroFlare->Template = P_AggroFlare;
	AggroFlare->bAutoActivate = false;
	AggroFlare->SetupAttachment(RootComponent);
	AggroFlare->SetRelativeScale3D(FVector(0.6f, 0.6f, 0.6f));
	
	AggroAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("AggroAudio"));
	AggroAudio->Sound = S_AggroAudio;
	AggroAudio->bAutoActivate = false;
	AggroAudio->SetupAttachment(RootComponent);
	
	SpitAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SpitAudio"));
	SpitAudio->Sound = S_SpitAudio;
	SpitAudio->bAutoActivate = false;
	SpitAudio->SetupAttachment(RootComponent);
	
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
void ADragonWorm::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &ADragonWorm::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &ADragonWorm::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &ADragonWorm::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &ADragonWorm::StartAttackCycle);  // bind the attack function to the OnReachedTarget event

	RockBase->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}

// Called every frame
void ADragonWorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADragonWorm::StartAttackCycle()
{
	if (!Target->IsDead)
	{
		if (!IsAttacking)
		{
			IsAttacking = true;

			TArray<AActor*> Overlapping;  // define a local array to store hits
			MeleeRadius->GetOverlappingActors(Overlapping, AEtherealPlayerMaster::StaticClass()); // check for overlapping players within the stomp radius

			if (Overlapping.Num() > 0)
			{
				for (AActor* Actor : Overlapping) // for each actor found overlapping
				{
					AEtherealPlayerMaster* Player = Cast<AEtherealPlayerMaster>(Actor);  // cast to Player Master

					if (Player) // if succeeded
					{
						Target = Player;
						EnemyDealDamage(60);
						DoSwing = true;  // if the player is inside the melee radius, do the melee swing attack
					}
				}
			}

			if (Overlapping.Num() == 0)
			{
				EnemyDealDamage(50);
				DoSpit = true;  // the player is outside the melee radius, so spit a fireball at him
			}

			// Restart the Attack Cycle after a short delay
			FTimerHandle EndTimer;
			GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
		}
	}
	// The rest of this code is inside this enemy's AnimBP
}

void ADragonWorm::Death()
{
	DeathAudio->Play();
	IsDead = true;
	LavaBlob->SetVisibility(false);
}

// Worm Aggro. Makes the worm appear from beneath the rock base
void ADragonWorm::WormAggro()
{
	//IsAggroed = true;
	AggroFlare->Activate(true);
	AggroAudio->Play();
	LavaBlob->SetVisibility(true);
}

// Deaggro worm.  Makes the worm disappear back underneath the rock base.
void ADragonWorm::WormDeaggro()
{
	IsAggroed = false;
	AggroFlare->Deactivate();
	LavaBlob->SetVisibility(false);
}

// A.I. Hearing
void ADragonWorm::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
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
void ADragonWorm::OnSeePawn(APawn* Pawn)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			WormAggro();
			Aggro(Pawn);
			RunToTarget();
		}
	}	
}

#undef LOCTEXT_NAMESPACE
