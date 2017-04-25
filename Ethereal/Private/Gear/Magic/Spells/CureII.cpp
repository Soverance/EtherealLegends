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
#include "Characters/Player/EtherealPlayerMaster.h"
#include "CureII.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
ACureII::ACureII(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/Blueprints/Gear/Magic/SpellEffects/Audio/Spell_CureII_Cue.Spell_CureII_Cue'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> CastParticleObject(TEXT("ParticleSystem'/Game/Blueprints/Gear/Magic/SpellEffects/Particles/P_CureII.P_CureII'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> ChargeParticleObject(TEXT("ParticleSystem'/Game/Blueprints/Gear/Magic/SpellEffects/Particles/ChargeFX/ChargeParticle.ChargeParticle'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/cure2.cure2'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/cure2-small.cure2-small'"));

	// Set Default Values
	Name = EMasterGearList::GL_Cure2;
	NameText = LOCTEXT("Cure2Name", "Cure II");
	Type = EMasterGearTypes::GT_White;
	TypeText = LOCTEXT("Cure2Type", "White Magic");
	Description = "Heals a significant portion of Max HP.";
	Price = 15000;
	MPCost = 150;
	ATK = 0;
	DEF = 0;
	SPD = 0;
	HP = -150;
	MP = 45;
	Duration = 4;
	CastTime = 35;
	CritMultiplier = 1.5f;
	HasteMultiplier = 0;
	DefenseMultiplier = 0.7f;
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
	CastFX->SetRelativeRotation(FRotator(31, -22, -117));
	ChargeFX->Template = P_ChargeFX;
	ChargeFX->SetColorParameter("Color", FLinearColor(0.2f, 1.0f, 0.3f, 1));

}

// Called when the game starts or when spawned
void ACureII::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	QuitCharging.AddDynamic(this, &ACureII::Cancel);
	
}

void ACureII::Cancel()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Cure II casting was cancelled.");
}

void ACureII::ChargeCureII()
{
	IsCharging = true; // Set Charging State True
	ChargeFX->SetColorParameter("Color", FLinearColor(0.2f, 1.0f, 0.3f, 1));  // Set Charge Particle Color
	ChargeFX->Activate();  // Activate the charge particle
	// Get player mesh and attach this object
	Root->AttachToComponent(OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "PowerSocket");

}

void ACureII::CastCureII()
{
	// TO DO: Get player controller and set Heal Status on BattleHUD

	ChargeFX->Deactivate();  // Deactivate Charge FX Particle
	
	// Do the Cast effect after a short delay
	FTimerHandle CastTimer;
	GetWorldTimerManager().SetTimer(CastTimer, this, &ACureII::DoCastEffect, 1.3f, false);
}

void ACureII::DoCastEffect()
{
	CastAudio->Play();  // Play Cast Audio
	CastFX->Activate();  // Activate Cast FX Particle

	if (OwnerReference->IsDead == false)
	{
		float MaxMultiplier = OwnerReference->EtherealPlayerState->HP_Max * DefenseMultiplier;  // Define Max multiplier for this spell.
		float Crit = FMath::FRandRange(1.0f, CritMultiplier);  // Define max critical rate
		float CureAmount = MaxMultiplier * Crit;  // Define total cure amount

		if (OwnerReference->BoostCurePotency > 0)
		{
			float BoostedPotency = CureAmount * OwnerReference->BoostCurePotency;
			CureAmount = CureAmount + BoostedPotency;  // Cure Potency +
		}

		OwnerReference->EtherealPlayerState->HP_Current = OwnerReference->EtherealPlayerState->HP_Current + CureAmount;  // Add Cure amount to Current HP
		OwnerReference->EtherealPlayerState->ForceHPCaps();  // Force HP Caps
		OwnerReference->EtherealPlayerController->ActivateStatus_Heal();

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
