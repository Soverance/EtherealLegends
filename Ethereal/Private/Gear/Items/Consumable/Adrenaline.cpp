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
#include "Adrenaline.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AAdrenaline::AAdrenaline(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/Sounds/Stingers/Mono/StingerPickup_Health_Cue.StingerPickup_Health_Cue'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleObject(TEXT("ParticleSystem'/Game/Elemental/Effects/Fx_Magic/Effects/FX_Knight_Hammer_Prefire.FX_Knight_Hammer_Prefire'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Adrenaline.ItemIcon_Adrenaline'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Adrenaline-small.ItemIcon_Adrenaline-small'"));

	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;
	S_ItemAudio = AudioObject.Object;
	ItemAudio->Sound = S_ItemAudio;
	P_ItemFX = ParticleObject.Object;
	ItemFX->Template = P_ItemFX;

	Name = EMasterGearList::GL_Adrenaline;
	NameText = LOCTEXT("AdrenalineName", "Adrenaline");
	Type = EMasterGearTypes::GT_Consumable;	
	TypeText = LOCTEXT("AdrenalineType", "Consumable");
	Effect = "+ 20% ATK for 120 Seconds";
	Description = "Grants an attack boost for a limited time.";
	Price = 1500;
	Quantity = 1;
}

// Called when the game starts or when spawned
void AAdrenaline::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	OnItemUse.AddDynamic(this, &AAdrenaline::Use);
}

void AAdrenaline::Use()
{
	ItemAudio->Play();
	ItemFX->Activate();

	// This check prevents multiple uses of this item from stacking the effect
	if (!OwnerReference->EtherealPlayerController->Active_Adrenaline)
	{		
		OwnerReference->EtherealPlayerController->ActivateStatus_Adrenaline();
	}	
}

#undef LOCTEXT_NAMESPACE
