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
#include "ClothShoes.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AClothShoes::AClothShoes(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_ClothBoots.ArmorIcon_ClothBoots'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_ClothBoots-small.ArmorIcon_ClothBoots-small'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmorMeshObject(TEXT("SkeletalMesh'/Game/EtherealParty/Morgan/Clothes/ClothArmor/ClothShoes/Morgan_ClothShoes.Morgan_ClothShoes'"));

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_ArmorMesh = ArmorMeshObject.Object;
	ArmorMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("ArmorMesh"));
	ArmorMesh->SetSkeletalMesh(SK_ArmorMesh);
	ArmorMesh->SetupAttachment(RootComponent);
	UCommonLibrary::SetupSKComponentsWithCollision(ArmorMesh);
	
	// Set Default Values
	Name = EMasterGearList::GL_ClothShoes;
	NameText = LOCTEXT("ClothShoesName", "Cloth Shoes");
	Type = EMasterGearTypes::GT_Feet;
	TypeText = LOCTEXT("ClothShoesType", "Feet");
	Description = "Armor of Ethereal Squires.";
	Price = 1500;
	MPCost = 0;
	ATK = 0;
	DEF = 1;
	SPD = 0;
	HP = 10;
	MP = 0;
}

// Called when the game starts or when spawned
void AClothShoes::BeginPlay()
{
	Super::BeginPlay();
}

#undef LOCTEXT_NAMESPACE
