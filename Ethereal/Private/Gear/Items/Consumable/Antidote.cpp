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
#include "Antidote.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AAntidote::AAntidote(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/Audio/Party/Consumable_Antidote_Cue.Consumable_Antidote_Cue'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleObject(TEXT("ParticleSystem'/Game/EtherealParty/OldWizard/Effects/Item_UseAntidote.Item_UseAntidote'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Antidote.ItemIcon_Antidote'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Antidote-small.ItemIcon_Antidote-small'"));

	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;
	S_ItemAudio = AudioObject.Object;
	ItemAudio->Sound = S_ItemAudio;
	P_ItemFX = ParticleObject.Object;
	ItemFX->Template = P_ItemFX;

	Name = EMasterGearList::GL_Antidote;
	NameText = LOCTEXT("AntidoteName", "Antidote");
	Type = EMasterGearTypes::GT_Consumable;
	TypeText = LOCTEXT("AntidoteType", "Consumable");
	Effect = "- Poison";
	Description = "Negates the effects of Poison.";
	Price = 50;
	Quantity = 1;
}

// Called when the game starts or when spawned
void AAntidote::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	OnItemUse.AddDynamic(this, &AAntidote::Use);
}

void AAntidote::Use()
{
	ItemAudio->Play();
	ItemFX->Activate();
	OwnerReference->EtherealPlayerController->RemoveStatus_Poison();
}

#undef LOCTEXT_NAMESPACE
