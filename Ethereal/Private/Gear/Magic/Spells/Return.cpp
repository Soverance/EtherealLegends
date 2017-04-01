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
#include "Return.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AReturn::AReturn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/Audio/Party/Eth_Teleport_Cue.Eth_Teleport_Cue'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CastParticleObject(TEXT("ParticleSystem'/Game/Particles/P_Sov_Sorceress_Detonate.P_Sov_Sorceress_Detonate'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ChargeParticleObject(TEXT("ParticleSystem'/Game/Blueprints/Gear/Magic/SpellEffects/Particles/ChargeFX/ChargeParticle.ChargeParticle'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/return.return'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/return-small.return-small'"));

	// Set Default Values
	Name = EMasterGearList::GL_Return;
	NameText = LOCTEXT("ReturnName", "Return");
	Type = EMasterGearTypes::GT_Support;
	TypeText = LOCTEXT("ReturnType", "Support");
	Description = "Teleport to the current Realm's entrance.";
	Price = 1000;
	MPCost = 100;
	ATK = 0;
	DEF = 0;
	SPD = 0;
	HP = 0;
	MP = 0;
	Duration = 0;
	CastTime = 100;
	CritMultiplier = 0;
	HasteMultiplier = 0;
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
void AReturn::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	QuitCharging.AddDynamic(this, &AReturn::Cancel);
}

void AReturn::Cancel()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Haste casting was cancelled.");
}


void AReturn::ChargeReturn()
{
	IsCharging = true; // Set Charging State True
	ChargeFX->SetColorParameter("Color", FColor::Purple);  // Set Charge Particle Color
	ChargeFX->Activate();  // Activate the charge particle
	 // Get player mesh and attach this object
	Root->AttachToComponent(OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "PowerSocket");
}

void AReturn::CastReturn()
{
	IsCharging = false;
	IsCasting = true;
	ChargeFX->Deactivate(); // Deactivate Charge particle
	//CastAudio->Play(); // Play Cast Audio
	CastFX->Activate(); // Activate Cast FX particle
	OwnerReference->TeleportReturn(false);
}