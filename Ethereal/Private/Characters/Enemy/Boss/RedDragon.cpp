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
#include "RedDragon.h"

#define LOCTEXT_NAMESPACE "EtherealText"

ARedDragon::ARedDragon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/EtherealParty/Dragon/dragon_skin.dragon_skin'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/Dragon/Anim_RedDragon.Anim_RedDragon_C'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> BreathAudioObject(TEXT("SoundCue'/Game/EtherealParty/Dragon/Audio/Dragon_FireBreath_Cue.Dragon_FireBreath_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> TailWhipAudioObject(TEXT("SoundCue'/Game/EtherealParty/Dragon/Audio/Dragon_TailWhip_Cue.Dragon_TailWhip_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> FlapAudioObject(TEXT("SoundCue'/Game/EtherealParty/Dragon/Audio/Dragon_Flap_Cue.Dragon_Flap_Cue'"));

	// Set Default Objects
	S_BreathAudio = BreathAudioObject.Object;
	S_TailWhipAudio = TailWhipAudioObject.Object;
	S_FlapAudio = FlapAudioObject.Object;
	
	// Default Config
	Name = EEnemyNames::EN_RedDragon;
	NameText = LOCTEXT("RedDragonText", "RedDragon");
	Realm = ERealms::R_Vulcan;
	BattleType = EBattleTypes::BT_Boss;
	CommonDrop = EMasterGearList::GL_Elixer;
	UncommonDrop = EMasterGearList::GL_Claymore;
	RareDrop = EMasterGearList::GL_EagleEye;
	AttackDelay = 2.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.6f, 0.6f, 0.6f));
	GetCharacterMovement()->MaxAcceleration = 30;
	
	// Pawn A.I. config
	PawnSensing->HearingThreshold = 200;
	PawnSensing->LOSHearingThreshold = 250;
	PawnSensing->SightRadius = 400;
	PawnSensing->SetPeripheralVisionAngle(50.0f);
	AcceptanceRadius = 200.0f;
	RunAI = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(2, 2, 2));
	GetMesh()->SetRelativeLocation(FVector(-50, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(100);
	MeleeRadius->SetRelativeLocation(FVector(150, 0, -50));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 25, 75));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	
	// FX Config
	HitFX->SetRelativeLocation(FVector(150, 0, 0));

	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
	
	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Enemy-Specific Object Config
	HitBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("HitBox"));
	HitBox->SetupAttachment(GetMesh());
	HitBox->SetRelativeLocation(FVector(0, 20, 0));
	HitBox->SetBoxExtent(FVector(20, 40, 40));
	HitBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	MeleeRadius_Tail = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("MeleeRadius_Tail"));
	MeleeRadius_Tail->SetupAttachment(RootComponent);
	MeleeRadius_Tail->SetRelativeLocation(FVector(-200, 0, -50));
	MeleeRadius_Tail->SetBoxExtent(FVector(125, 40, 60));
	MeleeRadius_Tail->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleeRadius_Tail->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	MeleeRadius_Breath = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("MeleeRadius_Breath"));
	MeleeRadius_Breath->SetupAttachment(RootComponent);
	MeleeRadius_Breath->SetRelativeLocation(FVector(350, 0, -50));
	MeleeRadius_Breath->SetBoxExtent(FVector(200, 40, 60));
	MeleeRadius_Breath->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleeRadius_Breath->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	
	BreathAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BreathAudio"));
	BreathAudio->Sound = S_BreathAudio;
	BreathAudio->bAutoActivate = false;
	BreathAudio->SetupAttachment(RootComponent);
	
	TailWhipAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("TailWhipAudio"));
	TailWhipAudio->Sound = S_TailWhipAudio;
	TailWhipAudio->bAutoActivate = false;
	TailWhipAudio->SetupAttachment(RootComponent);
	
	FlapAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("FlapAudio"));
	FlapAudio->Sound = S_FlapAudio;
	FlapAudio->bAutoActivate = false;
	FlapAudio->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARedDragon::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &ARedDragon::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &ARedDragon::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &ARedDragon::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &ARedDragon::AttackCycle);  // bind the attack function to the OnReachedTarget event 

	// Get the placement actor, so this enemy has a reference to the flight spline
	for (TActorIterator<ARedDragon_Placement> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Placement = *ActorItr; // get the instance of the Placement actor
	}
}

