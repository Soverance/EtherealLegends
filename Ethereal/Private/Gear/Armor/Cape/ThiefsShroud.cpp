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
#include "ThiefsShroud.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AThiefsShroud::AThiefsShroud(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_ThiefsShroud.ArmorIcon_ThiefsShroud'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_ThiefsShroud-small.ArmorIcon_ThiefsShroud-small'"));

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;
	
	// Set Default Values
	Name = EMasterGearList::GL_ThiefsShroud;
	NameText = LOCTEXT("ThiefsShroudName", "Thief's Shroud");
	Type = EMasterGearTypes::GT_Cape;
	TypeText = LOCTEXT("ThiefsShroudType", "Cape");
	Description = "Makes your footsteps inaudible, preventing enemy detection from sound.";
	Price = 30000;
	MPCost = 0;
	ATK = 5;
	DEF = 5;
	SPD = 10;
	HP = 50;
	MP = 0;
}

// Called when the game starts or when spawned
void AThiefsShroud::BeginPlay()
{
	Super::BeginPlay();
}

#undef LOCTEXT_NAMESPACE
