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
#include "Characters/Player/EtherealPlayerMaster.h"
#include "Yggdrasil_Runes.h"

AYggdrasil_Runes::AYggdrasil_Runes(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> AlcoveMesh(TEXT("StaticMesh'/Game/InfinityBladeIceLands/Environments/Ice/EX_Env_Ice_1/StaticMesh/SM_Ex_Rune_Stone_1.SM_Ex_Rune_Stone_1'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> RotundaMesh(TEXT("StaticMesh'/Game/InfinityBladeIceLands/Environments/Ice/EX_Env_Ice_1/StaticMesh/SM_Ex_Rune_Stone_1.SM_Ex_Rune_Stone_1'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TreetopMesh(TEXT("StaticMesh'/Game/InfinityBladeIceLands/Environments/Ice/EX_Env_Ice_1/StaticMesh/SM_Ex_Rune_Stone_1.SM_Ex_Rune_Stone_1'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AlcoveParticle(TEXT("ParticleSystem'/Game/Vectorfields/Particles/P_YggdrasilRune.P_YggdrasilRune'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> RotundaParticle(TEXT("ParticleSystem'/Game/Vectorfields/Particles/P_YggdrasilRune.P_YggdrasilRune'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> TreetopParticle(TEXT("ParticleSystem'/Game/Vectorfields/Particles/P_YggdrasilRune.P_YggdrasilRune'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> AlcoveAudioObject(TEXT("SoundCue'/Game/Audio/Party/Yggrasil_RunePower_Cue.Yggrasil_RunePower_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> RotundaAudioObject(TEXT("SoundCue'/Game/Audio/Party/Yggrasil_RunePower_Cue.Yggrasil_RunePower_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> TreetopAudioObject(TEXT("SoundCue'/Game/Audio/Party/Yggrasil_RunePower_Cue.Yggrasil_RunePower_Cue'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> LeftEyeParticle(TEXT("ParticleSystem'/Game/Environment/Effects/particles/gold_eye.gold_eye'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> RightEyeParticle(TEXT("ParticleSystem'/Game/Environment/Effects/particles/gold_eye.gold_eye'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TreeTrunkMesh(TEXT("StaticMesh'/Game/KiteDemo/Environments/Trees/Tree_Stump_01/Tree_Stump_01.Tree_Stump_01'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TreeBranchesMesh(TEXT("StaticMesh'/Game/Meshes/EpicTree.EpicTree'"));
	//static ConstructorHelpers::FObjectFinder<UDestructibleMesh> TreeHeadMeshObject(TEXT("DestructibleMesh'/Game/Environment/Meshes/RTS_Env_Fire_NordHeed01_DM.RTS_Env_Fire_NordHeed01_DM'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> EnergyPillarParticle(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/ICE/P_YggdrasilEnergyPillar.P_YggdrasilEnergyPillar'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PillarAuraParticle(TEXT("ParticleSystem'/Game/FXStarStarterKit/Particles/P_Yggdrasil_PillarPreAura.P_Yggdrasil_PillarPreAura'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> LiftIndicatorParticle(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/P_YggBossLiftIndicator.P_YggBossLiftIndicator'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> HeadExplosionAudioObject(TEXT("SoundCue'/Game/EtherealParty/IceKnight/Audio/IceGiant_RockExplosion_Cue.IceGiant_RockExplosion_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> EnergyChargeAudioObject(TEXT("SoundCue'/Game/EtherealParty/IceKnight/Audio/IceGiant_Charge_Cue.IceGiant_Charge_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> AuraAudioObject(TEXT("SoundCue'/Game/EtherealParty/IceKnight/Audio/IceGiant_Breath_Cue.IceGiant_Breath_Cue'"));

	// Set Default Objects
	SM_Rune_Alcove = AlcoveMesh.Object;
	SM_Rune_Rotunda = RotundaMesh.Object;
	SM_Rune_Treetop = TreetopMesh.Object;
	P_AlcoveFX = AlcoveParticle.Object;
	P_RotundaFX = RotundaParticle.Object;
	P_TreetopFX = TreetopParticle.Object;
	S_AlcoveAudio = AlcoveAudioObject.Object;
	S_RotundaAudio = RotundaAudioObject.Object;
	S_TreetopAudio = TreetopAudioObject.Object;
	P_LeftEyeFX = LeftEyeParticle.Object;
	P_RightEyeFX = RightEyeParticle.Object;
	SM_TreeTrunk = TreeTrunkMesh.Object;
	SM_TreeBranches = TreeBranchesMesh.Object;
	P_EnergyPillarFX = EnergyPillarParticle.Object;
	P_PillarAuraFX = PillarAuraParticle.Object;
	P_LiftIndicatorFX = LiftIndicatorParticle.Object;
	S_HeadExplosionAudio = HeadExplosionAudioObject.Object;
	S_EnergyChargeAudio = EnergyChargeAudioObject.Object;
	S_AuraAudio = AuraAudioObject.Object;

	IsUsable = true;
	CurrentRune = ECurrentRune::CR_None;
	InteractAnimType = EInteractAnims::IA_Open;
	DoInteraction.AddDynamic(this, &AYggdrasil_Runes::CustomInteract);

	//////////////////////////////////////
	// ALCOVE RUNE

	Rune_Alcove = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Rune_Alcove"));
	Rune_Alcove->SetStaticMesh(SM_Rune_Alcove);
	Rune_Alcove->SetupAttachment(Root);
	Rune_Alcove->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	AlcoveFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("AlcoveFX"));
	AlcoveFX->Template = P_AlcoveFX;
	AlcoveFX->bAutoActivate = false;
	AlcoveFX->SetupAttachment(Rune_Alcove);

	AlcoveAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("AlcoveAudio"));
	AlcoveAudio->Sound = S_AlcoveAudio;
	AlcoveAudio->bAutoActivate = false;
	AlcoveAudio->SetupAttachment(Rune_Alcove);

	PointLight_Alcove = ObjectInitializer.CreateDefaultSubobject<UPointLightComponent>(this, TEXT("PointLight_Alcove"));
	PointLight_Alcove->SetupAttachment(Rune_Alcove);

	InteractBox_Alcove = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("InteractBox_Alcove"));
	InteractBox_Alcove->SetupAttachment(Rune_Alcove);
	InteractBox_Alcove->SetBoxExtent(FVector(100, 100, 100));
	InteractBox_Alcove->SetRelativeLocation(FVector(0, 0, 0));

	//////////////////////////////////////
	// ROTUNDA RUNE

	Rune_Rotunda = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Rune_Rotunda"));
	Rune_Rotunda->SetStaticMesh(SM_Rune_Rotunda);
	Rune_Rotunda->SetupAttachment(Root);
	Rune_Rotunda->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	RotundaFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("RotundaFX"));
	RotundaFX->Template = P_RotundaFX;
	RotundaFX->bAutoActivate = false;
	RotundaFX->SetupAttachment(Rune_Rotunda);

	RotundaAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("RotundaAudio"));
	RotundaAudio->Sound = S_RotundaAudio;
	RotundaAudio->bAutoActivate = false;
	RotundaAudio->SetupAttachment(Rune_Rotunda);

	PointLight_Rotunda = ObjectInitializer.CreateDefaultSubobject<UPointLightComponent>(this, TEXT("PointLight_Rotunda"));
	PointLight_Rotunda->SetupAttachment(Rune_Rotunda);

	InteractBox_Rotunda = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("InteractBox_Rotunda"));
	InteractBox_Rotunda->SetupAttachment(Rune_Rotunda);
	InteractBox_Rotunda->SetBoxExtent(FVector(100, 100, 100));
	InteractBox_Rotunda->SetRelativeLocation(FVector(0, 0, 0));

	//////////////////////////////////////
	// TREETOP RUNE

	Rune_Treetop = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Rune_Treetop"));
	Rune_Treetop->SetStaticMesh(SM_Rune_Treetop);
	Rune_Treetop->SetupAttachment(Root);
	Rune_Treetop->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	TreetopFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("TreetopFX"));
	TreetopFX->Template = P_TreetopFX;
	TreetopFX->bAutoActivate = false;
	TreetopFX->SetupAttachment(Rune_Treetop);

	TreetopAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("TreetopAudio"));
	TreetopAudio->Sound = S_TreetopAudio;
	TreetopAudio->bAutoActivate = false;
	TreetopAudio->SetupAttachment(Rune_Treetop);
	
	PointLight_Treetop = ObjectInitializer.CreateDefaultSubobject<UPointLightComponent>(this, TEXT("PointLight_Treetop"));
	PointLight_Treetop->SetupAttachment(Rune_Treetop);

	InteractBox_Treetop = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("InteractBox_Treetop"));
	InteractBox_Treetop->SetupAttachment(Rune_Treetop);
	InteractBox_Treetop->SetBoxExtent(FVector(100, 100, 100));
	InteractBox_Treetop->SetRelativeLocation(FVector(0, 0, 0));

	///////////////////////////////////////
	// YGGDRASIL - WORLD TREE	

	TreeBase = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("TreeBase"));
	TreeBase->SetupAttachment(Root);

	TreeTrunk = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("TreeTrunk"));
	TreeTrunk->SetStaticMesh(SM_TreeTrunk);
	TreeTrunk->SetupAttachment(TreeBase);
	TreeTrunk->SetRelativeScale3D(FVector(16, 16, 19));

	TreeBranches = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("TreeBranches"));
	TreeBranches->SetStaticMesh(SM_TreeBranches);
	TreeBranches->SetupAttachment(TreeBase);
	TreeBranches->SetRelativeLocation(FVector(1265, 1953, 1819));
	TreeBranches->SetRelativeRotation(FRotator(-2, -33, 10));

	TreeHead = ObjectInitializer.CreateDefaultSubobject<UDestructibleComponent>(this, TEXT("TreeHead"));	
	TreeHead->SetupAttachment(TreeBase);
	TreeHead->SetRelativeLocation(FVector(223, 1162, -63));
	TreeHead->SetRelativeRotation(FRotator(0, 0, 22));

	HeadExplosionAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("HeadExplosionAudio"));
	HeadExplosionAudio->Sound = S_HeadExplosionAudio;
	HeadExplosionAudio->bAutoActivate = false;
	HeadExplosionAudio->SetupAttachment(TreeBase);

	LeftEyeFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("LeftEyeFX"));
	LeftEyeFX->Template = P_LeftEyeFX;
	LeftEyeFX->bAutoActivate = true;
	LeftEyeFX->SetupAttachment(HeadExplosionAudio);

	PointLight_LeftEye = ObjectInitializer.CreateDefaultSubobject<UPointLightComponent>(this, TEXT("PointLight_LeftEye"));
	PointLight_LeftEye->SetupAttachment(LeftEyeFX);
	PointLight_LeftEye->SetupAttachment(HeadExplosionAudio);

	RightEyeFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("RightEyeFX"));
	RightEyeFX->Template = P_RightEyeFX;
	RightEyeFX->bAutoActivate = true;
	RightEyeFX->SetupAttachment(HeadExplosionAudio);

	PointLight_RightEye = ObjectInitializer.CreateDefaultSubobject<UPointLightComponent>(this, TEXT("PointLight_RightEye"));
	PointLight_RightEye->SetupAttachment(RightEyeFX);
	PointLight_RightEye->SetupAttachment(HeadExplosionAudio);

	EnergyPillarFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("EnergyPillarFX"));
	EnergyPillarFX->Template = P_EnergyPillarFX;
	EnergyPillarFX->bAutoActivate = false;
	EnergyPillarFX->SetupAttachment(TreeBase);

	PillarAuraFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("PillarAuraFX"));
	PillarAuraFX->Template = P_PillarAuraFX;
	PillarAuraFX->bAutoActivate = false;
	PillarAuraFX->SetupAttachment(EnergyPillarFX);

	LiftIndicatorFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("LiftIndicatorFX"));
	LiftIndicatorFX->Template = P_LiftIndicatorFX;
	LiftIndicatorFX->bAutoActivate = false;
	LiftIndicatorFX->SetupAttachment(EnergyPillarFX);

	EnergyChargeAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("EnergyChargeAudio"));
	EnergyChargeAudio->Sound = S_EnergyChargeAudio;
	EnergyChargeAudio->bAutoActivate = false;
	EnergyChargeAudio->SetupAttachment(EnergyPillarFX);

	AuraAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("AuraAudio"));
	AuraAudio->Sound = S_AuraAudio;
	AuraAudio->bAutoActivate = false;
	AuraAudio->SetupAttachment(EnergyPillarFX);	
}

