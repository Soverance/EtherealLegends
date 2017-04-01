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
#include "Drops/DropBarrier.h"
#include "Barrier.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
ABarrier::ABarrier(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ChargeParticleObject(TEXT("ParticleSystem'/Game/Blueprints/Gear/Magic/SpellEffects/Particles/ChargeFX/ChargeParticle.ChargeParticle'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CastParticleObject(TEXT("ParticleSystem'/Game/Elemental/Logo/FrozenLogo/_FX_LogoReveal_ICE._FX_LogoReveal_ICE'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/barrier.barrier'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/barrier-small.barrier-small'"));

	// Set Default Values
	Name = EMasterGearList::GL_Barrier;
	NameText = LOCTEXT("BarrierName", "Barrier");
	Type = EMasterGearTypes::GT_Support;
	TypeText = LOCTEXT("BarrierType", "Support");
	Description = "Raises DEF by 25% while standing within the effect radius.";
	Price = 15000;
	MPCost = 45;
	ATK = 0;
	DEF = 0;
	SPD = 0;
	HP = 100;
	MP = -50;
	Duration = 20;
	CastTime = 40;
	CritMultiplier = 0;
	HasteMultiplier = 0;
	DefenseMultiplier = 0.25f;
	TargetType = EMagic_TargetTypes::TT_Player;
	AnimType = EMagic_AnimTypes::AT_Standard;

	// Set Default Objects
	P_ChargeFX = ChargeParticleObject.Object;
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	ChargeFX->Template = P_ChargeFX;

	ChargeFX->SetColorParameter("Color", FLinearColor(0.14f, 0.30f, 1, 1));  // Set Charge Particle Color BLUE
}

// Called when the game starts or when spawned
void ABarrier::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	QuitCharging.AddDynamic(this, &ABarrier::Cancel);
		
}

void ABarrier::Cancel()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Barrier casting was cancelled.");
}

void ABarrier::ChargeBarrier()
{
	IsCharging = true; // Set Charging State True
	
	ChargeFX->Activate();  // Activate the charge particle
	// Get player mesh and attach this object
	Root->AttachToComponent(OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "PowerSocket");
}

void ABarrier::CastBarrier()
{
	ChargeFX->Deactivate(); // Deactivate Charge particle
	CastFX->Activate(); // Activate Cast FX particle

	// Do the Cast effect after a short delay
	FTimerHandle CastTimer;
	GetWorldTimerManager().SetTimer(CastTimer, this, &ABarrier::DoCastEffect, 1.3f, false);
}

void ABarrier::DoCastEffect()
{
	// Spawn the Barrier Drop at the player's location, passing it the DefenseMultiplier and Duration variables.
	ADropBarrier* NewBarrierDrop = GetWorld()->SpawnActor<ADropBarrier>(OwnerReference->GetActorLocation(), FRotator(0, 0, 0));
	NewBarrierDrop->DefenseMultiplier = DefenseMultiplier;
	NewBarrierDrop->Duration = Duration;
}

#undef LOCTEXT_NAMESPACE
