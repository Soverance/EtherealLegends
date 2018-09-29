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
#include "Gear/EtherealGearMaster.h"
#include "Widgets/Shop.h"
#include "Priest.h"

APriest::APriest(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> NPCMesh(TEXT("SkeletalMesh'/Game/EtherealParty/OldWizard/OldWizard.OldWizard'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/OldWizard/Anim_OldWizard.Anim_OldWizard_C'"));
	static ConstructorHelpers::FClassFinder<UUserWidget> Widget(TEXT("/Game/Blueprints/Widgets/BP_Shop"));

	// Set Default Objects
	SM_Mesh = NPCMesh.Object;
	W_InteractWidget = Widget.Class;

	// Create objects
	Mesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetAnimInstanceClass(AnimBP.Object);
	Mesh->SkeletalMesh = SM_Mesh;
	Mesh->SetRelativeScale3D(FVector(0.15f, 0.15f, 0.15f));
	Mesh->bCastCapsuleIndirectShadow = true;

	ShopIndex = 1;  // MAGIC SHOP
	IsUsable = true;
	InteractAnimType = EInteractAnims::IA_Talk;

	DoInteraction.AddDynamic(this, &APriest::CustomInteract);
	DisableShop.AddDynamic(this, &APriest::DisableMagicShop);
}

// Called when the game starts or when spawned
void APriest::BeginPlay()
{
	Super::BeginPlay();

	// This usually wouldn't be necessary, since we collect this reference when the player enters the NPC's collider.
	// However, we require the reference to draw debug lines for the map, and the player may access the map before having interacting with this actor
	for (TActorIterator<AEtherealPlayerMaster> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		InteractingPlayer = *ActorItr; // get the instance of the Player
	}

	SpawnDefaultShopItems();  // Spawn the Shop's default items.
}

// Called every frame
void APriest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Interact with this NPC
void APriest::CustomInteract()
{	
	IsUsable = false;

	// if the widget does not yet exist....
	if (!InteractWidget)
	{
		InteractWidget = CreateWidget<UUserWidget>(GetWorld(), W_InteractWidget);  // creates the widget
		EnableMagicShop();  // Enable Magic Shop
		Shrug = true;
	}
	// if the widget already exists in scene
	if (InteractWidget)
	{
		bool InViewport = InteractWidget->IsInViewport();

		if (!InViewport)
		{
			EnableMagicShop();  // Enable Magic Shop
		}	
	}
}

// Enable the Magic Shop widget
void APriest::EnableMagicShop()
{
	UShop* MagicShop = Cast<UShop>(InteractWidget);

	if (MagicShop)
	{
		MagicShop->OwnerNPC = this;  // Set Owner NPC Reference
		MagicShop->ShopIndex = ShopIndex;  // Set Shop Index
		MagicShop->AddToViewport();  // Add Magic Shop to Viewport
		InteractingPlayer->EtherealGameInstance->CurrentState = EGameStates::GS_Shop;  // put game into shop state
	}
}

// Disabled the Interact Widget associated with this NPC
void APriest::DisableMagicShop()
{
	InteractWidget->RemoveFromViewport();
	InteractingPlayer->EtherealGameInstance->CurrentState = EGameStates::GS_Playing;  // put game into playing state
	IsUsable = true;
	Yawn = true;
}

void APriest::SpawnDefaultShopItems()
{
	TArray<EMasterGearList> DefaultShopList;  // Create Shop Inventory List

	// MAGIC
	EMasterGearList Magic0 = EMasterGearList::GL_Cure2;
	DefaultShopList.AddUnique(Magic0);
	EMasterGearList Magic1 = EMasterGearList::GL_Regen;
	DefaultShopList.AddUnique(Magic1);
	EMasterGearList Magic2 = EMasterGearList::GL_Refresh;
	DefaultShopList.AddUnique(Magic2);
	EMasterGearList Magic3 = EMasterGearList::GL_Fire;
	DefaultShopList.AddUnique(Magic3);
	EMasterGearList Magic4 = EMasterGearList::GL_Blizzard;
	DefaultShopList.AddUnique(Magic4);
	EMasterGearList Magic5 = EMasterGearList::GL_Thunder;
	DefaultShopList.AddUnique(Magic5);
	EMasterGearList Magic6 = EMasterGearList::GL_Berserk;
	DefaultShopList.AddUnique(Magic6);
	EMasterGearList Magic7 = EMasterGearList::GL_Barrier;
	DefaultShopList.AddUnique(Magic7);
	EMasterGearList Magic8 = EMasterGearList::GL_Haste;
	DefaultShopList.AddUnique(Magic8);
	EMasterGearList Magic9 = EMasterGearList::GL_Dash;
	DefaultShopList.AddUnique(Magic9);
	EMasterGearList Magic10 = EMasterGearList::GL_Return;
	DefaultShopList.AddUnique(Magic10);

	for (EMasterGearList Item : DefaultShopList)  // for each item in the inventory...
	{
		// check to see if the item already exists in the player's inventory
		AEtherealGearMaster* GearAlreadyOwned = InteractingPlayer->EtherealPlayerState->GetInventoryItem(Item);

		// if the item is not already in the player's inventory, create it, and add it to the Shop's inventory for the player to purchase.
		if (!GearAlreadyOwned)
		{
			AEtherealGearMaster* Gear = UCommonLibrary::CreateGear(this, Item, FName(TEXT("Arcadia")), this->GetActorLocation(), this->GetActorRotation()); // create the new item

			if (Gear)
			{
				Gear->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("ItemSocket"));  // attach gear to NPC
				ShopInventory.AddUnique(Gear);  // Add gear into the Priest's Shop Inventory
			}
		}
	}
}
