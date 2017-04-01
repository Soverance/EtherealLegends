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
#include "Mugbear.h"

#define LOCTEXT_NAMESPACE "EtherealText"

AMugbear::AMugbear(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/InfinityBladeAdversaries/Enemy/Enemy_Bear/Enemy_Bear.Enemy_Bear'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/InfinityBladeAdversaries/Enemy/Enemy_Bear/Anim_Bear.Anim_Bear_C'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> SlamAudioObject(TEXT("SoundCue'/Game/Audio/Party/Mugbear_SlamAtk_Cue.Mugbear_SlamAtk_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> RoarAudioObject(TEXT("SoundCue'/Game/Audio/Party/FrostCaptain_StompRoar_Cue.FrostCaptain_StompRoar_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DeathAudioObject(TEXT("SoundCue'/Game/Audio/Party/Mugbear_Death_Cue.Mugbear_Death_Cue'"));

	// Set Default Objects
	S_SlamAudio = SlamAudioObject.Object;
	S_RoarAudio = RoarAudioObject.Object;
	S_DeathAudio = DeathAudioObject.Object;

	// Default Config
	Name = EEnemyNames::EN_Mugbear;
	NameText = LOCTEXT("MugbearText", "Mugbear");
	Realm = ERealms::R_Yggdrasil;
	BattleType = EBattleTypes::BT_Standard;
	CommonDrop = EMasterGearList::GL_EchoHerb;
	UncommonDrop = EMasterGearList::GL_HiEther;
	RareDrop = EMasterGearList::GL_Adrenaline;
	AttackDelay = 2.0f;
	BaseEyeHeight = -50;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(1, 1, 1));
	GetCharacterMovement()->MaxAcceleration = 30;

	// Pawn A.I. config
	PawnSensing->HearingThreshold = 150;
	PawnSensing->LOSHearingThreshold = 200;
	PawnSensing->SightRadius = 250;
	PawnSensing->SetPeripheralVisionAngle(40.0f);
	AcceptanceRadius = 150.0f;
	RunAI = false;

	DoSwingLeft = false;
	DoSwingRight = false;
	DoThrow = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(50);
	MeleeRadius->SetRelativeLocation(FVector(30, 0, -75));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 200));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	
	// FX Config
	HitFX->SetRelativeLocation(FVector(0, 0, -50));
	HitFX->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	DeathFX->SetRelativeLocation(FVector(0, 0, -88));
	DeathFX->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	
	DisappearFX->SetRelativeLocation(FVector(0, 0, -60));
	DisappearFX->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));

	// Enemy-Specific Object Config
	SlamAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SlamAudio"));
	SlamAudio->Sound = S_SlamAudio;
	SlamAudio->bAutoActivate = false;
	SlamAudio->SetupAttachment(RootComponent);
	
	RoarAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("RoarAudio"));
	RoarAudio->Sound = S_RoarAudio;
	RoarAudio->bAutoActivate = false;
	RoarAudio->SetupAttachment(RootComponent);
	
	DeathAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DeathAudio"));
	DeathAudio->Sound = S_DeathAudio;
	DeathAudio->bAutoActivate = false;
	DeathAudio->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMugbear::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &AMugbear::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &AMugbear::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &AMugbear::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &AMugbear::MeleeAttack);  // bind the attack function to the OnReachedTarget event
}

// Called every frame
void AMugbear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Melee Attack function
void AMugbear::MeleeAttack()
{
	if (!Target->IsDead)
	{
		if (!IsAttacking)
		{
			IsAttacking = true;
			RunAI = false;

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

						int32 RandomAtk = FMath::RandRange(0, 4);  // get a random int

						if (!IsDead)
						{
							if (RandomAtk <= 2)
							{
								SwingLeft();
							}
							if (RandomAtk > 2 && RandomAtk <= 4)
							{
								SwingRight();
							}
						}
					}
				}
			}

			if (Overlapping.Num() == 0)
			{
				Throw();
			}
		}
	}
	// The rest of this code is inside this enemy's AnimBP
}

void AMugbear::Death()
{
	IsDead = true;
	DeathAudio->Play();
}

void AMugbear::SwingLeft()
{
	EnemyDealDamage(55);
	DoSwingLeft = true;
	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void AMugbear::SwingRight()
{
	EnemyDealDamage(55);
	DoSwingRight = true;
	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void AMugbear::Throw()
{
	EnemyDealDamage(70);
	DoThrow = true;
	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

// A.I. Hearing
void AMugbear::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
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
void AMugbear::OnSeePawn(APawn* Pawn)
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
