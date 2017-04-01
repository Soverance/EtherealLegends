// Ãƒâ€šÃ‚Â© 2014 - 2016 Soverance Studios
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
#include "CrusaderMitts.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
ACrusaderMitts::ACrusaderMitts(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_CrusaderMitts.ArmorIcon_CrusaderMitts'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_CrusaderMitts-small.ArmorIcon_CrusaderMitts-small'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmorMeshObject(TEXT("SkeletalMesh'/Game/EtherealParty/Morgan/Clothes/CrusaderArmor/CrusaderMitts/CrusaderMitts.CrusaderMitts'"));

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_ArmorMesh = ArmorMeshObject.Object;
	ArmorMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("ArmorMesh"));
	ArmorMesh->SetSkeletalMesh(SK_ArmorMesh);
	ArmorMesh->SetupAttachment(RootComponent);
	UCommonLibrary::SetupSKComponentsWithCollision(ArmorMesh);
	
	// Set Default Values
	Name = EMasterGearList::GL_CrusaderMitts;
	NameText = LOCTEXT("CrusaderMittsName", "Crusader Mitts");
	Type = EMasterGearTypes::GT_Hand;
	TypeText = LOCTEXT("CrusaderMittsType", "Hands");
	Description = "Armor of Ethereal Paladins.";
	Price = 20000;
	MPCost = 0;
	ATK = 4;
	DEF = 7;
	SPD = 4;
	HP = 60;
	MP = 30;
	SpecialEffectText = LOCTEXT("CrusaderMittsSpecialEffect", "Two Handed Damage +25%.");
}

// Called when the game starts or when spawned
void ACrusaderMitts::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &ACrusaderMitts::DoSpecialEffect);
	OnRemoveGear.AddDynamic(this, &ACrusaderMitts::RemoveSpecialEffect);
}

// Custom code for Special Effect
void ACrusaderMitts::DoSpecialEffect()
{
	OwnerReference->BoostTwoHanded = true;
}

// Custom code for Special Effect
void ACrusaderMitts::RemoveSpecialEffect()
{
	OwnerReference->BoostTwoHanded = false;
}

#undef LOCTEXT_NAMESPACE
