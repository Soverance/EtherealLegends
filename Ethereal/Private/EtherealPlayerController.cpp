// © 2014 - 2016 Soverance Studios
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
#include "EtherealPlayerController.h"

AEtherealPlayerController::AEtherealPlayerController()
{
	// ICONS
	static ConstructorHelpers::FObjectFinder<UTexture2D> HealIconObject(TEXT("Texture2D'/Game/CombatText/UI/Textures/T_Status_Heal.T_Status_Heal'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> RaiseIconObject(TEXT("Texture2D'/Game/CombatText/UI/Textures/raise.raise'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> RegenIconObject(TEXT("Texture2D'/Game/CombatText/UI/Textures/regen.regen'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> RefreshIconObject(TEXT("Texture2D'/Game/CombatText/UI/Textures/refresh.refresh'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> BarrierIconObject(TEXT("Texture2D'/Game/CombatText/UI/Textures/protect.protect'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> BerserkIconObject(TEXT("Texture2D'/Game/CombatText/UI/Textures/berserk.berserk'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> HasteIconObject(TEXT("Texture2D'/Game/CombatText/UI/Textures/haste.haste'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> PoisonIconObject(TEXT("Texture2D'/Game/CombatText/UI/Textures/T_Status_Poison.T_Status_Poison'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> BurnIconObject(TEXT("Texture2D'/Game/CombatText/UI/Textures/T_Status_Fire.T_Status_Fire'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SentinelIconObject(TEXT("Texture2D'/Game/CombatText/UI/Textures/sentinel.sentinel'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> AdrenalineIconObject(TEXT("Texture2D'/Game/CombatText/UI/Textures/adrenaline.adrenaline'"));
	// PARTICLES
	static ConstructorHelpers::FObjectFinder<UParticleSystem> HealEffectObject(TEXT("ParticleSystem'/Game/CombatText/Effects/P_Heal.P_Heal'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> RaiseEffectObject(TEXT("ParticleSystem'/Game/SenzaPeso/MASTERALL/Particles/P_AltarBurst.P_AltarBurst'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> RegenEffectObject(TEXT("ParticleSystem'/Game/CombatText/Effects/P_Heal.P_Heal'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> RefreshEffectObject(TEXT("ParticleSystem'/Game/CombatText/Effects/P_Refresh.P_Refresh'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> BarrierEffectObject(TEXT("ParticleSystem'/Game/CombatText/Effects/Barrier-ProtectShield.Barrier-ProtectShield'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> BerserkEffectObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/Fire/combat/P_YoYo_Fire_Charge_00.P_YoYo_Fire_Charge_00'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> HasteEffectObject(TEXT("ParticleSystem'/Game/CombatText/Effects/P_Haste1.P_Haste1'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PoisonEffectObject(TEXT("ParticleSystem'/Game/CombatText/Effects/P_Poison.P_Poison'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> BurnEffectObject(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> SentinelEffectObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Elemental/ICE/P_IceElementalSplit_Small.P_IceElementalSplit_Small'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AdrenalineEffectObject(TEXT("ParticleSystem'/Game/Elemental/Effects/Fx_Magic/Effects/FX_Knight_Hammer_Prefire.FX_Knight_Hammer_Prefire'"));

	// 0
	FCombatEffectStruct HealStatus;
	HealStatus.Name = FName(TEXT("HEAL"));
	HealStatus.Text = FText::FromString(FString(TEXT("HEAL")));
	HealStatus.Icon = HealIconObject.Object;
	HealStatus.Effect = HealEffectObject.Object;
	HealStatus.Duration = 2.0f;
	StatusEffects.Add(HealStatus); // Add
	// 1
	FCombatEffectStruct RaiseStatus;
	RaiseStatus.Name = FName(TEXT("RERAISE"));
	RaiseStatus.Text = FText::FromString(FString(TEXT("RERAISE")));
	RaiseStatus.Icon = RaiseIconObject.Object;
	RaiseStatus.Effect = RaiseEffectObject.Object;
	RaiseStatus.Duration = 3600.0f;
	StatusEffects.Add(RaiseStatus);  // Add
	// 2
	FCombatEffectStruct RegenStatus;
	RegenStatus.Name = FName(TEXT("REGEN"));
	RegenStatus.Text = FText::FromString(FString(TEXT("REGEN")));
	RegenStatus.Icon = RegenIconObject.Object;
	RegenStatus.Effect = RegenEffectObject.Object;
	RegenStatus.Duration = 60.0f;
	StatusEffects.Add(RegenStatus);  // Add
	// 3
	FCombatEffectStruct RefreshStatus;
	RefreshStatus.Name = FName(TEXT("REFRESH"));
	RefreshStatus.Text = FText::FromString(FString(TEXT("REFRESH")));
	RefreshStatus.Icon = RefreshIconObject.Object;
	RefreshStatus.Effect = RefreshEffectObject.Object;
	RefreshStatus.Duration = 60.0f;
	StatusEffects.Add(RefreshStatus);  // Add
	// 4
	FCombatEffectStruct BarrierStatus;
	BarrierStatus.Name = FName(TEXT("PROTECT"));
	BarrierStatus.Text = FText::FromString(FString(TEXT("PROTECT")));
	BarrierStatus.Icon = BarrierIconObject.Object;
	BarrierStatus.Effect = BarrierEffectObject.Object;
	BarrierStatus.Duration = 0.0f;
	StatusEffects.Add(BarrierStatus);  // Add
	// 5
	FCombatEffectStruct BerserkStatus;
	BerserkStatus.Name = FName(TEXT("BERSERK"));
	BerserkStatus.Text = FText::FromString(FString(TEXT("BERSERK")));
	BerserkStatus.Icon = BerserkIconObject.Object;
	BerserkStatus.Effect = BerserkEffectObject.Object;
	BerserkStatus.Duration = 60.0f;
	StatusEffects.Add(BerserkStatus);  // Add
	// 6
	FCombatEffectStruct HasteStatus;
	HasteStatus.Name = FName(TEXT("HASTE"));
	HasteStatus.Text = FText::FromString(FString(TEXT("HASTE")));
	HasteStatus.Icon = HasteIconObject.Object;
	HasteStatus.Effect = HasteEffectObject.Object;
	HasteStatus.Duration = 60.0f;
	StatusEffects.Add(HasteStatus);  // Add
	// 7
	FCombatEffectStruct PoisonStatus;
	PoisonStatus.Name = FName(TEXT("POISON"));
	PoisonStatus.Text = FText::FromString(FString(TEXT("POISON")));
	PoisonStatus.Icon = PoisonIconObject.Object;
	PoisonStatus.Effect = PoisonEffectObject.Object;
	PoisonStatus.Duration = 10.0f;
	StatusEffects.Add(PoisonStatus);  // Add
	// 8
	FCombatEffectStruct BurnStatus;
	BurnStatus.Name = FName(TEXT("BURN"));
	BurnStatus.Text = FText::FromString(FString(TEXT("BURN")));
	BurnStatus.Icon = BurnIconObject.Object;
	BurnStatus.Effect = BurnEffectObject.Object;
	BurnStatus.Duration = 10.0f;
	StatusEffects.Add(BurnStatus);  // Add
	// 9
	FCombatEffectStruct SentinelStatus;
	SentinelStatus.Name = FName(TEXT("SENTINEL"));
	SentinelStatus.Text = FText::FromString(FString(TEXT("SENTINEL")));
	SentinelStatus.Icon = SentinelIconObject.Object;
	SentinelStatus.Effect = SentinelEffectObject.Object;
	SentinelStatus.Duration = 120.0f;
	StatusEffects.Add(SentinelStatus);  // Add
	// 10
	FCombatEffectStruct AdrenalineStatus;
	AdrenalineStatus.Name = FName(TEXT("ADRENALINE"));
	AdrenalineStatus.Text = FText::FromString(FString(TEXT("ADRENALINE")));
	AdrenalineStatus.Icon = AdrenalineIconObject.Object;
	AdrenalineStatus.Effect = AdrenalineEffectObject.Object;
	AdrenalineStatus.Duration = 120.0f;
	StatusEffects.Add(AdrenalineStatus);  // Add
}

void AEtherealPlayerController::ActivateStatus_Heal_Implementation()
{
}

void AEtherealPlayerController::ActivateStatus_Reraise_Implementation()
{
}

void AEtherealPlayerController::ActivateStatus_Regen_Implementation()
{
}

void AEtherealPlayerController::ActivateStatus_Refresh_Implementation()
{
}

void AEtherealPlayerController::ActivateStatus_Barrier_Implementation()
{
}

void AEtherealPlayerController::RemoveStatus_Barrier_Implementation()
{
}

void AEtherealPlayerController::ActivateStatus_Berserk_Implementation()
{
}

void AEtherealPlayerController::ActivateStatus_Haste_Implementation()
{
}

void AEtherealPlayerController::ActivateStatus_Poison_Implementation()
{
}

void AEtherealPlayerController::RemoveStatus_Poison_Implementation()
{
}

void AEtherealPlayerController::ActivateStatus_Burn_Implementation()
{
}

void AEtherealPlayerController::ActivateStatus_Sentinel_Implementation()
{
}

void AEtherealPlayerController::ActivateStatus_Adrenaline_Implementation()
{
}

void AEtherealPlayerController::RemoveStatus_OnDeath_Implementation()
{
}

void AEtherealPlayerController::Save_Implementation()
{
}

void AEtherealPlayerController::Load_Implementation()
{
}

void AEtherealPlayerController::RefreshTargetingInfo_Implementation()
{
}

///////////////////////////////////
// ACHIEVEMENTS

void AEtherealPlayerController::Achievement_Complete_Tutorial_Implementation()
{
}

void AEtherealPlayerController::Achievement_Realm_Shiitake_Implementation()
{
}

void AEtherealPlayerController::Achievement_Realm_Vulcan_Implementation()
{
}

void AEtherealPlayerController::Achievement_Realm_Boreal_Implementation()
{
}

void AEtherealPlayerController::Achievement_Realm_Yggdrasil_Implementation()
{
}

void AEtherealPlayerController::Achievement_Realm_Empyrean_Implementation()
{
}

void AEtherealPlayerController::Achievement_Realm_Celestial_Implementation()
{
}

void AEtherealPlayerController::Achievement_GoldCount_Implementation()
{
}

void AEtherealPlayerController::Achievement_KillCount_Implementation()
{
}
