// © 2014 - 2017 Soverance Studios
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
#include "HuntersCoat.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AHuntersCoat::AHuntersCoat(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_HuntersCoat.ArmorIcon_HuntersCoat'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_HuntersCoat-small.ArmorIcon_HuntersCoat-small'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmorMeshObject(TEXT("SkeletalMesh'/Game/EtherealParty/Morgan/Clothes/HuntersGarb/HuntersCoat/HuntersCoat.HuntersCoat'"));

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_ArmorMesh = ArmorMeshObject.Object;
	ArmorMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("ArmorMesh"));
	ArmorMesh->SetSkeletalMesh(SK_ArmorMesh);
	ArmorMesh->SetupAttachment(RootComponent);
	UCommonLibrary::SetupSKComponentsWithCollision(ArmorMesh);
	
	// Set Default Values
	Name = EMasterGearList::GL_HuntersCoat;
	NameText = LOCTEXT("HuntersCoatName", "Hunters Coat");
	Type = EMasterGearTypes::GT_Body;
	TypeText = LOCTEXT("HuntersCoatType", "Body");
	Description = "Armor of Ethereal Hunters.";
	Price = 45000;
	MPCost = 0;
	ATK = 17;
	DEF = 5;
	SPD = 5;
	HP = 50;
	MP = 25;
	SpecialEffectText = LOCTEXT("HuntersCoatSpecialEffect", "Occasionally annulls all damage taken.");
}

// Called when the game starts or when spawned
void AHuntersCoat::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &AHuntersCoat::DoSpecialEffect);
	OnRemoveGear.AddDynamic(this, &AHuntersCoat::RemoveSpecialEffect);
}

// Custom code for Special Effect
void AHuntersCoat::DoSpecialEffect()
{
	OwnerReference->HasShadowGear = true;
}

// Custom code for Special Effect
void AHuntersCoat::RemoveSpecialEffect()
{
	OwnerReference->HasShadowGear = false;
}

#undef LOCTEXT_NAMESPACE