// Called every frame
void ARedDragon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Draw Debug Cylinder on Map
	if (Target->MapControl)
	{
		FVector DebugStart = GetActorLocation();
		FVector DebugEnd = FVector(DebugStart.X, DebugStart.Y, (DebugStart.Z + 1500));

		DrawDebugCylinder(GetWorld(), DebugStart, DebugEnd, 10, 12, FColor::Yellow, false, 0, 0);
	}
}

// Melee Attack function
void ARedDragon::AttackCycle()
{
	if (!Target->IsDead)
	{
		if (!IsAttacking)
		{
			IsAttacking = true;
			ResetAnims();

			TArray<AActor*> OverlappingBreath;  // define a local array to store hits
			MeleeRadius->GetOverlappingActors(OverlappingBreath, AEtherealPlayerMaster::StaticClass()); // check for overlapping players within the radius

			if (OverlappingBreath.Num() > 0)
			{
				for (AActor* Actor : OverlappingBreath) // for each actor found overlapping
				{
					AEtherealPlayerMaster* Player = Cast<AEtherealPlayerMaster>(Actor);  // cast to Player Master

					if (Player) // if succeeded
					{
						Target = Player;
						EnemyDealDamage(60);
						FireBreath();
					}
				}
			}

			TArray<AActor*> OverlappingTail;  // define a local array to store hits
			MeleeRadius_Tail->GetOverlappingActors(OverlappingTail, AEtherealPlayerMaster::StaticClass()); // check for overlapping players within the radius

			if (OverlappingTail.Num() > 0)
			{
				for (AActor* Actor : OverlappingTail) // for each actor found overlapping
				{
					AEtherealPlayerMaster* Player = Cast<AEtherealPlayerMaster>(Actor);  // cast to Player Master

					if (Player) // if succeeded
					{
						Target = Player;
						EnemyDealDamage(60);
						TailSwipe();
					}
				}
			}

			// Restart the Attack Cycle after a short delay
			FTimerHandle EndTimer;
			GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
		}
	}	
}

void ARedDragon::Death()
{
	
}

void ARedDragon::ResetAnims()
{
	IsHit = false;
	DoBreath = false;
	DoSwipe = false;
}

void ARedDragon::DetermineFlight()
{
	if (FlightCount < 2)
	{
		if (InFlight == false)
		{
			switch (FlightCount)
			{
				case 0:
					if (HP_Current < (HP_Max * 0.75f))
					{
						FlightCount = 1;
						TakeFlight();
					}
					break;
				case 1:
					if (HP_Current < (HP_Max * 0.50f))
					{
						FlightCount = 2;
						TakeFlight();
					}
					break;
				case 2:
					if (HP_Current < (HP_Max * 0.25f))
					{
						FlightCount = 3;
						TakeFlight();
					}
					break;
			}
		}
	}
}

void ARedDragon::TakeFlight()
{
	ResetAnims();
	Targetable = false;
	
	if (!IsDead)
	{
		//Placement->FollowSpline(this);
		EnemyDealDamage(40);
		FastFlap = true;
		// TO DO : Spawn Boss Worms
	}
}

void ARedDragon::FireBreath()
{
	EnemyDealDamage(35);
	DoBreath = true;

	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void ARedDragon::TailSwipe()
{
	EnemyDealDamage(45);
	DoSwipe = true;

	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void ARedDragon::FollowSplineInFlight()
{
	if (InFlight)
	{
		DistanceOnSpline = DistanceOnSpline + 12;
		// TO DO :  Get distance along spline, world space coordinates, and set the actor location accordingly
		// TO DO :  Get rotation at distance along spline, world coordinate space, and set actor rotation accordingly

		// TO DO : DECAL TRIGGERS and BREATH IN FLIGHT and END FLIGHT / LAND
	}
}

// A.I. Hearing
void ARedDragon::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			EtherealGameInstance->BlackBox->HasEngagedBoss = true;  // Engage Boss
			Aggro(PawnInstigator);
			RunToTarget();
		}
	}
}

// A.I. Sight
void ARedDragon::OnSeePawn(APawn* Pawn)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			EtherealGameInstance->BlackBox->HasEngagedBoss = true;  // Engage Boss
			Aggro(Pawn);
			RunToTarget();
		}
	}	
}

#undef LOCTEXT_NAMESPACE
