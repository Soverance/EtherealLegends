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
#include "Dash.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
ADash::ADash(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/Audio/Party/Dash1_Cue.Dash1_Cue'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> CastParticleObject(TEXT("ParticleSystem'/Game/Elemental/Logo/FrozenLogo/_FX_LogoReveal_ICE._FX_LogoReveal_ICE'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> ChargeParticleObject(TEXT("ParticleSystem'/Game/Blueprints/Gear/Magic/SpellEffects/Particles/ChargeFX/ChargeParticle.ChargeParticle'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/dash.dash'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/dash-small.dash-small'"));

	// Set Default Values
	Name = EMasterGearList::GL_Dash;
	NameText = LOCTEXT("DashName", "Dash");
	Type = EMasterGearTypes::GT_Ancient;
	TypeText = LOCTEXT("DashType", "Ancient");
	Description = "Quickly move forward in an evasive maneuver.";
	Price = 20000;
	MPCost = 35;
	ATK = 0;
	DEF = 0;
	SPD = 0;
	HP = 25;
	MP = 15;
	Duration = 0;
	CastTime = 0;
	CritMultiplier = 0;
	HasteMultiplier = 0;
	DefenseMultiplier = 0;
	TargetType = EMagic_TargetTypes::TT_Player;
	AnimType = EMagic_AnimTypes::AT_Dash;

	// Set Default Objects
	S_CastAudio = AudioObject.Object;
	P_CastFX = CastParticleObject.Object;
	P_ChargeFX = ChargeParticleObject.Object;
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	CastAudio->Sound = S_CastAudio;
	CastFX->Template = P_CastFX;
	ChargeFX->Template = P_ChargeFX;
	ChargeFX->SetColorParameter("Color", FLinearColor(0.29f, 0.67f, 0.85f, 1));  // Set Charge Particle Color BLUE
}

// Called when the game starts or when spawned
void ADash::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	QuitCharging.AddDynamic(this, &ADash::Cancel);
	
}

void ADash::Cancel()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Dash casting was cancelled.")
}


void ADash::ChargeDash()
{
	IsCharging = true; // Set Charging State True
	ChargeFX->Activate();  // Activate the charge particle
	// Get player mesh and attach this object
	Root->AttachToComponent(OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "PowerSocket");

}

void ADash::CastDash()
{
	// TO DO: Get player controller and set Heal Status on BattleHUD

	ChargeFX->Deactivate(); // Deactivate Charge particleCastAudio->Play();
	
	// Cannot cast Dash in the air
	if (OwnerReference->GetCharacterMovement()->IsFalling())
	{
		// return if the player is falling
		return;
	}
	else
	{
		CastAudio->Play();  // Play Cast Audio
		CastFX->Activate(true);  // Activate Cast FX
		FVector PlayerForward = OwnerReference->GetActorForwardVector();  // Get Player Forward Vector
		FVector Impulse = PlayerForward * 400;  // Multiply by the distance to go forward
		OwnerReference->GetCharacterMovement()->AddImpulse(Impulse);  // Add the distance as a movement impulse
	}
}

#undef LOCTEXT_NAMESPACE
