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
#include "Reraise.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AReraise::AReraise(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/Audio/Party/Ethereal_Altar_Cue.Ethereal_Altar_Cue'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Cines/Ausar/P_Reraise.P_Reraise'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Revive.ItemIcon_Revive'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Revive-small.ItemIcon_Revive-small'"));

	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;
	S_ItemAudio = AudioObject.Object;
	ItemAudio->Sound = S_ItemAudio;
	P_ItemFX = ParticleObject.Object;
	ItemFX->Template = P_ItemFX;

	Name = EMasterGearList::GL_Reraise;
	NameText = LOCTEXT("ReraiseName", "Reraise");
	Type = EMasterGearTypes::GT_Consumable;
	TypeText = LOCTEXT("ReraiseType", "Consumable");
	Effect = "+ Reraise Effect for 60 minutes";
	Description = "The power of the phoenix, granting life after death.";
	Price = 3000;
	Quantity = 1;
}

// Called when the game starts or when spawned
void AReraise::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	OnItemUse.AddDynamic(this, &AReraise::Use);
}

void AReraise::Use()
{
	if (OwnerReference)
	{
		// If the player already has the reraise effect active, then using this item results in an error
		if (OwnerReference->HasReraise)
		{
			FText DisplayText = LOCTEXT("ReraiseFailed", "NO EFFECT!");
			OwnerReference->CombatTextComponent->ShowCombatText(ECombatTextTypes::TT_Text, DisplayText);  // error notify
			OwnerReference->AudioManager->Play_SFX_Error();  // error notify
		}
		// if the player does not yet have reraise active, we'll make it active.
		else
		{			
			OwnerReference->HasReraise = true;
			ItemAudio->Play();
			OwnerReference->EtherealPlayerController->ActivateStatus_Reraise();
		}
	}	
}

#undef LOCTEXT_NAMESPACE
