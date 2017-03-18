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
#include "CrimsonHelm.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
ACrimsonHelm::ACrimsonHelm(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_CrimsonHelm.ArmorIcon_CrimsonHelm'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_CrimsonHelm-small.ArmorIcon_CrimsonHelm-small'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmorMeshObject(TEXT("SkeletalMesh'/Game/EtherealParty/Morgan/Clothes/CrimsonArmor/CrimsonHelm/CrimsonHelm.CrimsonHelm'"));

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_ArmorMesh = ArmorMeshObject.Object;
	ArmorMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("ArmorMesh"));
	ArmorMesh->SetSkeletalMesh(SK_ArmorMesh);
	ArmorMesh->SetupAttachment(RootComponent);
	UCommonLibrary::SetupSKComponentsWithCollision(ArmorMesh);
	
	// Set Default Values
	Name = EMasterGearList::GL_CrimsonHelm;
	NameText = LOCTEXT("CrimsonHelmName", "Crimson Helm");
	Type = EMasterGearTypes::GT_Head;
	TypeText = LOCTEXT("CrimsonHelmType", "Head");
	Description = "Armor of Ethereal Regents.";
	Price = 35000;
	MPCost = 0;
	ATK = 10;
	DEF = 15;
	SPD = 8;
	HP = 100;
	MP = 50;
	SpecialEffectText = LOCTEXT("CrimsonHelmSpecialEffect", "Refresh +10.");
}

// Called when the game starts or when spawned
void ACrimsonHelm::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &ACrimsonHelm::DoSpecialEffect);
	OnRemoveGear.AddDynamic(this, &ACrimsonHelm::RemoveSpecialEffect);
}

// Custom code for Special Effect
void ACrimsonHelm::DoSpecialEffect()
{
	OwnerReference->EtherealPlayerState->RefreshRate = (OwnerReference->EtherealPlayerState->RefreshRate + 10);
}

// Custom code for Special Effect
void ACrimsonHelm::RemoveSpecialEffect()
{
	OwnerReference->EtherealPlayerState->RefreshRate = (OwnerReference->EtherealPlayerState->RefreshRate - 10);
}

#undef LOCTEXT_NAMESPACE
