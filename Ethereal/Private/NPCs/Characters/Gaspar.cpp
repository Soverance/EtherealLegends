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
#include "Gaspar.h"

AGaspar::AGaspar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> NPCMesh(TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/Mixamo/gaspar.gaspar'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/InfinityBladeWarriors/Character/Mixamo/AnimBP_Gaspar.AnimBP_Gaspar_C'"));
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

	ShopIndex = 3;  // ARMOR SHOP
	IsUsable = true;
	InteractAnimType = EInteractAnims::IA_Talk;

	DoInteract.AddDynamic(this, &AGaspar::Interact);
	DisableShop.AddDynamic(this, &AGaspar::DisableArmorShop);
}

// Called when the game starts or when spawned
void AGaspar::BeginPlay()
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
void AGaspar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Interact with this NPC
void AGaspar::Interact()
{	
	IsUsable = false;

	if (!InteractWidget) // only run this code if the widget does not exist
	{
		InteractWidget = CreateWidget<UUserWidget>(GetWorld(), W_InteractWidget);  // creates the widget
		EnableArmorShop();  // Enable Armor Shop
		Shrug = true;
	}
	if (InteractWidget)
	{
		bool InViewport = InteractWidget->IsInViewport();

		if (!InViewport)
		{
			EnableArmorShop();  // Enable Armor Shop
		}	
	}
}

// Enable the Armor Shop widget
void AGaspar::EnableArmorShop()
{
	UShop* ArmorShop = Cast<UShop>(InteractWidget);

	if (ArmorShop)
	{
		ArmorShop->OwnerNPC = this;  // Set Owner NPC Reference
		ArmorShop->ShopIndex = ShopIndex;  // Set Shop Index
		ArmorShop->AddToViewport();  // Add Magic Shop to Viewport
		InteractingPlayer->EtherealGameInstance->CurrentState = EGameStates::GS_Shop;  // put game into shop state
	}
}

// Disabled the Interact Widget associated with this NPC
void AGaspar::DisableArmorShop()
{
	InteractWidget->RemoveFromViewport();
	InteractingPlayer->EtherealGameInstance->CurrentState = EGameStates::GS_Playing;  // put game into playing state
	IsUsable = true;
	Yawn = true;
}

void AGaspar::SpawnDefaultShopItems()
{
	TArray<EMasterGearList> DefaultShopList;  // Create Shop Inventory List

	// ARMOR

	// Leather
	EMasterGearList Armor0 = EMasterGearList::GL_LeatherCap;
	DefaultShopList.AddUnique(Armor0);
	EMasterGearList Armor1 = EMasterGearList::GL_LeatherVest;
	DefaultShopList.AddUnique(Armor1);
	EMasterGearList Armor2 = EMasterGearList::GL_LeatherGloves;
	DefaultShopList.AddUnique(Armor2);
	EMasterGearList Armor3 = EMasterGearList::GL_LeatherChaps;
	DefaultShopList.AddUnique(Armor3);
	EMasterGearList Armor4 = EMasterGearList::GL_LeatherBoots;
	DefaultShopList.AddUnique(Armor4);

	//EMasterGearList Armor5 = EMasterGearList::GL_ClothCape;
	//DefaultShopList.AddUnique(Armor5);

	EMasterGearList Armor6 = EMasterGearList::GL_SilverRing;
	DefaultShopList.AddUnique(Armor6);

	// Adaman
	EMasterGearList Armor7 = EMasterGearList::GL_AdamanHelm;
	DefaultShopList.AddUnique(Armor7);
	EMasterGearList Armor8 = EMasterGearList::GL_AdamanCuirass;
	DefaultShopList.AddUnique(Armor8);
	EMasterGearList Armor9 = EMasterGearList::GL_AdamanGauntlets;
	DefaultShopList.AddUnique(Armor9);
	EMasterGearList Armor10 = EMasterGearList::GL_AdamanCuisses;
	DefaultShopList.AddUnique(Armor10);
	EMasterGearList Armor11 = EMasterGearList::GL_AdamanSabatons;
	DefaultShopList.AddUnique(Armor11);

	//EMasterGearList Armor12 = EMasterGearList::GL_KnightsCape;
	//DefaultShopList.AddUnique(Armor12);

	EMasterGearList Armor13 = EMasterGearList::GL_DarksteelRing;
	DefaultShopList.AddUnique(Armor13);

	// War
	EMasterGearList Armor14 = EMasterGearList::GL_WarHelm;
	DefaultShopList.AddUnique(Armor14);
	EMasterGearList Armor15 = EMasterGearList::GL_WarCoat;
	DefaultShopList.AddUnique(Armor15);
	EMasterGearList Armor16 = EMasterGearList::GL_WarGloves;
	DefaultShopList.AddUnique(Armor16);
	EMasterGearList Armor17 = EMasterGearList::GL_WarBrais;
	DefaultShopList.AddUnique(Armor17);
	EMasterGearList Armor18 = EMasterGearList::GL_WarBoots;
	DefaultShopList.AddUnique(Armor18);
	
	EMasterGearList Armor20 = EMasterGearList::GL_ShadowRing;
	DefaultShopList.AddUnique(Armor20);

	// Crusader
	EMasterGearList Armor21 = EMasterGearList::GL_CrusaderHelm;
	DefaultShopList.AddUnique(Armor21);
	EMasterGearList Armor22 = EMasterGearList::GL_CrusaderTabard;
	DefaultShopList.AddUnique(Armor22);
	EMasterGearList Armor23 = EMasterGearList::GL_CrusaderMitts;
	DefaultShopList.AddUnique(Armor23);
	EMasterGearList Armor24 = EMasterGearList::GL_CrusaderChain;
	DefaultShopList.AddUnique(Armor24);
	EMasterGearList Armor25 = EMasterGearList::GL_CrusaderSandals;
	DefaultShopList.AddUnique(Armor25);

	EMasterGearList Armor19 = EMasterGearList::GL_SneakRing;
	DefaultShopList.AddUnique(Armor19);

	// Assassins
	EMasterGearList Armor26 = EMasterGearList::GL_AssassinsHood;
	DefaultShopList.AddUnique(Armor26);
	EMasterGearList Armor27 = EMasterGearList::GL_AssassinsVest;
	DefaultShopList.AddUnique(Armor27);
	EMasterGearList Armor28 = EMasterGearList::GL_AssassinsCuffs;
	DefaultShopList.AddUnique(Armor28);
	EMasterGearList Armor29 = EMasterGearList::GL_AssassinsBrais;
	DefaultShopList.AddUnique(Armor29);
	EMasterGearList Armor30 = EMasterGearList::GL_AssassinsBoots;
	DefaultShopList.AddUnique(Armor30);

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
