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
#include "DefendingRing.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
ADefendingRing::ADefendingRing(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_DefendingRing.ArmorIcon_DefendingRing'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_DefendingRing-small.ArmorIcon_DefendingRing-small'"));

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;
	
	// Set Default Values
	Name = EMasterGearList::GL_DefendingRing;
	NameText = LOCTEXT("DefendingRingName", "Defending Ring");
	Type = EMasterGearTypes::GT_Ring;
	TypeText = LOCTEXT("DefendingRingType", "Ring");
	Description = "A sturdy ring carried only by the most stoic of Ethereal Knights.";
	Price = 100000;
	MPCost = 0;
	ATK = 0;
	DEF = 100;
	SPD = 0;
	HP = 999;
	MP = 0;
	SpecialEffectText = LOCTEXT("DefendingRingSpecialEffect", "Reduces damage taken by 50 %.");
}

// Called when the game starts or when spawned
void ADefendingRing::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &ADefendingRing::DoSpecialEffect);
	OnRemoveGear.AddDynamic(this, &ADefendingRing::RemoveSpecialEffect);
}


// Custom code for Special Effect
void ADefendingRing::DoSpecialEffect()
{
	OwnerReference->HasDefenseWall = true;
}

// Custom code for Special Effect
void ADefendingRing::RemoveSpecialEffect()
{
	OwnerReference->HasDefenseWall = false;
}

#undef LOCTEXT_NAMESPACE
