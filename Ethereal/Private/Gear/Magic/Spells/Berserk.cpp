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
#include "Berserk.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
ABerserk::ABerserk(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/Audio/Party/BerserkCast_Cue.BerserkCast_Cue'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> CastParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Ability/Heal/P_BerserkCast.P_BerserkCast'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> ChargeParticleObject(TEXT("ParticleSystem'/Game/Blueprints/Gear/Magic/SpellEffects/Particles/ChargeFX/ChargeParticle.ChargeParticle'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/berserk.berserk'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/berserk-small.berserk-small'"));

	// Set Default Values
	Name = EMasterGearList::GL_Berserk;
	NameText = LOCTEXT("BerserkName", "Berserk");
	Type = EMasterGearTypes::GT_Support;
	TypeText = LOCTEXT("BerserkType", "Support");
	Description = "Temporarily increase ATK, boosting attack damage by 25%.";
	Price = 15000;
	MPCost = 45;
	ATK = 10;
	DEF = -25;
	SPD = 5;
	HP = 250;
	MP = -50;
	Duration = 60;
	CastTime = 30;
	CritMultiplier = 0.25f;
	HasteMultiplier = 0;
	DefenseMultiplier = 0;
	TargetType = EMagic_TargetTypes::TT_Player;
	AnimType = EMagic_AnimTypes::AT_ForwardBlast;

	// Set Default Objects
	S_CastAudio = AudioObject.Object;
	P_CastFX = CastParticleObject.Object;
	P_ChargeFX = ChargeParticleObject.Object;
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	CastAudio->Sound = S_CastAudio;
	CastFX->Template = P_CastFX;
	ChargeFX->Template = P_ChargeFX;

	ChargeFX->SetColorParameter("Color", FLinearColor(1, 0, 0, 1));  // Set Charge Particle Color RED
}

// Called when the game starts or when spawned
void ABerserk::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	QuitCharging.AddDynamic(this, &ABerserk::Cancel);
}

void ABerserk::Cancel()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Berserk casting was cancelled.");
}

void ABerserk::ChargeBerserk()
{
	IsCharging = true; // Set Charging State True
	ChargeFX->Activate();  // Activate the charge particle
	 // Get player mesh and attach this object
	Root->AttachToComponent(OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "PowerSocket");
}

void ABerserk::CastBerserk()
{
	// TO DO:  Get player controller and set Berserk Status on BattleHUD

	IsCharging = false;
	IsCasting = true;
	ChargeFX->Deactivate(); // Deactivate Charge particle
	CastAudio->Play(); // Play Cast Audio
	CastFX->Activate(); // Activate Cast FX particle
	OwnerReference->EtherealPlayerController->ActivateStatus_Berserk();  // Activate Haste Status Effect

	// Get the ATK boost and store it for later use
	StoredATKBoost = OwnerReference->EtherealPlayerState->ATK * CritMultiplier;
	// Add the ATK Boost to the Player's current ATK.
	OwnerReference->EtherealPlayerState->ATK = OwnerReference->EtherealPlayerState->ATK + StoredATKBoost; 

	// Do the Cast effect after a short delay
	FTimerHandle CastTimer;
	GetWorldTimerManager().SetTimer(CastTimer, this, &ABerserk::RemoveCastEffect, Duration, false);
}

void ABerserk::RemoveCastEffect()
{
	// Remove the ATK Boost from the Player's current ATK.
	OwnerReference->EtherealPlayerState->ATK = OwnerReference->EtherealPlayerState->ATK - StoredATKBoost; 
}

#undef LOCTEXT_NAMESPACE
