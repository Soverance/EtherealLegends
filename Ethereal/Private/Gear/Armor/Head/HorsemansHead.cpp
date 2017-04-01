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
#include "HorsemansHead.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AHorsemansHead::AHorsemansHead(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_HorsemansHead.ArmorIcon_HorsemansHead'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_HorsemansHead_small.ArmorIcon_HorsemansHead_small'"));
	
	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	// Set Default Values
	Name = EMasterGearList::GL_HorsemansHead;
	NameText = LOCTEXT("HorsemansHeadName", "Horseman's Head");
	Type = EMasterGearTypes::GT_Head;
	TypeText = LOCTEXT("HorsemansHeadType", "Head");
	Description = "A head said to have belonged to the Horseman himself. Great for scaring folks!";
	Price = 5000;
	MPCost = 0;
	ATK = 0;
	DEF = 0;
	SPD = 0;
	HP = 0;
	MP = 0;

}

// Called when the game starts or when spawned
void AHorsemansHead::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	//OnBindGear.AddDynamic(this, &AHorsemansHead::BindArmor);
	//OnRemoveGear.AddDynamic(this, &AHorsemansHead::UnbindArmor);
}


#undef LOCTEXT_NAMESPACE
