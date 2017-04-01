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
#include "ValhallaBreastplate.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AValhallaBreastplate::AValhallaBreastplate(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_ValhallaBreastplate.ArmorIcon_ValhallaBreastplate'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_ValhallaBreastplate-small.ArmorIcon_ValhallaBreastplate-small'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmorMeshObject(TEXT("SkeletalMesh'/Game/EtherealParty/Morgan/Clothes/ValhallaPlate/ValhallaBreastplate/ValhallaBreastplate.ValhallaBreastplate'"));

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_ArmorMesh = ArmorMeshObject.Object;
	ArmorMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("ArmorMesh"));
	ArmorMesh->SetSkeletalMesh(SK_ArmorMesh);
	ArmorMesh->SetupAttachment(RootComponent);
	UCommonLibrary::SetupSKComponentsWithCollision(ArmorMesh);
	
	// Set Default Values
	Name = EMasterGearList::GL_ValhallaBreastplate;
	NameText = LOCTEXT("ValhallaBreastplateName", "Valhalla Breastplate");
	Type = EMasterGearTypes::GT_Body;
	TypeText = LOCTEXT("ValhallaBreastplateType", "Body");
	Description = "Armor of Ethereal Guards.";
	Price = 35000;
	MPCost = 0;
	ATK = 10;
	DEF = 15;
	SPD = 8;
	HP = 100;
	MP = 50;
	SpecialEffectText = LOCTEXT("ValhallaBreastplateSpecialEffect", "+ Reraise Effect");
}

// Called when the game starts or when spawned
void AValhallaBreastplate::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &AValhallaBreastplate::DoSpecialEffect);
	OnRemoveGear.AddDynamic(this, &AValhallaBreastplate::RemoveSpecialEffect);
}

// Custom code for Special Effect
void AValhallaBreastplate::DoSpecialEffect()
{
	OwnerReference->HasReraise = true;
	OwnerReference->EtherealPlayerController->ActivateStatus_Reraise();
}

// Custom code for Special Effect
void AValhallaBreastplate::RemoveSpecialEffect()
{
	OwnerReference->HasReraise = true;
	OwnerReference->EtherealPlayerController->RemoveStatus_Reraise();
}

#undef LOCTEXT_NAMESPACE
