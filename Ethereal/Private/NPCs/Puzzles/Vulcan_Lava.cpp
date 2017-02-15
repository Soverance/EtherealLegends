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
#include "Characters/Player/EtherealPlayerMaster.h"
#include "Vulcan_Lava.h"

// The majority of this class got moved into a matinee... lulz

AVulcan_Lava::AVulcan_Lava(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> LavaMesh(TEXT("StaticMesh'/Game/InfinityBladeFireLands/Environments/Fire/Env_Fire_Magma/StaticMesh/WeaponSmithsLava.WeaponSmithsLava'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FireHeadMesh(TEXT("StaticMesh'/Game/InfinityBladeFireLands/Environments/Fire/Fire_Fortress/SM/Env_Fire_NordHeed02.Env_Fire_NordHeed02'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> HeadLavaMesh(TEXT("StaticMesh'/Game/InfinityBladeFireLands/Environments/Fire/Env_Fire_FlameDungeon/StaticMesh/Pipes/SM_Dungeon_Pipes_Lava01.SM_Dungeon_Pipes_Lava01'"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> RockMesh(TEXT("StaticMesh'/Game/Elemental/Environment/Throne_Interior/Mesh/SM_Rock_01.SM_Rock_01'"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> KickRockMesh(TEXT("StaticMesh'/Game/Elemental/Environment/Throne_Interior/Mesh/SM_Rock_01.SM_Rock_01'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> AvalancheAudioObject(TEXT("SoundCue'/Game/Elemental/Sound/shrt_avalanche_begin_Cue.shrt_avalanche_begin_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ExplosionAudioObject(TEXT("SoundCue'/Game/Sounds/Weapon_GrenadeLauncher/Mono/GrenadeLauncher_Explosion_Cue.GrenadeLauncher_Explosion_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> FinalScreamAudioObject(TEXT("SoundCue'/Game/Elemental/Sound/shrt_finalscream_sfx_to_end_Cue.shrt_finalscream_sfx_to_end_Cue'"));
	static ConstructorHelpers::FObjectFinder<UClass> KickRockCamShakeObject(TEXT("Blueprint'/Game/Blueprints/CamShakes/CS_OpenChest.CS_OpenChest_C'"));
	static ConstructorHelpers::FObjectFinder<UClass> RockSlideCamShakeObject(TEXT("Blueprint'/Game/Blueprints/CamShakes/CS_VulcanRockSlide.CS_VulcanRockSlide_C'"));
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> DebrisParticleObject(TEXT("ParticleSystem'/Game/Elemental/Effects/Fx_DustAndDebris/ParticleSystems/P_Burnin_Sigil_RockDebris.P_Burnin_Sigil_RockDebris'"));
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> BreakParticleObject(TEXT("ParticleSystem'/Game/Elemental/Effects/Fx_DustAndDebris/ParticleSystems/P_BreakAway_BackDebris.P_BreakAway_BackDebris'"));

	// Set Default Objects
	SM_LavaMesh1 = LavaMesh.Object;
	SM_LavaMesh2 = LavaMesh.Object;
	SM_FireHead = FireHeadMesh.Object;
	SM_HeadLava = HeadLavaMesh.Object;
	//SM_Rock = RockMesh.Object;
	//SM_KickRock = KickRockMesh.Object;
	S_AvalancheAudio = AvalancheAudioObject.Object;
	S_ExplosionAudio = ExplosionAudioObject.Object;
	S_FinalScreamAudio = FinalScreamAudioObject.Object;
	KickRockCamShake = KickRockCamShakeObject.Object; 
	RockSlideCamShake = RockSlideCamShakeObject.Object;
	//P_DebrisFX = DebrisParticleObject.Object;
	//P_BreakFX = BreakParticleObject.Object;

	InteractBox->SetRelativeLocation(FVector(-63, -2065, 532));
	InteractBox->SetBoxExtent(FVector(60, 60, 60));

	// Create objects
	FireHead = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("FireHead"));
	FireHead->SetStaticMesh(SM_FireHead);
	FireHead->SetupAttachment(Root);

	HeadLava = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("HeadLava"));
	HeadLava->SetStaticMesh(SM_HeadLava);
	HeadLava->SetupAttachment(FireHead);

	LavaMesh1 = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("LavaMesh1"));
	LavaMesh1->SetStaticMesh(SM_LavaMesh1);
	LavaMesh1->SetupAttachment(FireHead);
	LavaMesh1->SetRelativeLocation(FVector(1180, 34, 29));
	UCommonLibrary::SetupSMComponentsWithCollision(LavaMesh1);

	LavaMesh2 = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("LavaMesh2"));
	LavaMesh2->SetStaticMesh(SM_LavaMesh2);
	LavaMesh2->SetupAttachment(LavaMesh1);
	LavaMesh2->SetRelativeLocation(FVector(-670, 1026, 0));
	LavaMesh2->SetRelativeRotation(FRotator(0, -20, 0));
	UCommonLibrary::SetupSMComponentsWithCollision(LavaMesh2);

	//Rock = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Rock"));
	//Rock->StaticMesh = SM_Rock;
	//Rock->SetupAttachment(Root);
	//Rock->SetRelativeLocation(FVector(-485, -1265, 475));
	//Rock->SetRelativeRotation(FRotator(0, -70, 0));
	//Rock->SetRelativeScale3D(FVector(4, 4, 4));

	//KickRock = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("KickRock"));
	//KickRock->StaticMesh = SM_KickRock;
	//KickRock->SetupAttachment(Root);
	//KickRock->SetRelativeLocation(FVector(-203, -2058, 557));
	//KickRock->SetRelativeRotation(FRotator(-71, -14, -150));
	//KickRock->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));

	AvalancheAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("AvalancheAudio"));
	AvalancheAudio->Sound = S_AvalancheAudio;
	AvalancheAudio->SetupAttachment(Root);
	AvalancheAudio->bAutoActivate = false;

	ExplosionAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("ExplosionAudio"));
	ExplosionAudio->Sound = S_ExplosionAudio;
	ExplosionAudio->SetupAttachment(Root);
	ExplosionAudio->bAutoActivate = false;

	FinalScreamAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("FinalScreamAudio"));
	FinalScreamAudio->Sound = S_FinalScreamAudio;
	FinalScreamAudio->SetupAttachment(Root);
	FinalScreamAudio->bAutoActivate = false;

	//DebrisFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("DebrisFX"));
	//DebrisFX->Template = P_DebrisFX;
	//DebrisFX->SetupAttachment(Root);

	//BreakFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("BreakFX"));
	//BreakFX->Template = P_BreakFX;
	//BreakFX->SetupAttachment(Root);

	IsUsable = true;
	InteractAnimType = EInteractAnims::IA_Kick;

	MapMarkerFX->SetRelativeLocation(InteractBox->GetComponentLocation());
	MapMarkerFX->SetColorParameter(FName(TEXT("BeamColor")), FColor::Purple);
}

// Called when the game starts or when spawned
void AVulcan_Lava::BeginPlay()
{
	Super::BeginPlay();

	//DoInteract.AddDynamic(this, &AVulcan_Lava::Interact);
	// This usually wouldn't be necessary, since we collect this reference when the player enters the NPC's collider.
	// However, we require the reference to draw debug lines for the map, and the player may access the map before having interacting with this actor
	for (TActorIterator<AEtherealPlayerMaster> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		InteractingPlayer = *ActorItr; // get the instance of the Player
	}
}

// Called every frame
void AVulcan_Lava::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Interact with this NPC
void AVulcan_Lava::Interact()
{
	IsUsable = false;

	StartRockSlide();

	// I left this code in Blueprint because it's sort of a mess that Jacob originally built with Timelines, but it works, so whatever.
	// By calling the StartRockSlide() event, it does what is listed below inside the BP:

	//IsUsable = false;
	// TO DO : Play World Camera Shake CS Open Chest (for kicking the rock)
	//UGameplayStatics::PlayWorldCameraShake(GetWorld(), KickRockCamShake, InteractingPlayer->GetActorLocation(), 0, 10000, 1, false);  // Kick Rock cam shake 
	// TO DO : DELAY 0.8
	// Start Rock Slide after a short delay (right about when the player's foot hits the rock from his interact animation)
	//FTimerHandle KickTimer;
	//GetWorldTimerManager().SetTimer(KickTimer, this, &AVulcan_Lava::StartRockSlide, 0.8f, false);

	// Play avalanche audio
	// TO DO : Play world camera shake CS Vulcan Rock Slide
	// TO DO : Spawn emitter at location, ParticleSystem'/Game/Elemental/Effects/Fx_DustAndDebris/ParticleSystems/P_Burnin_Sigil_RockDebris.P_Burnin_Sigil_RockDebris'
	// TO DO : Spawn emitter at location, ParticleSystem'/Game/Elemental/Effects/Fx_DustAndDebris/ParticleSystems/P_BreakAway_BackDebris.P_BreakAway_BackDebris'
	// TO DO : Move kick rock towards large rock with timeline
	// TO DO : Impact large rock, spawn emitter ParticleSystem'/Game/Elemental/Effects/Fx_Fire/ParticleSystems/P_ShatterRock_Blast2.P_ShatterRock_Blast2'
	// TO DO : Play Rock Explosion Audio (this was removed from the BP, too much audio at once. probably not going to put it back in)
	// TO DO : Play SFX Final Scream Audio
	// TO DO : SPawn emitter at Rock, ParticleSystem'/Game/Elemental/Effects/FX_HammerHit/ParticleSystems/P_Crack_03_BurstRock.P_Crack_03_BurstRock'
	// TO DO : move the Rock and the KickRock into their final positions
	// TO DO : move the lava down, so that the player can now traverse the area
}

// Start Rock Slide
void AVulcan_Lava::StartRockSlide_Implementation()
{
	//AvalancheAudio->Play();
	// TO DO : Play World Camera Shake CS Rock Slide (for kicking the rock)
	//UGameplayStatics::PlayWorldCameraShake(GetWorld(), RockSlideCamShake, InteractingPlayer->GetActorLocation(), 0, 10000, 1, false);  // Rock Slide cam shake 
}


