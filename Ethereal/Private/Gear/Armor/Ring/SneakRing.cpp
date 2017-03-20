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
#include "SneakRing.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
ASneakRing::ASneakRing(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_SneakRing.ArmorIcon_SneakRing'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_SneakRing-small.ArmorIcon_SneakRing-small'"));

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;
	
	// Set Default Values
	Name = EMasterGearList::GL_SneakRing;
	NameText = LOCTEXT("SneakRingName", "Sneak Ring");
	Type = EMasterGearTypes::GT_Ring;
	TypeText = LOCTEXT("SneakRingType", "Ring");
	Description = "Ring of an Ethereal Spy.";
	Price = 45000;
	MPCost = 0;
	ATK = 10;
	DEF = 10;
	SPD = 10;
	HP = -999;
	MP = -500;
	SpecialEffectText = LOCTEXT("SneakRingSpecialEffect", "+ Sneak");
}

// Called when the game starts or when spawned
void ASneakRing::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &ASneakRing::DoSpecialEffect);
	OnRemoveGear.AddDynamic(this, &ASneakRing::RemoveSpecialEffect);
}


// Custom code for Special Effect
void ASneakRing::DoSpecialEffect()
{
	OwnerReference->HasSneak = true;
}

// Custom code for Special Effect
void ASneakRing::RemoveSpecialEffect()
{
	OwnerReference->HasSneak = false;
}

#undef LOCTEXT_NAMESPACE
