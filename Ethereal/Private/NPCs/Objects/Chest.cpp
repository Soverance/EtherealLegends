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
#include "Gear/EtherealGearMaster.h"
#include "Chest.h"

#define LOCTEXT_NAMESPACE "EtherealText"

AChest::AChest(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh(TEXT("StaticMesh'/Game/InfinityBladeFireLands/Environments/Forge/Env_Forge/StaticMesh/SM_Forge_Chest_Bottom.SM_Forge_Chest_Bottom'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> LidMesh(TEXT("StaticMesh'/Game/InfinityBladeFireLands/Environments/Forge/Env_Forge/StaticMesh/SM_Forge_Chest_Top.SM_Forge_Chest_Top'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> OpenAudioObject(TEXT("SoundCue'/Game/Audio/Cave/Ethereal_ChestOpen_Cue.Ethereal_ChestOpen_Cue'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> OpenParticle(TEXT("ParticleSystem'/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh'"));
	static ConstructorHelpers::FObjectFinder<UClass> OpenCamShakeObject(TEXT("Blueprint'/Game/Blueprints/CamShakes/CS_OpenChest.CS_OpenChest_C'"));
	static ConstructorHelpers::FClassFinder<UUserWidget> Widget(TEXT("/Game/Blueprints/Widgets/BP_ChestDisplay"));
	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/Weapons/Novelty/Curve_BeamSaber.Curve_BeamSaber'"));

	// Set Default Objects
	SM_Base = BaseMesh.Object;
	SM_Lid = LidMesh.Object;
	S_OpenAudio = OpenAudioObject.Object;
	P_OpenFX = OpenParticle.Object;
	W_InteractWidget = Widget.Class;
	OpenCurve = Curve.Object;
	OpenCamShake = OpenCamShakeObject.Object;

	Root->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	InteractBox->SetBoxExtent(FVector(120, 120, 100));
	
	// Create objects
	Base = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Base"));
	Base->SetupAttachment(Root);
	Base->SetStaticMesh(SM_Base);

	LidRoot = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("LidRoot"));
	LidRoot->SetupAttachment(Base);
	LidRoot->SetRelativeLocation(FVector(34, 0, 50));

	Lid = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Lid"));
	Lid->SetupAttachment(LidRoot);
	Lid->SetStaticMesh(SM_Lid);
	Lid->SetRelativeLocation(FVector(-34, 0, 0));
	Lid->SetRelativeRotation(FRotator(0, -180, 0));

	OpenAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("OpenAudio"));
	OpenAudio->SetupAttachment(Root);
	OpenAudio->Sound = S_OpenAudio;
	OpenAudio->bAutoActivate = false;

	OpenFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("OpenFX"));
	OpenFX->SetupAttachment(Root);
	OpenFX->Template = P_OpenFX;
	OpenFX->bAutoActivate = false;
	OpenFX->SetRelativeLocation(FVector(-36, 0, 3));
	OpenFX->SetRelativeScale3D(FVector(1, 0.6f, 1));

	OpenTimeline = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("OpenTimeline"));
	InterpFunction.BindUFunction(this, FName{ TEXT("TimelineFloatReturn") });

	IsUsable = true;
	InteractAnimType = EInteractAnims::IA_Kick;
	ItemInChest = EMasterGearList::GL_None;  // set variable on instance in map
	GoldInChest = 0;  // variable gets set randomly, below

	DoInteract.AddDynamic(this, &AChest::Interact);
}

// Called when the game starts or when spawned
void AChest::BeginPlay()
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
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Draw Debug Cylinder on Map
	if (InteractingPlayer->MapControl)
	{
		if (IsUsable)
		{
			FVector DebugStart = GetActorLocation();
			FVector DebugEnd = FVector(DebugStart.X, DebugStart.Y, (DebugStart.Z + 1500));

			DrawDebugCylinder(GetWorld(), DebugStart, DebugEnd, 10, 12, FColor::Emerald, false, 0, 0);
		}		
	}
}

// Interact with this NPC
void AChest::Interact()
{
	if (IsUsable)
	{
		IsUsable = false;
		// Open chest during the kick animation
		FTimerHandle ChestTimer;
		GetWorldTimerManager().SetTimer(ChestTimer, this, &AChest::OnChestTouched, 0.5f, false);
	}
}

