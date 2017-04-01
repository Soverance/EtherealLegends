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
#include "DeathCap.h"

#define LOCTEXT_NAMESPACE "EtherealText"

ADeathCap::ADeathCap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> EnemyMesh(TEXT("SkeletalMesh'/Game/EtherealParty/GiantMushroom/GiantMushroomMesh.GiantMushroomMesh'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/GiantMushroom/Anim_GiantMushroom.Anim_GiantMushroom_C'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> UpheavalParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Skill_Aura/Mushroom_Pulse.Mushroom_Pulse'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> GasParticleObject(TEXT("ParticleSystem'/Game/Vectorfields/Particles/P_PoisonVent.P_PoisonVent'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> AggroAudioObject(TEXT("SoundCue'/Game/Audio/Party/GiantMushroom_Aggro_Cue.GiantMushroom_Aggro_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> SpitAudioObject(TEXT("SoundCue'/Game/Audio/Party/GiantMushroom_Attack1_Cue.GiantMushroom_Attack1_Cue'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> UpheavalDecalObject(TEXT("Material'/Game/Materials/AreaEffectDecals/M_SoulEater-Statue-StompDecal.M_SoulEater-Statue-StompDecal'"));
	static ConstructorHelpers::FObjectFinder<UClass> LobBlueprintObject(TEXT("Blueprint'/Game/Blueprints/Characters/Enemy/1-ShiitakeTemple/Mushroom_PoisonLob.Mushroom_PoisonLob_C'"));
		
	// DEFAULTS
	Name = EEnemyNames::EN_DeathCap;
	NameText = LOCTEXT("DeathCapText", "Death Cap");
	Realm = ERealms::R_Shiitake;
	BattleType = EBattleTypes::BT_Boss;	
	CommonDrop = EMasterGearList::GL_AquaSignet;
	UncommonDrop = EMasterGearList::GL_EagleEye;
	RareDrop = EMasterGearList::GL_SpartanShield;
	AttackDelay = 3.0f;
	BaseEyeHeight = 16;
	GetCapsuleComponent()->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	GetCharacterMovement()->MaxAcceleration = 0;
	GetCharacterMovement()->RotationRate = FRotator(0, 90, 0); 

	MapMarkerFX->SetColorParameter(FName(TEXT("BeamColor")), FLinearColor::Yellow);

	IsHiding = true;  // puts the mushroom in the ground, so he can pop up when the player aggros him
	IsAttacking = false;

	PoisonLobBP = LobBlueprintObject.Object;  

	// Pawn A.I. config
	PawnSensing->HearingThreshold = 300;
	PawnSensing->LOSHearingThreshold = 400;
	PawnSensing->SightRadius = 750;
	PawnSensing->SetPeripheralVisionAngle(50.0f);
	AcceptanceRadius = 750.0f;
	RunAI = false;

	// Mesh Config
	GetMesh()->SkeletalMesh = EnemyMesh.Object;
	GetMesh()->SetAnimInstanceClass(AnimBP.Object);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	GetMesh()->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// Melee Radius Config
	MeleeRadius->SetSphereRadius(220);
	MeleeRadius->SetRelativeLocation(FVector(0, 0, -90));

	// Targeting Reticle config
	TargetingReticle->SetRelativeLocation(FVector(0, 0, 150));
	TargetingReticle->SetRelativeRotation(FRotator(0, 0, 180));
	TargetingReticle->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	// Hit & Death Effect Config
	HitFX->SetRelativeLocation(FVector(40, 0, 10));
	DeathFX->SetRelativeLocation(FVector(0, 0, -90));
	DeathFX->SetRelativeScale3D(FVector(1, 1, 1));
	DisappearFX->SetRelativeLocation(FVector(0, 0, -20));

	// Configure components
	UpheavalFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("UpheavalFX"));
	UpheavalFX->SetupAttachment(GetMesh());
	P_UpheavalFX = UpheavalParticleObject.Object;
	UpheavalFX->Template = P_UpheavalFX;
	UpheavalFX->bAutoActivate = false;

	PoisonGasFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("PoisonGasFX"));
	PoisonGasFX->SetupAttachment(GetMesh());
	P_PoisonGasFX = GasParticleObject.Object;
	PoisonGasFX->Template = P_PoisonGasFX;
	PoisonGasFX->SetRelativeLocation(FVector(9, 70, 0));
	PoisonGasFX->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.05f));
	PoisonGasFX->bAutoActivate = false;

	AggroAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("AggroAudio"));
	AggroAudio->SetupAttachment(GetMesh());
	S_AggroAudio = AggroAudioObject.Object;
	AggroAudio->Sound = S_AggroAudio;
	AggroAudio->bAutoActivate = false;

	SpitAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SpitAudio"));
	SpitAudio->SetupAttachment(GetMesh());
	S_SpitAudio = SpitAudioObject.Object;
	SpitAudio->Sound = S_SpitAudio;
	SpitAudio->bAutoActivate = false;

	UpheavalDecal = ObjectInitializer.CreateDefaultSubobject<UDecalComponent>(this, TEXT("UpheavalDecal"));
	UpheavalDecal->SetupAttachment(GetMesh());
	UpheavalDecal->SetMaterial(0, UpheavalDecalObject.Object);  // set the Beam Decal material
	UpheavalDecal->SetRelativeRotation(FRotator(90, 0, -90));
	UpheavalDecal->SetRelativeScale3D(FVector(0.85f, 0.85f, 0.85f));
	UpheavalDecal->SetVisibility(false);
}

