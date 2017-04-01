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
#include "Drops/DropRefresh.h"
#include "Refresh.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets Default Values
ARefresh::ARefresh(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	ConstructorHelpers::FObjectFinder<USoundCue> AudioObject(TEXT("SoundCue'/Game/Audio/Party/RefreshCast_Cue.RefreshCast_Cue'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> CastParticleObject(TEXT("ParticleSystem'/Game/Blueprints/Gear/Magic/SpellEffects/Particles/Spell_Refresh.Spell_Refresh'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> ChargeParticleObject(TEXT("ParticleSystem'/Game/Blueprints/Gear/Magic/SpellEffects/Particles/ChargeFX/ChargeParticle.ChargeParticle'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/refresh.refresh'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/refresh-small.refresh-small'"));

	// Set Default Values
	Name = EMasterGearList::GL_Refresh;
	NameText = LOCTEXT("RefreshName", "Refresh");
	Type = EMasterGearTypes::GT_White;
	TypeText = LOCTEXT("RefreshType", "White Magic");
	Description = "Restores a significant portion of MP over time.";
	Price = 20000;
	MPCost = 95;
	ATK = 0;
	DEF = 5;
	SPD = 0;
	HP = 200;
	MP = 20;
	Duration = 60;
	CastTime = 40;
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
	ChargeFX->SetColorParameter("Color", FLinearColor(0.29f, 0.67f, 0.85f, 1));  // Set Charge Particle Color BLUE
}

// Called when the game starts or when spawned
void ARefresh::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	QuitCharging.AddDynamic(this, &ARefresh::Cancel);	
}

void ARefresh::Cancel()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Refresh casting was cancelled.");
}

void ARefresh::ChargeRefresh()
{
	IsCharging = true; // Set Charging State True	
	ChargeFX->Activate();  // Activate the charge particle
	// Get player mesh and attach this object
	Root->AttachToComponent(OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "PowerSocket");
}

void ARefresh::CastRefresh()
{
	ChargeFX->Deactivate(); // Deactivate Charge particle
	CastAudio->Play();  // Play Cast Audio

	ADropRefresh* RefreshDrop = GetWorld()->SpawnActor<ADropRefresh>();  // spawn the regen drop

	if (RefreshDrop)
	{
		RefreshDrop->AttachToComponent(OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "PowerSocket");  // attach it to player
	}

	OwnerReference->EtherealPlayerController->ActivateStatus_Refresh();  // Activate the Regen Status Effect

	// Do the Cast effect after a short delay
	FTimerHandle CastTimer;
	GetWorldTimerManager().SetTimer(CastTimer, this, &ARefresh::DoCastEffect, 1.2f, false);
}

void ARefresh::DoCastEffect()
{
	CastFX->Activate();
}

