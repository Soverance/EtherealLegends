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
#include "HiEther.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AHiEther::AHiEther(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/Audio/Party/Barrier_Active_Cue.Barrier_Active_Cue'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleObject(TEXT("ParticleSystem'/Game/EtherealParty/OldWizard/Effects/Item_UseEther.Item_UseEther'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Hi-Ether.ItemIcon_Hi-Ether'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ItemIcon_Hi-Ether-small.ItemIcon_Hi-Ether-small'"));

	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;
	S_ItemAudio = AudioObject.Object;
	ItemAudio->Sound = S_ItemAudio;
	P_ItemFX = ParticleObject.Object;
	ItemFX->Template = P_ItemFX;

	Name = EMasterGearList::GL_HiEther;
	NameText = LOCTEXT("HiEtherName", "Hi-Ether");
	Type = EMasterGearTypes::GT_Consumable;
	TypeText = LOCTEXT("HiEtherType", "Consumable");
	Effect = "+ 65% of Max MP";
	Description = "Restores a moderate portion of MP.";
	Price = 1000;
	Quantity = 1;
}

// Called when the game starts or when spawned
void AHiEther::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	OnItemUse.AddDynamic(this, &AHiEther::Use);
}

void AHiEther::Use()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "An Item Was Used.");
	ItemFX->Activate();
	ItemAudio->Play();
	float CureAmount = OwnerReference->EtherealPlayerState->MP_Max * 0.65f;
	OwnerReference->EtherealPlayerState->MP_Current = OwnerReference->EtherealPlayerState->MP_Current + CureAmount;
	OwnerReference->EtherealPlayerState->ForceMPCaps();
	OwnerReference->CombatTextComponent->ShowCombatText(ECombatTextTypes::TT_CritMP, UCommonLibrary::GetFloatAsTextWithPrecision(CureAmount, 0, false));
}

#undef LOCTEXT_NAMESPACE
