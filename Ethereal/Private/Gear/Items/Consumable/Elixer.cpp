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
#include "Elixer.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AElixer::AElixer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/Audio/Party/Ethereal_Elixer_Cue.Ethereal_Elixer_Cue'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleObject(TEXT("ParticleSystem'/Game/EtherealParty/OldWizard/Effects/Item_UseElixer.Item_UseElixer'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Elixer.ItemIcon_Elixer'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Elixer-small.ItemIcon_Elixer-small'"));

	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;
	S_ItemAudio = AudioObject.Object;
	ItemAudio->Sound = S_ItemAudio;
	P_ItemFX = ParticleObject.Object;
	ItemFX->Template = P_ItemFX;

	Name = EMasterGearList::GL_Elixer;
	NameText = LOCTEXT("ElixerName", "Elixer");
	Type = EMasterGearTypes::GT_Consumable;
	TypeText = LOCTEXT("ElixerType", "Consumable");
	Effect = "+ Full Restore";
	Description = "Instantly restores HP and MP to full capacity.";
	Price = 1500;
	Quantity = 1;	
}

// Called when the game starts or when spawned
void AElixer::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	OnItemUse.AddDynamic(this, &AElixer::Use);	
}

void AElixer::Use()
{
	ItemFX->Activate();
	ItemAudio->Play();
	OwnerReference->EtherealPlayerState->HP_Current = OwnerReference->EtherealPlayerState->HP_Max;
	OwnerReference->EtherealPlayerState->ForceHPCaps();
	OwnerReference->CombatTextComponent->ShowCombatText(ECombatTextTypes::TT_CritHP, UCommonLibrary::GetFloatAsTextWithPrecision(OwnerReference->EtherealPlayerState->HP_Max, 0, false));
	OwnerReference->EtherealPlayerState->MP_Current = OwnerReference->EtherealPlayerState->MP_Max;
	OwnerReference->EtherealPlayerState->ForceMPCaps();
	OwnerReference->CombatTextComponent->ShowCombatText(ECombatTextTypes::TT_CritMP, UCommonLibrary::GetFloatAsTextWithPrecision(OwnerReference->EtherealPlayerState->MP_Max, 0, false));
}

#undef LOCTEXT_NAMESPACE
