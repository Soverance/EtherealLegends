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
#include "Characters/Player/EtherealPlayerMaster.h"
#include "Cure.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
ACure::ACure(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/EtherealParty/OldWizard/Audio/Absolut_Cure_Cue.Absolut_Cure_Cue'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CastParticleObject(TEXT("ParticleSystem'/Game/Blueprints/Gear/Magic/SpellEffects/Particles/Spell_Cure.Spell_Cure'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ChargeParticleObject(TEXT("ParticleSystem'/Game/Blueprints/Gear/Magic/SpellEffects/Particles/ChargeFX/ChargeParticle.ChargeParticle'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/cure.cure'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/cure-small.cure-small'"));

	// Set Default Values
	Name = EMasterGearList::GL_Cure;
	NameText = LOCTEXT("CureName", "Cure");
	Type = EMasterGearTypes::GT_White;
	TypeText = LOCTEXT("CureType", "White Magic");
	Description = "Restores a small amount of total HP.";
	Price = 5000;
	MPCost = 60;
	ATK = 0;
	DEF = 0;
	SPD = 20;
	HP = -40;
	MP = -40;
	Duration = 60;
	CastTime = 40;
	CritMultiplier = 1.5;
	HasteMultiplier = 0;
	DefenseMultiplier = 0.35f;
	TargetType = EMagic_TargetTypes::TT_Player;
	AnimType = EMagic_AnimTypes::AT_Standard;

	// Set Default Objects
	S_CastAudio = AudioObject.Object;
	P_CastFX = CastParticleObject.Object;
	P_ChargeFX = ChargeParticleObject.Object;
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	CastAudio->Sound = S_CastAudio;
	CastFX->Template = P_CastFX;
	ChargeFX->Template = P_ChargeFX;
	ChargeFX->SetColorParameter("Color", FLinearColor(0.2f, 1.0f, 0.3f, 1)); // GREEN
}

// Called when the game starts or when spawned
void ACure::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	QuitCharging.AddDynamic(this, &ACure::Cancel);

}

void ACure::Cancel()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Cure casting was cancelled.");
}

void ACure::ChargeCure()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, "Cure is charging.");
	IsCharging = true;
	ChargeFX->Activate();
}

void ACure::CastCure()
{
	ChargeFX->Deactivate();
	CastAudio->Play();

	// Do the Cast effect after a short delay
	FTimerHandle CastTimer;
	GetWorldTimerManager().SetTimer(CastTimer, this, &ACure::DoCastEffect, 1.3f, false);
}

void ACure::DoCastEffect()
{
	CastFX->Activate();
	
	if (OwnerReference->IsDead == false)
	{
		float MaxMultiplier = OwnerReference->EtherealPlayerState->HP_Max * DefenseMultiplier;  // Define Max multiplier for this spell, which is 35% of Max HP.
		float Crit = FMath::FRandRange(1.0f, CritMultiplier);  // Define max critical rate
		float CureAmount = FMath::FloorToInt(MaxMultiplier * Crit);  // Define total cure amount

		if (OwnerReference->BoostCurePotency > 0)
		{
			float BoostedPotency = CureAmount * OwnerReference->BoostCurePotency;
			CureAmount = CureAmount + BoostedPotency;  // Cure Potency +
		}

		OwnerReference->EtherealPlayerState->HP_Current = OwnerReference->EtherealPlayerState->HP_Current + CureAmount;  // Add Cure amount to Current HP
		OwnerReference->EtherealPlayerState->ForceHPCaps();  // Force HP Caps
		OwnerReference->EtherealPlayerController->ActivateStatus_Heal();  // Activate Heal Status Effect

		if (Crit >= 1.4f)
		{
			OwnerReference->CombatTextComponent->ShowCombatText(ECombatTextTypes::TT_CritHP, UCommonLibrary::GetFloatAsTextWithPrecision(CureAmount, 0, false));
		}
		else
		{
			OwnerReference->CombatTextComponent->ShowCombatText(ECombatTextTypes::TT_HP, UCommonLibrary::GetFloatAsTextWithPrecision(CureAmount, 0, false));
		}
	}


}

#undef LOCTEXT_NAMESPACE
