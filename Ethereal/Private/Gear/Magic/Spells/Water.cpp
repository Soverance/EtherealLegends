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
#include "Characters/Enemy/EtherealEnemyMaster.h"
#include "Water.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AWater::AWater(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ChargeParticleObject(TEXT("ParticleSystem'/Game/Blueprints/Gear/Magic/SpellEffects/Particles/ChargeFX/ChargeParticle.ChargeParticle'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> CastParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/Lightning/P_LineToPoint_Spawn_Proj_Lightning_00.P_LineToPoint_Spawn_Proj_Lightning_00'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/thunder.thunder'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Magic/thunder-small.thunder-small'"));
	static ConstructorHelpers::FObjectFinder<UClass> DropBlueprintObject(TEXT("Blueprint'/Game/Blueprints/Gear/Magic/Spells/Drops/ThunderDrop.ThunderDrop_C'"));

	// Set Default Values
	Name = EMasterGearList::GL_Water;
	NameText = LOCTEXT("WaterName", "Water");
	Type = EMasterGearTypes::GT_Black;
	TypeText = LOCTEXT("WaterType", "Black Magic");
	Description = "Drown your enemies with a pillar of water.";
	Price = 10000;
	MPCost = 75;
	ATK = 5;
	DEF = 0;
	SPD = 0;
	HP = -60;
	MP = 40;
	Duration = 10;
	CastTime = 30;
	CritMultiplier = 0;
	HasteMultiplier = 0;
	DefenseMultiplier = 0;
	TargetType = EMagic_TargetTypes::TT_Enemy;
	AnimType = EMagic_AnimTypes::AT_TopDown;

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	P_ChargeFX = ChargeParticleObject.Object;
	ChargeFX->Template = P_ChargeFX;
	ChargeFX->SetColorParameter("Color", FLinearColor(1, 0.98f, 0.42f, 1));  // Set Charge Particle Color

	P_CastFX = CastParticleObject.Object;
	CastFX->Template = P_CastFX;

	ThunderDropBP = DropBlueprintObject.Object;
}

// Called when the game starts or when spawned
void AWater::BeginPlay()
{
	Super::BeginPlay();

	// Bind the Use function to the event dispatcher for Item Use
	QuitCharging.AddDynamic(this, &AWater::Cancel);
}

void AWater::Cancel()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Thunder casting was cancelled.");
}

void AWater::ChargeThunder()
{
	IsCharging = true; // Set Charging State True	
	ChargeFX->Activate();  // Activate the charge particle
	// Get player mesh and attach this object
	Root->AttachToComponent(OwnerReference->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "PowerSocket");
}

void AWater::CastThunder()
{
	ChargeFX->Deactivate(); // Deactivate Charge particle
	CastFX->Activate();

	// Do the Cast effect after a short delay
	FTimerHandle CastTimer;
	GetWorldTimerManager().SetTimer(CastTimer, this, &AWater::DoCastEffect, 1.3f, false);
}

void AWater::DoCastEffect()
{
	// Make sure the current target is anything but the player himself
	// Because this is a single player game, this will work fine
	if (OwnerReference->CurrentTarget != OwnerReference)
	{
		AActor* ThunderDrop = UCommonLibrary::SpawnBP(GetWorld(), ThunderDropBP, OwnerReference->CurrentTarget->GetActorLocation(), OwnerReference->CurrentTarget->GetActorRotation());
	}
	else
	{
		OwnerReference->AudioManager->Play_SFX_Error();
	}
}

#undef LOCTEXT_NAMESPACE
