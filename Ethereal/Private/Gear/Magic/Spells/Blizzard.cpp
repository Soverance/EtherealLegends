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
#include "Gear/Magic/Spells/Drops/DropBlizzard.h"
#include "Blizzard.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
ABlizzard::ABlizzard(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ChargeParticleObject(TEXT("ParticleSystem'/Game/Blueprints/Gear/Magic/SpellEffects/Particles/ChargeFX/ChargeParticle.ChargeParticle'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CastParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/Lightning/P_LineToPoint_Spawn_Proj_Lightning_00.P_LineToPoint_Spawn_Proj_Lightning_00'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/blizzard.blizzard'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/blizzard-small.blizzard-small'"));
	static ConstructorHelpers::FObjectFinder<UClass> DropBlueprintObject(TEXT("Blueprint'/Game/Blueprints/Gear/Magic/Spells/Drops/BlizzardDrop.BlizzardDrop_C'"));

	// Set Default Values
	Name = EMasterGearList::GL_Blizzard;
	NameText = LOCTEXT("BlizzardName", "Blizzard");
	Type = EMasterGearTypes::GT_Black;
	TypeText = LOCTEXT("BlizzardType", "Black Magic");
	Description = "Briefly encase a single target in a block of ice, halting their movement.";
	Price = 10000;
	MPCost = 60;
	ATK = 5;
	DEF = 0;
	SPD = 0;
	HP = -120;
	MP = 40;
	Duration = 10;
	CastTime = 30;
	CritMultiplier = 0;
	HasteMultiplier = 0;
	DefenseMultiplier = 0;
	TargetType = EMagic_TargetTypes::TT_Enemy;
	AnimType = EMagic_AnimTypes::AT_GroundUp;

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	P_ChargeFX = ChargeParticleObject.Object;
	ChargeFX->Template = P_ChargeFX;
	ChargeFX->SetColorParameter("Color", FLinearColor(0, 0.87f, 1, 1));  // Set Charge Particle Color

	P_CastFX = CastParticleObject.Object;
	CastFX->Template = P_CastFX;

	BlizzardDropBP = DropBlueprintObject.Object;
}

// Called when the game starts or when spawned
void ABlizzard::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	QuitCharging.AddDynamic(this, &ABlizzard::Cancel);		
}

void ABlizzard::Cancel()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Blizzard casting was cancelled.");
}

void ABlizzard::ChargeBlizzard()
{
	IsCharging = true; // Set Charging State True
	ChargeFX->Activate();  // Activate the charge particle
	// Get player mesh and attach this object
	Root->AttachToComponent(OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "PowerSocket");

}

void ABlizzard::CastBlizzard()
{
	ChargeFX->Deactivate(); // Deactivate Charge particle

	// TO DO:  Spawn the Blizzard Drop at the enemy's location, passing it the target and player references.

	// Do the Cast effect after a short delay
	FTimerHandle CastTimer;
	GetWorldTimerManager().SetTimer(CastTimer, this, &ABlizzard::DoCastEffect, 1.3f, false);
}

void ABlizzard::DoCastEffect()
{
	// Make sure the current target is anything but the player himself
	// Because this is a single player game, this will work fine
	if (OwnerReference->CurrentTarget != OwnerReference)
	{
		AActor* BlizzardDrop = UCommonLibrary::SpawnBP(GetWorld(), BlizzardDropBP, OwnerReference->CurrentTarget->GetActorLocation(), OwnerReference->CurrentTarget->GetActorRotation());

		// Cast to DropBlizzard class
		ADropBlizzard* DropBlizzard = Cast<ADropBlizzard>(BlizzardDrop);

		if (DropBlizzard)
		{
			DropBlizzard->Start_Blizzard(OwnerReference); // Start the Blizzard Spell Damage Effect
		}
	}
	else
	{
		OwnerReference->AudioManager->Play_SFX_Error();
	}
}

#undef LOCTEXT_NAMESPACE