// Called when this chest is touched by the player
void AChest::OnChestTouched()
{
	OpenAudio->Play();
	OpenFX->Activate();
	
	OpenTimeline->AddInterpFloat(OpenCurve, InterpFunction, FName{ TEXT("Float") });
	OpenTimeline->PlayFromStart();

	UGameplayStatics::PlayWorldCameraShake(GetWorld(), OpenCamShake, InteractingPlayer->GetActorLocation(), 0, 10000, 1, false);  // level up cam shake

	// since there isn't really a "Gold" item in the MasterGearList, you can just set chests to "NONE" and have them give gold instead of an item
	if (ItemInChest == EMasterGearList::GL_None)
	{
		AddGold();
	}
	else
	{
		AddItem();
	}
}

// Player obtains Gold
void AChest::AddGold()
{
	GoldInChest = FMath::RandRange(500, 5000);
	InteractingPlayer->EtherealPlayerState->AddGold(GoldInChest);
	
	// Get the Gold Amount and convert it to text
	FText GoldAmt = UCommonLibrary::GetFloatAsTextWithPrecision(GoldInChest, 0, false);

	// Format the text for proper display in the widget
	FFormatNamedArguments Arguments;
	Arguments.Add(TEXT("DisplayText"), GoldAmt);
	FText FormattedDesc = FText::Format(LOCTEXT("ChestGoldText", "Obtained :  {DisplayText} Gold"), Arguments);

	// wait a half second before showing the widget, passing in the description of the item in this chest.
	FTimerDelegate DelegateWidget;
	DelegateWidget.BindUFunction(this, FName("ShowWidget"), FormattedDesc);
	FTimerHandle WidgetTimer;
	GetWorldTimerManager().SetTimer(WidgetTimer, DelegateWidget, 0.5f, false);
}

// Player obtains Item
void AChest::AddItem()
{
	// Check to see if the player already has the item
	AEtherealGearMaster* Item = InteractingPlayer->EtherealPlayerState->GetInventoryItem(ItemInChest);

	if (Item)
	{
		if (Item->Type == EMasterGearTypes::GT_Consumable)
		{
			GiveItem();  // Item was found, but it's consumable, so add it anyway
		}
		else
		{
			AddGold(); // player already has the item in inventory, so add gold instead
		}		
	}
	else
	{
		GiveItem();  // item was not found in inventory, so give it to the player
	}
}

// Show Widget
void AChest::ShowWidget(FText Description)
{
	if (!InteractWidget) // only run this code if the widget does not exist
	{
		InteractWidget = CreateWidget<UChestDisplay>(GetWorld(), W_InteractWidget);  // creates the widget
		InteractWidget->Description = Description;
		InteractWidget->AddToViewport();
	}
	else
	{
		if (!InteractWidget->IsInViewport()) // if the widget exists, check to be sure it is not already in the viewport
		{
			InteractWidget->AddToViewport(); // if not, add it to the viewport
		}
	}
}

// Show Widget
void AChest::GiveItem()
{
	InteractingPlayer->EtherealPlayerState->AddToInventory(ItemInChest, false, false);  // Add item from chest to player inventory

	FText DropName = InteractingPlayer->EtherealPlayerState->GetInventoryItem(ItemInChest)->NameText;

	// Format the text for proper display in the widget
	FFormatNamedArguments Arguments;
	Arguments.Add(TEXT("DisplayText"), DropName);
	FText FormattedDesc = FText::Format(LOCTEXT("ChestItemText", "Obtained :  {DisplayText}"), Arguments);

	// wait a half second before showing the widget, passing in the description of the item in this chest.
	FTimerDelegate DelegateWidget;
	DelegateWidget.BindUFunction(this, FName("ShowWidget"), FormattedDesc);
	FTimerHandle WidgetTimer;
	GetWorldTimerManager().SetTimer(WidgetTimer, DelegateWidget, 0.5f, false);
}

// Open Timeline
void AChest::TimelineFloatReturn(float val)
{
	LidRoot->SetRelativeRotation(FRotator(FMath::FInterpTo(0, -180, val, 0.3f), 0, 0));
}

#undef LOCTEXT_NAMESPACE
