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
#include "Widgets/Tutorial.h"
#include "UndeadWarrior.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AUndeadWarrior::AUndeadWarrior(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/EtherealParty/Skeleton/mSkeleton.mSkeleton'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/Skeleton/Skeleton_AnimBP.Skeleton_AnimBP_C'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DeathAudioObject(TEXT("SoundCue'/Game/Audio/Party/SoulEater_Death_Cue.SoulEater_Death_Cue'"));

	S_DeathAudio = DeathAudioObject.Object;

	// Default Config
	Name = EEnemyNames::EN_UndeadWarrior;
	NameText = LOCTEXT("UndeadWarriorText", "Undead Warrior");
	Realm = ERealms::R_Arcadia;
	BattleType = EBattleTypes::BT_Standard;
	CommonDrop = EMasterGearList::GL_None;
	UncommonDrop = EMasterGearList::GL_Potion;
	RareDrop = EMasterGearList::GL_Ether;
	AttackDelay = 2.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	GetCharacterMovement()->MaxAcceleration = 30;
	GetCharacterMovement()->RotationRate = FRotator(0, 5, 0);  // seems to do nothing?

	// Pawn A.I. config
	PawnSensing->HearingThreshold = 400;
	PawnSensing->LOSHearingThreshold = 500;
	PawnSensing->SightRadius = 500;
	PawnSensing->SetPeripheralVisionAngle(40.0f);
	AcceptanceRadius = 50.0f;
	RunAI = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(1, 1, 1));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// Melee Radius Config
	MeleeRadius->SetSphereRadius(100);
	MeleeRadius->SetRelativeLocation(FVector(50, 0, 0));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 215));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	// Death FX Config
	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
	HitFX->SetRelativeLocation(FVector(0, 0, 40));
	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Enemy-Specific Object Config
	DeathAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DeathAudio"));
	DeathAudio->Sound = S_DeathAudio;
	DeathAudio->bAutoActivate = false;
	DeathAudio->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AUndeadWarrior::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &AUndeadWarrior::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &AUndeadWarrior::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &AUndeadWarrior::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &AUndeadWarrior::MeleeAttack);  // bind the attack function to the OnReachedTarget event

	// Get the Gatekeeper actor, so this enemy has a reference to it for tutorial progression
	for (TActorIterator<AGatekeeper> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Gatekeeper = *ActorItr; // get the instance of the Gatekeeper actor
	}
}

// Called every frame
void AUndeadWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUndeadWarrior::MeleeAttack()
{
	EnemyDealDamage(15);
	Attack = true;
}

void AUndeadWarrior::Death()
{
	DeathAudio->Play();  // Play death audio
	//Target->EtherealPlayerState->EnemyKillReward(Level, CommonDrop, UncommonDrop, RareDrop);  // reward the player for killing this enemy
	
	if (!Target->EtherealPlayerState->HasCompletedTutorial)  // don't bother running this code if the player has completed the tutorial
	{
		if (Gatekeeper)  // be sure Gatekeeper reference isn't NULL
		{
			if (Gatekeeper->Tutorial)  // be sure the Tutorial widget isn't NULL
			{
				if (Target->AggroList.Num() == 0)  // only progress with this function if the aggro list is empty
				{
					if (Gatekeeper->Tutorial->TutorialIndex == 2)  // you killed this enemy while on the proper TutorialIndex, so we progress the Tutorial
					{
						FTimerHandle ConvoTimer;
						GetWorldTimerManager().SetTimer(ConvoTimer, this, &AUndeadWarrior::ShowTutorialConvo, 2.5f, false);
					}
				}				
			}
		}
	}	
}

void AUndeadWarrior::ShowTutorialConvo()
{
	Gatekeeper->Tutorial->ShowConversation_05();  // show the Consumable Item tutorial panel
}

void AUndeadWarrior::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			//Aggro(PawnInstigator);

			IsAggroed = true;

			// Delay Aggro so the skeleton can get up from the ground
			FTimerDelegate DelegateAggro;
			DelegateAggro.BindUFunction(this, FName("Aggro"), PawnInstigator);
			FTimerHandle AggroTimer;
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 2.5f, false);
		}
	}
}

void AUndeadWarrior::OnSeePawn(APawn* Pawn)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			//Aggro(Pawn);

			IsAggroed = true;

			// Delay Aggro so the skeleton can get up from the ground
			FTimerDelegate DelegateAggro;
			DelegateAggro.BindUFunction(this, FName("Aggro"), Pawn);
			FTimerHandle AggroTimer;
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 2.5f, false);
		}
	}
}

#undef LOCTEXT_NAMESPACE
