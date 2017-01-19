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
#include "Eternal.h"

#define LOCTEXT_NAMESPACE "EtherealText"

AEternal::AEternal(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/EtherealParty/Genie/Genie.Genie'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/Genie/Anim_Genie.Anim_Genie_C'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AuraParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Ability/Summon/P_EternalEnergy.P_EternalEnergy'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> RangedBuildUpParticleObject(TEXT("ParticleSystem'/Game/Vectorfields/Particles/P_Gateway.P_Gateway'"));
	static ConstructorHelpers::FObjectFinder<UClass> InitAggroBlueprintObject(TEXT("Blueprint'/Game/Blueprints/Characters/Enemy/6-CelestialNexus/Eternal_AggroDrop.Eternal_AggroDrop_C'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> AggroVoiceAudioObject(TEXT("SoundCue'/Game/EtherealParty/Genie/Audio/YourSoulIsMine_Cue.YourSoulIsMine_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> RangedBuildUpAudioObject(TEXT("SoundCue'/Game/EtherealParty/Genie/Audio/Eternal_RangedBuildUp_Cue.Eternal_RangedBuildUp_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> HitAudioObject(TEXT("SoundCue'/Game/EtherealParty/Genie/Audio/Eternal_Hit.Eternal_Hit'"));

	// Set Default Objects
	P_AuraFX = AuraParticleObject.Object;
	P_RangedBuildUpFX = RangedBuildUpParticleObject.Object;
	AggroDropBP = InitAggroBlueprintObject.Object;
	S_AggroVoiceAudio = AggroVoiceAudioObject.Object;
	S_RangedBuildUpAudio = RangedBuildUpAudioObject.Object;
	S_HitAudio = HitAudioObject.Object;
	
	// Default Config
	Name = EEnemyNames::EN_Eternal;
	NameText = LOCTEXT("EternalText", "Eternal");
	Realm = ERealms::R_Empyrean;
	BattleType = EBattleTypes::BT_Boss;
	CommonDrop = EMasterGearList::GL_Elixer;
	UncommonDrop = EMasterGearList::GL_Comet;
	RareDrop = EMasterGearList::GL_Aegis;
	AttackDelay = 3.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	GetCharacterMovement()->MaxAcceleration = 30;

	// A.I. Config
	PawnSensing->HearingThreshold = 300;
	PawnSensing->LOSHearingThreshold = 400;
	PawnSensing->SightRadius = 750;
	PawnSensing->SetPeripheralVisionAngle(50.0f);
	AcceptanceRadius = 200.0f;
	RunAI = false;

	Targetable = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(2, 2, 2));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -350));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// Melee Radius Config
	MeleeRadius->SetSphereRadius(100);
	MeleeRadius->SetRelativeLocation(FVector(15, 0, 0));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 200));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));
	
	// Death FX Config
	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
	HitFX->SetRelativeLocation(FVector(0, 0, -40));
	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Enemy-Specific Object Config
	
	// Rune Aura Effect
	AuraFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("AuraFX"));
	AuraFX->SetupAttachment(GetMesh(), FName(TEXT("SummonSocket")));
	AuraFX->Template = P_AuraFX;
	AuraFX->bAutoActivate = true;

	// Ranged Build Up Aura Effect
	RangedBuildUpFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("RangedBuildUpFX"));
	RangedBuildUpFX->SetupAttachment(GetMesh(), FName(TEXT("SummonSocket")));
	RangedBuildUpFX->SetRelativeRotation(FRotator(0, 0, 180));
	RangedBuildUpFX->Template = P_RangedBuildUpFX;
	RangedBuildUpFX->bAutoActivate = false;

	// AggroVoice audio
	AggroVoiceAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("AggroVoiceAudio"));
	AggroVoiceAudio->SetupAttachment(RootComponent);
	AggroVoiceAudio->Sound = S_AggroVoiceAudio;
	AggroVoiceAudio->bAutoActivate = false;

	// RangedBuildUp audio
	RangedBuildUpAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("RangedBuildUpAudio"));
	RangedBuildUpAudio->SetupAttachment(RootComponent);
	RangedBuildUpAudio->Sound = S_RangedBuildUpAudio;
	RangedBuildUpAudio->bAutoActivate = false;

	// Hit audio
	HitAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("HitAudio"));
	HitAudio->SetupAttachment(RootComponent);
	HitAudio->Sound = S_HitAudio;
	HitAudio->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AEternal::BeginPlay()
{
	Super::BeginPlay();

	Targetable = false;  // make this enemy untargetable when spawned
	GetCapsuleComponent()->SetVisibility(false, true); // hide root object and propagate to all children

	PawnSensing->OnHearNoise.AddDynamic(this, &AEternal::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &AEternal::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &AEternal::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &AEternal::AttackCycle);  // bind the attack function to the OnReachedTarget event 

	// We collected this reference in the EnemyMaster class
	if (EtherealGameInstance)
	{
		// Set all Volume Controls
		EtherealGameInstance->SetAudioVolume(AggroVoiceAudio, EAudioTypes::AT_SoundEffect);
		EtherealGameInstance->SetAudioVolume(RangedBuildUpAudio, EAudioTypes::AT_SoundEffect);
	}
}

