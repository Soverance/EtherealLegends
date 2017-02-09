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
#include "FrostCaptain.h"

#define LOCTEXT_NAMESPACE "EtherealText"

AFrostCaptain::AFrostCaptain(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/InfinityBladeAdversaries/Enemy/Enemy_Frost_Giant/SK_Enemy_FrostGiant_Captain.SK_Enemy_FrostGiant_Captain'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/InfinityBladeAdversaries/Enemy/Enemy_Frost_Giant/Anim_GiantCaptain.Anim_GiantCaptain_C'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> AggroAudioObject(TEXT("SoundCue'/Game/Audio/Party/FrostGiant_Aggro_Cue.FrostGiant_Aggro_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> HitAudioObject(TEXT("SoundCue'/Game/Audio/Party/FrostGiant_Aggro_Cue.FrostGiant_Aggro_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> SnortAudioObject(TEXT("SoundCue'/Game/Audio/Party/FrostGiant_LobStart_Cue.FrostGiant_LobStart_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> StompAudioObject(TEXT("SoundCue'/Game/Audio/Party/FrostGiant_Aggro_Cue.FrostGiant_Aggro_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> RoarAudioObject(TEXT("SoundCue'/Game/Audio/Party/FrostGiant_Aggro_Cue.FrostGiant_Aggro_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> FirstDropAudioObject(TEXT("SoundCue'/Game/Audio/Party/FrostGiant_Death_FirstDrop_Cue.FrostGiant_Death_FirstDrop_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> SecondDropAudioObject(TEXT("SoundCue'/Game/Audio/Party/FrostGiant_Death_SecondDrop_Cue.FrostGiant_Death_SecondDrop_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DeathAudioObject(TEXT("SoundCue'/Game/Audio/Party/FrostGiant_Death_Cue.FrostGiant_Death_Cue'"));

	// Set Default Objects
	S_AggroAudio = AggroAudioObject.Object;
	S_HitAudio = HitAudioObject.Object;
	S_SnortAudio = SnortAudioObject.Object;
	S_StompAudio = StompAudioObject.Object;
	S_RoarAudio = RoarAudioObject.Object;
	S_FirstDropAudio = FirstDropAudioObject.Object;
	S_SecondDropAudio = SecondDropAudioObject.Object;
	S_DeathAudio = DeathAudioObject.Object;


	// Default Config
	Name = EEnemyNames::EN_FrostCaptain;
	NameText = LOCTEXT("FrostCaptainText", "Frost Captain");
	Realm = ERealms::R_Boreal;
	BattleType = EBattleTypes::BT_Boss;
	CommonDrop = EMasterGearList::GL_Elixer;
	UncommonDrop = EMasterGearList::GL_Marauder;
	RareDrop = EMasterGearList::GL_Hauteclaire;
	AttackDelay = 5.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	GetCharacterMovement()->MaxAcceleration = 30;

	// Pawn A.I. config
	PawnSensing->HearingThreshold = 1200;
	PawnSensing->LOSHearingThreshold = 1500;
	PawnSensing->SightRadius = 1200;
	PawnSensing->SetPeripheralVisionAngle(50.0f);
	AcceptanceRadius = 500.0f;
	RunAI = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(125);
	MeleeRadius->SetRelativeLocation(FVector(50, 0, -80));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 130));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	
	// Death FX Config
	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
	
	HitFX->SetRelativeLocation(FVector(0, 0, 30));

	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Enemy-Specific Object Config
	AggroAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("AggroAudio"));
	AggroAudio->Sound = S_AggroAudio;
	AggroAudio->bAutoActivate = false;
	
	HitAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("HitAudio"));
	HitAudio->Sound = S_HitAudio;
	HitAudio->bAutoActivate = false;
	
	SnortAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SnortAudio"));
	SnortAudio->Sound = S_SnortAudio;
	SnortAudio->bAutoActivate = false;
	
	StompAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("StompAudio"));
	StompAudio->Sound = S_StompAudio;
	StompAudio->bAutoActivate = false;
	
	RoarAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("RoarAudio"));
	RoarAudio->Sound = S_RoarAudio;
	RoarAudio->bAutoActivate = false;
	
	FirstDropAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("FirstDropAudio"));
	FirstDropAudio->Sound = S_FirstDropAudio;
	FirstDropAudio->bAutoActivate = false;
	
	SecondDropAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SecondDropAudio"));
	SecondDropAudio->Sound = S_SecondDropAudio;
	SecondDropAudio->bAutoActivate = false;
	
	DeathAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DeathAudio"));
	DeathAudio->Sound = S_DeathAudio;
	DeathAudio->bAutoActivate = false;	

	DoAggro = false;
	DoHaymaker = false;
	DoStomp = false;
	DoBlizzard = false;
}

