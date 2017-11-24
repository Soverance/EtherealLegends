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
#include "LavaKnight.h"

#define LOCTEXT_NAMESPACE "EtherealText"

ALavaKnight::ALavaKnight(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/EtherealParty/LavaKnight/Mesh/SM_LavaKnight.SM_LavaKnight'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/LavaKnight/Mesh/LavaKnight_AnimBP.LavaKnight_AnimBP_C'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DeathAudioObject(TEXT("SoundCue'/Game/Elemental/Sound/shrt_finalscream_sfx_to_end_Cue.shrt_finalscream_sfx_to_end_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> HitAudioObject(TEXT("SoundCue'/Game/EtherealParty/IceKnight/Audio/Avatar_IceKnight_Hit_Cue.Avatar_IceKnight_Hit_Cue'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshObject(TEXT("SkeletalMesh'/Game/EtherealParty/LavaKnight/Mesh/GDC2012_Hammer.GDC2012_Hammer'"));

	// Set Default Objects
	S_DeathAudio = DeathAudioObject.Object;
	S_HitAudio = HitAudioObject.Object;
	SK_WeaponSkeletalMesh = SkeletalMeshObject.Object;

	// Default Config
	Name = EEnemyNames::EN_LavaKnight;
	NameText = LOCTEXT("LavaKnightText", "Lava Knight");
	Realm = ERealms::R_Vulcan;
	BattleType = EBattleTypes::BT_Boss;
	CommonDrop = EMasterGearList::GL_FlameSignet;
	UncommonDrop = EMasterGearList::GL_Claymore;
	RareDrop = EMasterGearList::GL_Joyeuse;
	AttackDelay = 6.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	GetCharacterMovement()->MaxAcceleration = 40;

	MapMarkerFX->SetColorParameter(FName(TEXT("BeamColor")), FLinearColor::Yellow);

	// Pawn A.I. config
	PawnSensing->HearingThreshold = 400;
	PawnSensing->LOSHearingThreshold = 550;
	PawnSensing->SightRadius = 550;
	PawnSensing->SetPeripheralVisionAngle(60.0f);
	AcceptanceRadius = 300.0f;
	RunAI = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -84));
	GetMesh()->SetRelativeRotation(FRotator(0, 270, 90));

	// Melee Radius Config
	MeleeRadius->SetSphereRadius(150);
	MeleeRadius->SetRelativeLocation(FVector(100, 0, -50));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 25, 75));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));

	// FX Config
	HitFX->SetRelativeLocation(FVector(0, 0, 0));

	DeathFX->SetRelativeLocation(FVector(0, 0, -84));
	DeathFX->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));

	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Hammer Weapon
	WeaponSkeletalMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponSkeletalMesh"));
	WeaponSkeletalMesh->SetSkeletalMesh(SK_WeaponSkeletalMesh);
	UCommonLibrary::SetupSKComponentsWithCollision(WeaponSkeletalMesh);
	WeaponSkeletalMesh->SetupAttachment(GetMesh(), FName(TEXT("WeaponSocket_Right")));
	WeaponSkeletalMesh->SetRelativeScale3D(FVector(1, 1, 1));
	WeaponSkeletalMesh->SetRelativeLocation(FVector(0, 0, 0));
	WeaponSkeletalMesh->SetRelativeRotation(FRotator(0, 0, 0));
	WeaponSkeletalMesh->SetVisibility(true);

	// Death Audio
	DeathAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DeathAudio"));
	DeathAudio->Sound = S_DeathAudio;
	DeathAudio->bAutoActivate = false;
	DeathAudio->SetupAttachment(RootComponent);

	// Hit Audip
	HitAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("HitAudio"));
	HitAudio->Sound = S_HitAudio;
	HitAudio->bAutoActivate = false;
	HitAudio->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALavaKnight::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &ALavaKnight::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &ALavaKnight::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &ALavaKnight::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &ALavaKnight::AttackCycle);  // bind the attack function to the OnReachedTarget event	
}

// Called every frame
void ALavaKnight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Melee Attack function
void ALavaKnight::AttackCycle()
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
						EnemyDealDamage(25);

						int32 RandomAtk = FMath::RandRange(0, 6);  // get a random int
						// All melee attacks are the same, just with different animations.
						if (!IsDead)
						{
							if (RandomAtk <= 2)
							{
								DoAtk1 = true;
							}
							if (RandomAtk > 2 && RandomAtk <= 5)
							{
								DoAtk2 = true;
							}
							if (RandomAtk > 5)
							{
								DoKick = true;
							}
						}
					}
				}
			}

			// player isn't overlapping, which means we can do a ranged attack at him
			if (Overlapping.Num() == 0)
			{
				EnemyDealDamage(20);
				int32 RandomAtk = FMath::RandRange(0, 4);  // get a random int

				// Do ranged attacks at random
				if (!IsDead)
				{
					if (RandomAtk <= 2)
					{
						DoCasting1 = true;
					}
					if (RandomAtk > 2)
					{
						DoCasting2 = true;
					}
				}
			}

			// Restart the Attack Cycle after a short delay
			FTimerHandle EndTimer;
			GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
		}
	}
}

void ALavaKnight::Death()
{
	DeathAudio->Play();

	// SIGNET RING
	EMasterGearList SignetRing = EMasterGearList::GL_FlameSignet;  // Players get the Signet Ring at a 100% drop rate
	Target->EtherealPlayerState->EnemyKillReward(0, SignetRing, SignetRing, SignetRing);  // reward the player with the appropriate signet ring, but give no EXP
}

// A.I. Hearing
void ALavaKnight::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			IsAggroed = true;
			EtherealGameInstance->BlackBox->HasEngagedBoss = true;  // Engage Boss
			// Delay Aggro 
			FTimerDelegate DelegateAggro;
			DelegateAggro.BindUFunction(this, FName("Aggro"), PawnInstigator);
			FTimerHandle AggroTimer;
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 2.5f, false);
		}
	}
}

// A.I. Sight
void ALavaKnight::OnSeePawn(APawn* Pawn)
{
	if (!IsDead)
	{
		if (!IsAggroed)
		{
			IsAggroed = true;
			EtherealGameInstance->BlackBox->HasEngagedBoss = true;  // Engage Boss
			// Delay Aggro 
			FTimerDelegate DelegateAggro;
			DelegateAggro.BindUFunction(this, FName("Aggro"), Pawn);
			FTimerHandle AggroTimer;
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 2.5f, false);
		}
	}
}

#undef LOCTEXT_NAMESPACE
