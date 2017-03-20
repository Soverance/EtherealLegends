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
#include "CrimsonGreaves.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
ACrimsonGreaves::ACrimsonGreaves(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_CrimsonGreaves.ArmorIcon_CrimsonGreaves'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_CrimsonGreaves-small.ArmorIcon_CrimsonGreaves-small'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmorMeshObject(TEXT("SkeletalMesh'/Game/EtherealParty/Morgan/Clothes/CrimsonArmor/CrimsonGreaves/CrimsonGreaves.CrimsonGreaves'"));

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_ArmorMesh = ArmorMeshObject.Object;
	ArmorMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("ArmorMesh"));
	ArmorMesh->SetSkeletalMesh(SK_ArmorMesh);
	ArmorMesh->SetupAttachment(RootComponent);
	UCommonLibrary::SetupSKComponentsWithCollision(ArmorMesh);
	
	// Set Default Values
	Name = EMasterGearList::GL_CrimsonGreaves;
	NameText = LOCTEXT("CrimsonGreavesName", "Crimson Greaves");
	Type = EMasterGearTypes::GT_Feet;
	TypeText = LOCTEXT("CrimsonGreavesType", "Feet");
	Description = "Armor of Ethereal Regents.";
	Price = 50000;
	MPCost = 0;
	ATK = 15;
	DEF = 10;
	SPD = 15;
	HP = 150;
	MP = 75;
	SpecialEffectText = LOCTEXT("CrimsonGreavesSpecialEffect", "Regen +10.");
}

// Called when the game starts or when spawned
void ACrimsonGreaves::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &ACrimsonGreaves::DoSpecialEffect);
	OnRemoveGear.AddDynamic(this, &ACrimsonGreaves::RemoveSpecialEffect);
}

// Custom code for Special Effect
void ACrimsonGreaves::DoSpecialEffect()
{
	OwnerReference->EtherealPlayerState->RefreshRate = (OwnerReference->EtherealPlayerState->RegenRate + 15);
}

// Custom code for Special Effect
void ACrimsonGreaves::RemoveSpecialEffect()
{
	OwnerReference->EtherealPlayerState->RefreshRate = (OwnerReference->EtherealPlayerState->RegenRate - 15);
}

#undef LOCTEXT_NAMESPACE
