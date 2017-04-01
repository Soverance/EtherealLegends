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
#include "HiPotion.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AHiPotion::AHiPotion(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/Audio/Party/Ethereal_Elixer_Cue.Ethereal_Elixer_Cue'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleObject(TEXT("ParticleSystem'/Game/EtherealParty/OldWizard/Effects/Item_UsePotion.Item_UsePotion'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Hi-Potion.ItemIcon_Hi-Potion'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Hi-Potion-small.ItemIcon_Hi-Potion-small'"));

	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;
	S_ItemAudio = AudioObject.Object;
	ItemAudio->Sound = S_ItemAudio;
	P_ItemFX = ParticleObject.Object;
	ItemFX->Template = P_ItemFX;

	Name = EMasterGearList::GL_HiPotion;
	NameText = LOCTEXT("HiPotionName", "Hi-Potion");
	Type = EMasterGearTypes::GT_Consumable;
	TypeText = LOCTEXT("HiPotionType", "Consumable");
	Effect = "+ 65% of Max HP";
	Description = "Restores a moderate portion of HP.";
	Price = 500;
	Quantity = 1;
}

// Called when the game starts or when spawned
void AHiPotion::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	OnItemUse.AddDynamic(this, &AHiPotion::Use);
}

void AHiPotion::Use()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "An Item Was Used.");
	ItemFX->Activate();
	ItemAudio->Play();
	float CureAmount = OwnerReference->EtherealPlayerState->HP_Max * 0.65f;
	OwnerReference->EtherealPlayerState->HP_Current = OwnerReference->EtherealPlayerState->HP_Current + CureAmount;
	OwnerReference->EtherealPlayerState->ForceHPCaps();
	OwnerReference->CombatTextComponent->ShowCombatText(ECombatTextTypes::TT_CritHP, UCommonLibrary::GetFloatAsTextWithPrecision(CureAmount, 0, false));
	OwnerReference->EtherealPlayerController->ActivateStatus_Heal();
}

#undef LOCTEXT_NAMESPACE