// Called every frame
void AEternal::Tick(float DeltaTime)
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
void AEternal::AttackCycle()
{
	if (!Target->IsDead)
	{
		if (!IsAttacking)
		{
			// Start Attacking
			IsAttacking = true;
			// Reset All Attack Animations
			DoAttack1 = false;
			DoAttack2 = false;
			DoHeavyAttack = false;
			DoRangedAttack = false;

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

						// To make this guy harder, he'll use the HeavyAttack on rare occasions
						if (!IsDead)
						{
							if (RandomAtk <= 2)
							{
								Attack1();
							}
							if (RandomAtk > 2 && RandomAtk < 5)
							{
								Attack2();
							}
							if (RandomAtk >= 5)
							{
								HeavyAttack();
							}
						}
					}
				}
			}
			// Player is not overlapping, so do a ranged attack.
			if (Overlapping.Num() == 0)
			{
				if (!IsDead)
				{
					EnemyDealDamage(15);
					RangedAttack();
				}
			}
		}
	}
}

void AEternal::Death()
{
	IsDead = true;
}

// Init Aggro - Called by Zhan's death while inside Celestial Nexus
void AEternal::InitAggro()
{	
	// Spawn Eternal's Aggro Drop at current location - StartHeightOffset on Z
	AActor* AggroDrop = UCommonLibrary::SpawnBP(GetWorld(), AggroDropBP, FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z), GetActorRotation());
	AudioManager->Play_Eternal_Intro();	
	// Start the spawn process
	FTimerHandle AggroTimer;
	GetWorldTimerManager().SetTimer(AggroTimer, this, &AEternal::RaiseToAggro, 8.0f, false);
}

// RaiseToAggro - Handles the spawning of the Eternal enemy
void AEternal::RaiseToAggro()
{
	this->GetCapsuleComponent()->SetVisibility(true, true);  // this will also turn on the Targeting Reticle
	DoRaiseAggro = true;
	AggroVoiceAudio->Play();  // "YOUR SOUL IS MINE!"
	UGameplayStatics::PlayWorldCameraShake(GetWorld(), Target->LevelUpCamShake, Target->GetActorLocation(), 0, 10000, 1, false);  // level up cam shake 
	// TO DO : Client Play Force Feedback FF_ZhanSpawn

	// earlier code in BeginPlay() sets the reticle visible, be sure to turn it off.
	if (TargetingReticle->IsVisible())
	{
		TargetingReticle->SetVisibility(false);
	}

	// Start the attack cycle
	FTimerHandle AttackTimer;
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AEternal::StartAttacking, 4.0f, false);
}

void AEternal::StartAttacking()
{
	Targetable = true;
	Aggro(Target);
	AudioManager->Play_Eternal_Battle();
	RunToTarget();
}

void AEternal::Attack1()
{
	DoAttack1 = true;
	EnemyDealDamage(50);
	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void AEternal::Attack2()
{
	DoAttack2 = true;
	EnemyDealDamage(60);
	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void AEternal::RangedAttack()
{
	DoRangedAttack = true;
	EnemyDealDamage(70);
	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void AEternal::HeavyAttack()
{
	DoHeavyAttack = true;
	EnemyDealDamage(70);
	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

// A.I. Hearing
void AEternal::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			// This functionality is removed because the Eternal does not aggro in a traditional manner
			//Aggro(PawnInstigator);
		}
	}
}

// A.I. Sight
void AEternal::OnSeePawn(APawn* Pawn)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			// This functionality is removed because the Eternal does not aggro in a traditional manner
			//Aggro(Pawn);
		}
	}	
}

#undef LOCTEXT_NAMESPACE