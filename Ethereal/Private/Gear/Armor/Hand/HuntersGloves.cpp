// © 2014 - 2016 Soverance Studios
// http://www.soverance.com

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, softHunterse
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT HuntersRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Ethereal.h"
#include "HuntersGloves.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AHuntersGloves::AHuntersGloves(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_HuntersGloves.ArmorIcon_HuntersGloves'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_HuntersGloves-small.ArmorIcon_HuntersGloves-small'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmorMeshObject(TEXT("SkeletalMesh'/Game/EtherealParty/Morgan/Clothes/HuntersGarb/HuntersGloves/HuntersGloves.HuntersGloves'"));

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_ArmorMesh = ArmorMeshObject.Object;
	ArmorMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("ArmorMesh"));
	ArmorMesh->SetSkeletalMesh(SK_ArmorMesh);
	ArmorMesh->SetupAttachment(RootComponent);
	UCommonLibrary::SetupSKComponentsWithCollision(ArmorMesh);
	
	// Set Default Values
	Name = EMasterGearList::GL_HuntersGloves;
	NameText = LOCTEXT("HuntersGlovesName", "Hunters Gloves");
	Type = EMasterGearTypes::GT_Hand;
	TypeText = LOCTEXT("HuntersGlovesType", "Hands");
	Description = "Armor of Ethereal Hunters.";
	Price = 20000;
	MPCost = 0;
	ATK = 5;
	DEF = 5;
	SPD = 5;
	HP = 100;
	MP = 50;
	SpecialEffectText = LOCTEXT("HuntersGlovesSpecialEffect", "Ranged Damage +25%.");
}

// Called when the game starts or when spawned
void AHuntersGloves::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &AHuntersGloves::DoSpecialEffect);
	OnRemoveGear.AddDynamic(this, &AHuntersGloves::RemoveSpecialEffect);
}

// Custom code for Special Effect
void AHuntersGloves::DoSpecialEffect()
{
	OwnerReference->BoostRanged = true;
}

// Custom code for Special Effect
void AHuntersGloves::RemoveSpecialEffect()
{
	OwnerReference->BoostRanged = false;
}

#undef LOCTEXT_NAMESPACE