// Called when the game starts or when spawned
void AFrostCaptain::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &AFrostCaptain::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &AFrostCaptain::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &AFrostCaptain::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &AFrostCaptain::AttackRound);  // bind the attack function to the OnReachedTarget event 

	// Get the placement actor
	for (TActorIterator<AFrostCaptain_Placement> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Placement = *ActorItr; // get the instance of the Placement actor
		Placement->FrostCaptain = this;
	}
}

// Called every frame
void AFrostCaptain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Draw Debug Cylinder on Map
	if (Target->MapControl)
	{
		FVector DebugStart = GetActorLocation();
		FVector DebugEnd = FVector(DebugStart.X, DebugStart.Y, (DebugStart.Z + 500));

		DrawDebugCylinder(GetWorld(), DebugStart, DebugEnd, 10, 12, FColor::Yellow, false, 0, 0);
	}
}

// Melee Attack function
void AFrostCaptain::AttackRound()
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
						

						EnemyDealDamage(15);
						int32 RandomAtk = FMath::RandRange(0, 5);  // get a random int

						// To make this guy harder, he'll use the Stomp attack on rare occasions
						if (!IsDead)
						{
							if (RandomAtk <= 2)
							{
								CastHaymaker();
							}
							if (RandomAtk > 2)
							{
								CastStomp();  // Cast Stomp
							}
						}
					}
				}
			}

			if (Overlapping.Num() == 0)
			{
				if (!IsDead)
				{
					EnemyDealDamage(15);
					CastBlizzard();  // if the player is outside the melee radius, cast Blizzard
				}				
			}

			
		}
	}
}

void AFrostCaptain::Death()
{
	IsDead = true;
	DeathAudio->Play();
	// TO DO : Deactivate Energy Wall 
}

void AFrostCaptain::CastHaymaker()
{
	EnemyDealDamage(20);
	DoHaymaker = true;  // should set DoHaymaker to false based on anim notify

	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AFrostCaptain::ShouldPowerCore, AttackDelay, false);
}

void AFrostCaptain::CastStomp()
{
	EnemyDealDamage(20);
	DoStomp = true;

	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AFrostCaptain::ShouldPowerCore, AttackDelay, false);
}

void AFrostCaptain::CastBlizzard()
{
	EnemyDealDamage(20);
	DoBlizzard = true;
	AggroAudio->Play();

	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AFrostCaptain::ShouldPowerCore, AttackDelay, false);
}

void AFrostCaptain::ShouldPowerCore()
{
	if (PoweredCoreCount < 2)
	{
		switch (PoweredCoreCount)
		{
		case 0:
			if (HP_Current < (HP_Max * 0.75f))
			{
				PoweredCoreCount = 1;
				PowerCore();
			}
			else
			{
				RunToTarget();
			}
			break;
		case 1:
			if (HP_Current < (HP_Max * 0.30f))
			{
				PoweredCoreCount = 2;
				PowerCore();
			}
			else
			{
				RunToTarget();
			}
			break;
		}
	}
}

void AFrostCaptain::PowerCore()
{
	if (!IsDead)
	{
		Targetable = false;  // cannot target during this phase
		RunAI = false;
		DoLeap = true;  // leap animation
		Placement->LeapToCore();  // Leap to Core
	}
}

// A.I. Hearing
void AFrostCaptain::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			DoAggro = true;
			AudioManager->Play_BattleMusic(EBattleTypes::BT_Boss);  // play the boss battle music
			EtherealGameInstance->BlackBox->HasEngagedBoss = true;  // Engage Boss
			// Delay Aggro so this guy can finish his aggro animation
			FTimerDelegate DelegateAggro;
			DelegateAggro.BindUFunction(this, FName("Aggro"), PawnInstigator);
			FTimerHandle AggroTimer;
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 7.5f, false);
		}
	}
}

// A.I. Sight
void AFrostCaptain::OnSeePawn(APawn* Pawn)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			DoAggro = true;
			AudioManager->Play_BattleMusic(EBattleTypes::BT_Boss);  // play the boss battle music
			EtherealGameInstance->BlackBox->HasEngagedBoss = true;  // Engage Boss
			// Delay Aggro so this guy can finish his aggro animation
			FTimerDelegate DelegateAggro;
			DelegateAggro.BindUFunction(this, FName("Aggro"), Pawn);
			FTimerHandle AggroTimer;
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 7.5f, false);
		}
	}	
}

#undef LOCTEXT_NAMESPACE
