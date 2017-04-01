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
#include "SentinelBrew.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
ASentinelBrew::ASentinelBrew(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/Sounds/InterfaceAudio/Stereo/UI_PlayerRespawn_Stereo_Cue.UI_PlayerRespawn_Stereo_Cue'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Elemental/ICE/P_IceElementalSplit_Small.P_IceElementalSplit_Small'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_SentinelBrew.ItemIcon_SentinelBrew'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_SentinelBrew-small.ItemIcon_SentinelBrew-small'"));

	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;
	S_ItemAudio = AudioObject.Object;
	ItemAudio->Sound = S_ItemAudio;
	P_ItemFX = ParticleObject.Object;
	ItemFX->Template = P_ItemFX;

	Name = EMasterGearList::GL_SentinelBrew;
	NameText = LOCTEXT("SentinelBrewName", "Sentinel Brew");
	Type = EMasterGearTypes::GT_Consumable;
	TypeText = LOCTEXT("SentinelBrewType", "Consumable");
	Effect = "+ 20% DEF for 120 Seconds";
	Description = "Grants a defensive boost for a limited time.";
	Price = 1500;
	Quantity = 1;
}

// Called when the game starts or when spawned
void ASentinelBrew::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	OnItemUse.AddDynamic(this, &ASentinelBrew::Use);
}

void ASentinelBrew::Use()
{
	ItemAudio->Play();
	ItemFX->Activate();

	// This check prevents multiple uses of this item from stacking the effect
	if (!OwnerReference->EtherealPlayerController->Active_SentinelBrew)
	{	
		OwnerReference->EtherealPlayerController->ActivateStatus_Sentinel();
	}	
}

#undef LOCTEXT_NAMESPACE