// Called when the game starts or when spawned
void AYggdrasil_Runes::BeginPlay()
{
	Super::BeginPlay();

	DoInteraction.AddDynamic(this, &AYggdrasil_Runes::CustomInteract);

	InteractBox_Alcove->OnComponentBeginOverlap.AddDynamic(this, &AYggdrasil_Runes::Entered_Alcove);
	InteractBox_Rotunda->OnComponentBeginOverlap.AddDynamic(this, &AYggdrasil_Runes::Entered_Rotunda);
	InteractBox_Treetop->OnComponentBeginOverlap.AddDynamic(this, &AYggdrasil_Runes::Entered_Treetop);

	// add the destructible rock after a short delay... thanks 4.18 for moving apex destructibles into a plugin so they load super slow now
	FTimerHandle DestructibleAddTimer;
	GetWorldTimerManager().SetTimer(DestructibleAddTimer, this, &AYggdrasil_Runes::AddDestructible, 2.0f, false);
}

void AYggdrasil_Runes::AddDestructible()
{
	DM_TreeHead = Cast<UDestructibleMesh>(StaticLoadObject(UDestructibleMesh::StaticClass(), NULL, TEXT("DestructibleMesh'/Game/Environment/DestructibleMeshes/RTS_Env_Fire_NordHeed01_DM.RTS_Env_Fire_NordHeed01_DM'")));
	TreeHead->SetDestructibleMesh(DM_TreeHead);
}

