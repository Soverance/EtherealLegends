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
#include "Iraphise.h"

AIraphise::AIraphise(const FObjectInitializer& ObjectInitializer)
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

	ShopIndex = 2;  // WEAPON SHOP
	IsUsable = true;
	InteractAnimType = EInteractAnims::IA_Talk;

	DoInteract.AddDynamic(this, &AIraphise::Interact);
	DisableShop.AddDynamic(this, &AIraphise::DisableWeaponShop);
}

// Called when the game starts or when spawned
void AIraphise::BeginPlay()
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
void AIraphise::Tick(float DeltaTime)
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
void AIraphise::Interact()
{	
	IsUsable = false;

	if (!InteractWidget) // only run this code if the widget does not exist
	{
		InteractWidget = CreateWidget<UUserWidget>(GetWorld(), W_InteractWidget);  // creates the widget
		EnableWeaponShop();  // Enable Weapon Shop
		Shrug = true;
	}
	if (InteractWidget)
	{
		bool InViewport = InteractWidget->IsInViewport();

		if (!InViewport)
		{
			EnableWeaponShop();  // Enable Weapon Shop
		}	
	}
}

// Enable the Weapon Shop widget
void AIraphise::EnableWeaponShop()
{
	UShop* WeaponShop = Cast<UShop>(InteractWidget);

	if (WeaponShop)
	{
		WeaponShop->OwnerNPC = this;  // Set Owner NPC Reference
		WeaponShop->ShopIndex = ShopIndex;  // Set Shop Index
		WeaponShop->AddToViewport();  // Add Magic Shop to Viewport
		InteractingPlayer->EtherealGameInstance->CurrentState = EGameStates::GS_Shop;  // put game into shop state
	}
}

// Disabled the Interact Widget associated with this NPC
void AIraphise::DisableWeaponShop()
{
	InteractWidget->RemoveFromViewport();
	InteractingPlayer->EtherealGameInstance->CurrentState = EGameStates::GS_Playing;  // put game into playing state
	IsUsable = true;
	Yawn = true;
}

void AIraphise::SpawnDefaultShopItems()
{
	TArray<EMasterGearList> DefaultShopList;  // Create Shop Inventory List

	// WEAPONS

	// One-Handed
	EMasterGearList Weapon0 = EMasterGearList::GL_Joyeuse;
	DefaultShopList.AddUnique(Weapon0);
	EMasterGearList Weapon1 = EMasterGearList::GL_Hauteclaire;
	DefaultShopList.AddUnique(Weapon1);
	EMasterGearList Weapon2 = EMasterGearList::GL_BalloonSword;
	DefaultShopList.AddUnique(Weapon2);
	// Shields
	EMasterGearList Weapon3 = EMasterGearList::GL_SpartanShield;
	DefaultShopList.AddUnique(Weapon3);
	EMasterGearList Weapon4 = EMasterGearList::GL_DiablosDread;
	DefaultShopList.AddUnique(Weapon4);
	// Two-Handed
	EMasterGearList Weapon5 = EMasterGearList::GL_Juggernaut;
	DefaultShopList.AddUnique(Weapon5);
	EMasterGearList Weapon6 = EMasterGearList::GL_Claymore;
	DefaultShopList.AddUnique(Weapon6);
	EMasterGearList Weapon7 = EMasterGearList::GL_Marauder;
	DefaultShopList.AddUnique(Weapon7);
	// Ranged
	EMasterGearList Weapon8 = EMasterGearList::GL_ShortBow;
	DefaultShopList.AddUnique(Weapon8);
	EMasterGearList Weapon9 = EMasterGearList::GL_EagleEye;
	DefaultShopList.AddUnique(Weapon9);
	EMasterGearList Weapon10 = EMasterGearList::GL_EurytosBow;
	DefaultShopList.AddUnique(Weapon10);
	// Ammunition
	EMasterGearList Weapon11 = EMasterGearList::GL_WoodenArrow;
	DefaultShopList.AddUnique(Weapon11);
	EMasterGearList Weapon12 = EMasterGearList::GL_IronArrow;
	DefaultShopList.AddUnique(Weapon12);
	EMasterGearList Weapon13 = EMasterGearList::GL_FlameArrow;
	DefaultShopList.AddUnique(Weapon13);

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
