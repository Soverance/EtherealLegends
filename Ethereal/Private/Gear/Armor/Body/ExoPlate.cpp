// Ã‚Â© 2014 - 2016 Soverance Studios
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
#include "ExoPlate.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AExoPlate::AExoPlate(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_ExoPlate.ArmorIcon_ExoPlate'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_ExoPlate-small.ArmorIcon_ExoPlate-small'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmorMeshObject(TEXT("SkeletalMesh'/Game/EtherealParty/Morgan/Clothes/ExoPlate/ExoPlate/ExoPlate.ExoPlate'"));

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_ArmorMesh = ArmorMeshObject.Object;
	ArmorMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("ArmorMesh"));
	ArmorMesh->SetSkeletalMesh(SK_ArmorMesh);
	ArmorMesh->SetupAttachment(RootComponent);
	UCommonLibrary::SetupSKComponentsWithCollision(ArmorMesh);
	
	// Set Default Values
	Name = EMasterGearList::GL_ExoPlate;
	NameText = LOCTEXT("ExoPlateName", "Exo Plate");
	Type = EMasterGearTypes::GT_Body;
	TypeText = LOCTEXT("ExoPlateType", "Body");
	Description = "Space Trooper Armor.";
	Price = 20000;
	MPCost = 0;
	ATK = 12;
	DEF = 10;
	SPD = 12;
	HP = 100;
	MP = 50;
	SpecialEffectText = LOCTEXT("ExoPlateSpecialEffect", "Weapon Damage +25%.");
}

// Called when the game starts or when spawned
void AExoPlate::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &AExoPlate::DoSpecialEffect);
	OnRemoveGear.AddDynamic(this, &AExoPlate::RemoveSpecialEffect);
}

// Custom code for Special Effect
void AExoPlate::DoSpecialEffect()
{
	OwnerReference->BoostOneHanded = true;
	OwnerReference->BoostTwoHanded = true;
	OwnerReference->BoostRanged = true;
}

// Custom code for Special Effect
void AExoPlate::RemoveSpecialEffect()
{
	OwnerReference->BoostOneHanded = false;
	OwnerReference->BoostTwoHanded = false;
	OwnerReference->BoostRanged = false;
}

#undef LOCTEXT_NAMESPACE
