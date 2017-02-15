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
#include "Management/GameStates.h"
#include "Characters/Player/EtherealPlayerMaster.h"
#include "Portal.h"

APortal::APortal(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh(TEXT("StaticMesh'/Game/Env/Infil1_City_Decos/Mesh/SM_Infil1_City_Roof_Trim_VarB_ColumnBaseDouble.SM_Infil1_City_Roof_Trim_VarB_ColumnBaseDouble'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> PortalAudioObject(TEXT("SoundCue'/Game/Audio/Impacts/PortalExplosion_Cue.PortalExplosion_Cue'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> HolosphereParticle(TEXT("ParticleSystem'/Game/Effects/Holograms/P_Hologram_Sculpture_01.P_Hologram_Sculpture_01'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> HolospireParticle(TEXT("ParticleSystem'/Game/Effects/Holograms/HologramSpire.HologramSpire'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> BurstParticle(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Ausar/P_AU_Trap_Impact.P_AU_Trap_Impact'"));
	static ConstructorHelpers::FClassFinder<UUserWidget> Widget(TEXT("/Game/Blueprints/Widgets/BP_RealmSelect"));

	// Set Default Objects
	SM_Base = BaseMesh.Object;
	S_PortalAudio = PortalAudioObject.Object;
	P_HolosphereFX = HolosphereParticle.Object;
	P_HolospireFX = HolospireParticle.Object;
	P_BurstFX = BurstParticle.Object;
	W_InteractWidget = Widget.Class;

	InteractBox->SetBoxExtent(FVector(100, 100, 100));  // scale up the interact box

	// Create objects
	Base = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Base"));
	Base->SetupAttachment(RootComponent);
	Base->SetStaticMesh(SM_Base);

	PortalAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("PortalAudio"));
	PortalAudio->SetupAttachment(RootComponent);
	PortalAudio->Sound = S_PortalAudio;
	PortalAudio->bAutoActivate = false;

	HolosphereFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("HolosphereFX"));
	HolosphereFX->SetupAttachment(RootComponent);
	HolosphereFX->Template = P_HolosphereFX;
	HolosphereFX->bAutoActivate = true;
	HolosphereFX->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	HolospireFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("HolospireFX"));
	HolospireFX->SetupAttachment(RootComponent);
	HolospireFX->Template = P_HolospireFX;
	HolospireFX->bAutoActivate = false;
	HolospireFX->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));

	BurstFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("BurstFX"));
	BurstFX->SetupAttachment(RootComponent);
	BurstFX->Template = P_BurstFX;
	BurstFX->bAutoActivate = false;
	BurstFX->SetRelativeScale3D(FVector(6.0f, 6.0f, 6.0f));

	IsUsable = true;
	InteractAnimType = EInteractAnims::IA_Open;

	DoInteract.AddDynamic(this, &APortal::Interact); // bind interact

	MapMarkerFX->SetColorParameter(FName(TEXT("BeamColor")), FColor::Purple);
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	// This usually wouldn't be necessary, since we collect this reference when the player enters the NPC's collider.
	// However, we require the reference to draw debug lines for the map, and the player may access the map before having interacting with this actor
	for (TActorIterator<AEtherealPlayerMaster> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		InteractingPlayer = *ActorItr; // get the instance of the Player
	}
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Do a Burst effect when the portal is activated
void APortal::DoBurstEffect()
{
	HolospireFX->Activate();
	BurstFX->Activate();
	PortalAudio->Play();
}

// Interact with this NPC
void APortal::Interact()
{
	IsUsable = false;

	if (!InteractWidget) // only run this code if the widget does not exist
	{
		InteractWidget = CreateWidget<UUserWidget>(GetWorld(), W_InteractWidget);  // creates the widget
		InteractWidget->AddToViewport();
		InteractingPlayer->EtherealGameInstance->CurrentState = EGameStates::GS_Menu;
	}
	if (InteractWidget)
	{
		bool InViewport = InteractWidget->IsInViewport();

		if (!InViewport)
		{
			InteractWidget->AddToViewport(); // if not, add it to the viewport
			InteractingPlayer->EtherealGameInstance->CurrentState = EGameStates::GS_Menu;
		}
	}
}

// Disabled the Interact Widget associated with this NPC
void APortal::DisableInteractWidget()
{
	InteractWidget->RemoveFromViewport();
	IsUsable = true;
	InteractingPlayer->EtherealGameInstance->CurrentState = EGameStates::GS_Playing;
}
