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
#include "Haste.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AHaste::AHaste(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/EtherealParty/OldWizard/Audio/Absolut_Haste_Cue.Absolut_Haste_Cue'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> CastParticleObject(TEXT("ParticleSystem'/Game/Elemental/Effects/Fx_Magic/Effects/FX_Knight_Hammer_Powerup.FX_Knight_Hammer_Powerup'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> ChargeParticleObject(TEXT("ParticleSystem'/Game/Blueprints/Gear/Magic/SpellEffects/Particles/ChargeFX/ChargeParticle.ChargeParticle'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/haste.haste'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/haste-small.haste-small'"));

	// Set Default Values
	Name = EMasterGearList::GL_Haste;
	NameText = LOCTEXT("HasteName", "Haste");
	Type = EMasterGearTypes::GT_Support;
	TypeText = LOCTEXT("HasteType", "Support");
	Description = "Temporarily increase SPD, improving cast time and movement speed by 20%.";
	Price = 25000;
	MPCost = 60;
	ATK = 0;
	DEF = 0;
	SPD = 20;
	HP = -240;
	MP = -40;
	Duration = 60;
	CastTime = 40;
	CritMultiplier = 0;
	HasteMultiplier = 0.20f;
	DefenseMultiplier = 0;
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
}

// Called when the game starts or when spawned
void AHaste::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	QuitCharging.AddDynamic(this, &AHaste::Cancel);
}

void AHaste::Cancel()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Haste casting was cancelled.");
}


void AHaste::ChargeHaste()
{
	IsCharging = true; // Set Charging State True
	ChargeFX->SetColorParameter("Color", FLinearColor(1, 0.33f, 0, 1));  // Set Charge Particle Color
	ChargeFX->Activate();  // Activate the charge particle
	 // Get player mesh and attach this object
	Root->AttachToComponent(OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "PowerSocket");
}

void AHaste::CastHaste()
{
	// TO DO:  Create Dynamic Material Instances and set the Scalar Parameter Value "HasteAlpha" in order to fade in/out the particle effect using a timeline

	IsCharging = false;
	IsCasting = true;
	ChargeFX->Deactivate(); // Deactivate Charge particle
	CastAudio->Play(); // Play Cast Audio
	CastFX->Activate(); // Activate Cast FX particle
	OwnerReference->IsHasted = true;
	OwnerReference->EtherealPlayerController->ActivateStatus_Haste();  // Activate Haste Status Effect
	IncreaseSPD();

	// Remove the SPD Boost after the spell's Duration is complete
	FTimerHandle CastTimer;
	GetWorldTimerManager().SetTimer(CastTimer, this, &AHaste::DecreaseSPD, Duration, false);
}

void AHaste::IncreaseSPD()
{
	StoredSPDBoost = OwnerReference->EtherealPlayerState->SPD * HasteMultiplier;  // Define the SPD Boost amount
	OwnerReference->EtherealPlayerState->SPD = OwnerReference->EtherealPlayerState->SPD + StoredSPDBoost;  // Add the SPD Boost to the player's current SPD
	OwnerReference->SetMovementSpeed();  // set the player's movement speed	
}

void AHaste::DecreaseSPD()
{
	OwnerReference->IsHasted = false;
	OwnerReference->EtherealPlayerState->SPD = OwnerReference->EtherealPlayerState->SPD - StoredSPDBoost;  // Remove the SPD Boost from the player's current SPD
	// Set the player's Max Walk Speed back to normal
	OwnerReference->SetMovementSpeed();
}