// Called when the game starts or when spawned
void ADeathCap::BeginPlay()
{
	Super::BeginPlay();

	PawnSensing->OnHearNoise.AddDynamic(this, &ADeathCap::OnHearNoise);  // bind the OnHearNoise event
	PawnSensing->OnSeePawn.AddDynamic(this, &ADeathCap::OnSeePawn);  // bind the OnSeePawn event
	OnDeath.AddDynamic(this, &ADeathCap::Death); // bind the death fuction to the OnDeath event 
	OnReachedTarget.AddDynamic(this, &ADeathCap::AttackCycle);  // bind the attack function to the OnReachedTarget event
}

// Called every frame
void ADeathCap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADeathCap::Death()
{
	//Target->EtherealPlayerState->EnemyKillReward(Level, CommonDrop, UncommonDrop, RareDrop);  // reward the player for killing this enemy	
	IsHiding = true;
	// FinalDeath() is called by anim notify after the death animation
}

void ADeathCap::AttackCycle()
{
	if (!Target->IsDead)
	{
		if (!IsAttacking)
		{
			IsAttacking = true;

			int32 RandomAtk = FMath::RandRange(0, 4);  // get a random int

			if (!IsDead)
			{
				if (RandomAtk <= 2)
				{
					PoisonLob();  // do Poison Lob
				}
				if (RandomAtk > 2)
				{
					PoisonUpheaval();  // Do Poison Upheaval
				}
			}
		}
	}	
}

void ADeathCap::PoisonLob()
{
	EnemyDealDamage(30); // get damage output
	DoSpit = true;  // do the spit animation
	SpitAudio->Play();

	// I'm spawning this blueprint because I was too lazy to convert this Lob drop actor to C++
	// it's on the TO DO list...
	AActor* PoisonLob = UCommonLibrary::SpawnBP(GetWorld(), PoisonLobBP, Target->GetActorLocation(), Target->GetActorRotation());

	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void ADeathCap::PoisonUpheaval()
{
	EnemyDealDamage(45); // get damage output
	DoRoar = true;  // do the roar animation
	AggroAudio->Play();
	UpheavalDecal->SetVisibility(true);
	
	// start upheaval effects after a short delay (gives the player time to see and react to the incoming attack)
	FTimerHandle DestroyTimer;
	GetWorldTimerManager().SetTimer(DestroyTimer, this, &ADeathCap::StartUpheaval, 2.5f, false);
}

// start upheaval effects
void ADeathCap::StartUpheaval()
{
	UpheavalFX->Activate();
	PoisonGasFX->Activate();

	TArray<AActor*> Overlapping;  // define a local array to store hits
	MeleeRadius->GetOverlappingActors(Overlapping, AEtherealPlayerMaster::StaticClass()); // check for overlapping players within the blast radius

	for (AActor* Actor : Overlapping) // for each actor found overlapping
	{
		AEtherealPlayerMaster* Player = Cast<AEtherealPlayerMaster>(Actor);  // cast to Player Master

		if (Player) // if succeeded
		{
			Player->PlayerTakeDamage(DamageOutput);  // have the player take damage
			Player->EtherealPlayerController->ActivateStatus_Poison();  // POISON STATUS
		}
	}

	// disable upheaval effects after a short delay
	FTimerHandle DestroyTimer;
	GetWorldTimerManager().SetTimer(DestroyTimer, this, &ADeathCap::StopUpheaval, 1.0f, false);
}

// disable upheaval effects
void ADeathCap::StopUpheaval()
{
	UpheavalDecal->SetVisibility(false);
	UpheavalFX->Deactivate();
	PoisonGasFX->Deactivate();

	// Restart the Attack Cycle after a short delay
	FTimerHandle EndTimer;
	GetWorldTimerManager().SetTimer(EndTimer, this, &AEtherealEnemyMaster::EndAttackRound, AttackDelay, false);
}

void ADeathCap::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if (!IsAggroed)
	{
		if (IsHiding)
		{
			IsHiding = false;

			// wait a bit
			FTimerDelegate DelegateAggro;
			DelegateAggro.BindUFunction(this, FName("Aggro"), PawnInstigator);
			FTimerHandle AggroTimer;
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 2.5f, false);
		}
		else
		{
			// wait a bit
			FTimerDelegate DelegateAggro;
			DelegateAggro.BindUFunction(this, FName("Aggro"), PawnInstigator);
			FTimerHandle AggroTimer;
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 5.0f, false);
		}
	}
}

void ADeathCap::OnSeePawn(APawn* Pawn)
{
	if (!IsAggroed)
	{
		if (IsHiding)
		{
			IsHiding = false;

			// wait a bit before aggroing 
			FTimerDelegate DelegateAggro;
			DelegateAggro.BindUFunction(this, FName("Aggro"), Pawn);
			FTimerHandle AggroTimer;
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 2.5f, false);
		}
		else
		{
			// wait a bit before aggroing 
			FTimerDelegate DelegateAggro;
			DelegateAggro.BindUFunction(this, FName("Aggro"), Pawn);
			FTimerHandle AggroTimer;
			GetWorldTimerManager().SetTimer(AggroTimer, DelegateAggro, 5.0f, false);
		}
	}
}

#undef LOCTEXT_NAMESPACE
