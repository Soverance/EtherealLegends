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
#include "Kismet/KismetMathLibrary.h"
#include "Flytrap.h"

#define LOCTEXT_NAMESPACE "EtherealText"

AFlytrap::AFlytrap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/EtherealParty/Elongata/Elongata.Elongata'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/Elongata/Flytrap_AnimBP.Flytrap_AnimBP_C'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FernBaseMesh(TEXT("StaticMesh'/Game/KiteDemo/Environments/Foliage/Ferns/SM_Fern_01.SM_Fern_01'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> AggroAudioObject(TEXT("SoundCue'/Game/Audio/Party/Flytrap_Aggro_Cue.Flytrap_Aggro_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> HitAudioObject(TEXT("SoundCue'/Game/Audio/Party/Flytrap_Hit_Cue.Flytrap_Hit_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> BiteAudioObject(TEXT("SoundCue'/Game/Audio/Party/Flytrap_Bite_Cue.Flytrap_Bite_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> SpitAudioObject(TEXT("SoundCue'/Game/Audio/Party/Flytrap_Spit_Cue.Flytrap_Spit_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DeathAudioObject(TEXT("SoundCue'/Game/Audio/Party/Flytrap_Death_Cue.Flytrap_Death_Cue'"));

	// Set Default Objects
	SM_FernBase = FernBaseMesh.Object;
	S_AggroAudio = AggroAudioObject.Object;
	S_HitAudio = HitAudioObject.Object;
	S_BiteAudio = BiteAudioObject.Object;
	S_SpitAudio = SpitAudioObject.Object;
	S_DeathAudio = DeathAudioObject.Object;

	// Default Config
	Name = EEnemyNames::EN_Flytrap;
	NameText = LOCTEXT("FlytrapText", "Flytrap");
	Realm = ERealms::R_Yggdrasil;
	BattleType = EBattleTypes::BT_Standard;
	CommonDrop = EMasterGearList::GL_Antidote;
	UncommonDrop = EMasterGearList::GL_HiPotion;
	RareDrop = EMasterGearList::GL_Elixer;
	AttackDelay = 2.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	GetCharacterMovement()->MaxAcceleration = 0;

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
	GetMesh()->SetRelativeScale3D(FVector(1.2f, 1.2f, 1.2f));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(100);
	MeleeRadius->SetRelativeLocation(FVector(60, 0, -75));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 150));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	
	// Death FX Config
	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
	
	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Enemy-Specific Object Config
	FernBase = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("FernBase"));
	FernBase->SetStaticMesh(SM_FernBase);
	FernBase->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	FernBase->SetRelativeLocation(FVector(0, 0, -90));
	FernBase->SetRelativeScale3D(FVector(1.2f, 1.2f, 0.7f));
	FernBase->SetupAttachment(RootComponent);
	
	AggroAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("AggroAudio"));
	AggroAudio->Sound = S_AggroAudio;
	AggroAudio->bAutoActivate = false;
	AggroAudio->SetupAttachment(RootComponent);
	
	HitAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("HitAudio"));
	HitAudio->Sound = S_HitAudio;
	HitAudio->bAutoActivate = false;
	HitAudio->SetupAttachment(RootComponent);
	
	BiteAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BiteAudio"));
	BiteAudio->Sound = S_BiteAudio;
	BiteAudio->bAutoActivate = false;
	BiteAudio->SetupAttachment(RootComponent);
	
	SpitAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SpitAudio"));
	SpitAudio->Sound = S_SpitAudio;
	SpitAudio->bAutoActivate = false;
	SpitAudio->SetupAttachment(RootComponent);
	
	DeathAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DeathAudio"));
	DeathAudio->Sound = S_DeathAudio;
	DeathAudio->bAutoActivate = false;
	DeathAudio->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFlytrap::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &AFlytrap::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &AFlytrap::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &AFlytrap::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &AFlytrap::MeleeAttack);  // bind the attack function to the OnReachedTarget event

	FernBase->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}

// Called every frame
void AFlytrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Melee Attack function
void AFlytrap::MeleeAttack()
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
						DoBite = true;  // if the player is inside the melee radius, do the melee bite attack
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

void AFlytrap::Death()
{
	IsDead = true;
	DeathAudio->Play();
}

void AFlytrap::LookAtTarget()
{
	FVector FlytrapLocation = this->GetActorLocation(); // GetFlytrap rotation
	FVector PlayerLocation = Target->GetActorLocation();  // get player location
	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(FlytrapLocation, PlayerLocation);  // find look at rotation
	FRotator CorrectedRot = FRotator(LookAtRot.Pitch, LookAtRot.Yaw - 90, LookAtRot.Roll);  // correct rotation
	this->SetActorRotation(CorrectedRot); // set rotation to the corrected rotation
}

// A.I. Hearing
void AFlytrap::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
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
void AFlytrap::OnSeePawn(APawn* Pawn)
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
