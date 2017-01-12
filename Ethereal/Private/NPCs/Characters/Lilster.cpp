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
#include "Widgets/Shop.h"
#include "Lilster.h"

ALilster::ALilster(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> NPCMesh(TEXT("SkeletalMesh'/Game/EtherealParty/Lilster/Lilster.Lilster'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/Lilster/Lilster_AnimBP.Lilster_AnimBP_C'"));
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

	ShopIndex = 0;  // CONSUMABLE ITEM SHOP
	IsUsable = true;
	InteractAnimType = EInteractAnims::IA_Talk;

	DoInteract.AddDynamic(this, &ALilster::Interact);
	DisableShop.AddDynamic(this, &ALilster::DisableConsumableShop);
}

// Called when the game starts or when spawned
void ALilster::BeginPlay()
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
void ALilster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Draw Debug Cylinder on Map
	if (InteractingPlayer->MapControl)
	{
		FVector DebugStart = GetActorLocation();
		FVector DebugEnd = FVector(DebugStart.X, DebugStart.Y, (DebugStart.Z + 1500));

		DrawDebugCylinder(GetWorld(), DebugStart, DebugEnd, 10, 12, FColor::Purple, false, 0, 0);
	}
}

// Interact with this NPC
void ALilster::Interact()
{	
	IsUsable = false;

	if (!InteractWidget) // only run this code if the widget does not exist
	{
		InteractWidget = CreateWidget<UUserWidget>(GetWorld(), W_InteractWidget);  // creates the widget
		EnableConsumableShop();  // Enable Consumable Shop
		Shrug = true;
	}
	if (InteractWidget)
	{
		bool InViewport = InteractWidget->IsInViewport();

		if (!InViewport)
		{
			Yawn = true;
			EnableConsumableShop();  // Enable Consumable Shop
		}	
	}
}

// Enable the Consumable Shop widget
void ALilster::EnableConsumableShop()
{
	UShop* ConsumableShop = Cast<UShop>(InteractWidget);

	if (ConsumableShop)
	{
		ConsumableShop->OwnerNPC = this;  // Set Owner NPC Reference
		ConsumableShop->ShopIndex = ShopIndex;  // Set Shop Index
		ConsumableShop->AddToViewport();  // Add Magic Shop to Viewport
		InteractingPlayer->EtherealGameInstance->CurrentState = EGameStates::GS_Shop;  // put game into shop state
	}
}

// Disabled the Interact Widget associated with this NPC
void ALilster::DisableConsumableShop()
{
	InteractWidget->RemoveFromViewport();
	InteractingPlayer->EtherealGameInstance->CurrentState = EGameStates::GS_Playing;  // put game into playing state
	IsUsable = true;
	GiveObject = true;
}

void ALilster::SpawnDefaultShopItems()
{
	TArray<EMasterGearList> DefaultShopList;  // Create Shop Inventory List

	// CONSUMABLE ITEMS
	EMasterGearList Consumable0 = EMasterGearList::GL_Potion;
	DefaultShopList.AddUnique(Consumable0);
	EMasterGearList Consumable1 = EMasterGearList::GL_HiPotion;
	DefaultShopList.AddUnique(Consumable1);
	EMasterGearList Consumable2 = EMasterGearList::GL_Ether;
	DefaultShopList.AddUnique(Consumable2);
	EMasterGearList Consumable3 = EMasterGearList::GL_HiEther;
	DefaultShopList.AddUnique(Consumable3);
	EMasterGearList Consumable4 = EMasterGearList::GL_Elixer;
	DefaultShopList.AddUnique(Consumable4);
	EMasterGearList Consumable5 = EMasterGearList::GL_Adrenaline;
	DefaultShopList.AddUnique(Consumable5);
	EMasterGearList Consumable6 = EMasterGearList::GL_SentinelBrew;
	DefaultShopList.AddUnique(Consumable6);
	EMasterGearList Consumable7 = EMasterGearList::GL_Antidote;
	DefaultShopList.AddUnique(Consumable7);
	EMasterGearList Consumable8 = EMasterGearList::GL_Reraise;
	DefaultShopList.AddUnique(Consumable8);

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