// Interact with this NPC
void AYggdrasil_Runes::CustomInteract()
{
	InteractWithRune();

	// The rest of this code is in the related Blueprint instance.
}

void AYggdrasil_Runes::Entered_Alcove(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!Active_Alcove)
	{
		if (Cast<AEtherealPlayerMaster>(OtherActor))
		{
			InteractingPlayer = Cast<AEtherealPlayerMaster>(OtherActor);
			CheckIfUsable();
			CurrentRune = ECurrentRune::CR_Alcove;
		}
	}	
}

void AYggdrasil_Runes::Entered_Rotunda(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!Active_Rotunda)
	{
		if (Cast<AEtherealPlayerMaster>(OtherActor))
		{
			InteractingPlayer = Cast<AEtherealPlayerMaster>(OtherActor);
			CheckIfUsable();
			CurrentRune = ECurrentRune::CR_Rotunda;
		}
	}	
}

void AYggdrasil_Runes::Entered_Treetop(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!Active_Treetop)
	{
		if (Cast<AEtherealPlayerMaster>(OtherActor))
		{
			InteractingPlayer = Cast<AEtherealPlayerMaster>(OtherActor);
			CheckIfUsable();
			CurrentRune = ECurrentRune::CR_Treetop;
		}
	}	
}

void AYggdrasil_Runes::InteractWithRune_Implementation()
{
}

void AYggdrasil_Runes::ResetRuneInteraction_Implementation()
{
}
