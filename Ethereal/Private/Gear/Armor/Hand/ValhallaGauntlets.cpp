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
#include "ValhallaGauntlets.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AValhallaGauntlets::AValhallaGauntlets(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_ValhallaGauntlets.ArmorIcon_ValhallaGauntlets'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_ValhallaGauntlets-small.ArmorIcon_ValhallaGauntlets-small'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmorMeshObject(TEXT("SkeletalMesh'/Game/EtherealParty/Morgan/Clothes/ValhallaPlate/ValhallaGauntlets/ValhallaGauntlets.ValhallaGauntlets'"));

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_ArmorMesh = ArmorMeshObject.Object;
	ArmorMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("ArmorMesh"));
	ArmorMesh->SetSkeletalMesh(SK_ArmorMesh);
	ArmorMesh->SetupAttachment(RootComponent);
	UCommonLibrary::SetupSKComponentsWithCollision(ArmorMesh);
	
	// Set Default Values
	Name = EMasterGearList::GL_ValhallaGauntlets;
	NameText = LOCTEXT("ValhallaGauntletsName", "Valhalla Gauntlets");
	Type = EMasterGearTypes::GT_Hand;
	TypeText = LOCTEXT("ValhallaGauntletsType", "Hands");
	Description = "Armor of Ethereal Guards.";
	Price = 35000;
	MPCost = 0;
	ATK = 10;
	DEF = 15;
	SPD = 8;
	HP = 100;
	MP = 50;
	SpecialEffectText = LOCTEXT("ValhallaGauntletsSpecialEffect", "One Handed Damage +25%.");
}

// Called when the game starts or when spawned
void AValhallaGauntlets::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &AValhallaGauntlets::DoSpecialEffect);
	OnRemoveGear.AddDynamic(this, &AValhallaGauntlets::RemoveSpecialEffect);
}

// Custom code for Special Effect
void AValhallaGauntlets::DoSpecialEffect()
{
	OwnerReference->BoostOneHanded = true;
}

// Custom code for Special Effect
void AValhallaGauntlets::RemoveSpecialEffect()
{
	OwnerReference->BoostOneHanded = false;
}

#undef LOCTEXT_NAMESPACE
