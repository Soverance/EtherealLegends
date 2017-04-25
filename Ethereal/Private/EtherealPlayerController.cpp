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
#include "Gear/EtherealGearMaster.h"
#include "Gear/Items/Item_Master.h"
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
	static ConstructorHelpers::FObjectFinder<UTexture2D> ConfuseIconObject(TEXT("Texture2D'/Game/CombatText/UI/Textures/T_Status_Confuse.T_Status_Confuse'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SilenceIconObject(TEXT("Texture2D'/Game/CombatText/UI/Textures/T_Status_Silence.T_Status_Silence'"));
	// PARTICLES
	static ConstructorHelpers::FObjectFinder<UParticleSystem> HealEffectObject(TEXT("ParticleSystem'/Game/CombatText/Effects/P_Heal.P_Heal'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> RaiseEffectObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Cines/Ausar/P_Reraise.P_Reraise'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> RegenEffectObject(TEXT("ParticleSystem'/Game/CombatText/Effects/P_Heal.P_Heal'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> RefreshEffectObject(TEXT("ParticleSystem'/Game/CombatText/Effects/P_Refresh.P_Refresh'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> BarrierEffectObject(TEXT("ParticleSystem'/Game/CombatText/Effects/Barrier-ProtectShield.Barrier-ProtectShield'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> BerserkEffectObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/Fire/combat/P_YoYo_Fire_Charge_00.P_YoYo_Fire_Charge_00'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> HasteEffectObject(TEXT("ParticleSystem'/Game/Elemental/Effects/Fx_Magic/Effects/FX_Sigil_08.FX_Sigil_08'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PoisonEffectObject(TEXT("ParticleSystem'/Game/CombatText/Effects/P_Poison.P_Poison'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> BurnEffectObject(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> SentinelEffectObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Elemental/ICE/P_IceElementalSplit_Small.P_IceElementalSplit_Small'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AdrenalineEffectObject(TEXT("ParticleSystem'/Game/Elemental/Effects/Fx_Magic/Effects/FX_Knight_Hammer_Prefire.FX_Knight_Hammer_Prefire'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ConfuseEffectObject(TEXT("ParticleSystem'/Game/CombatText/Effects/P_Stun.P_Stun'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> SilenceEffectObject(TEXT("ParticleSystem'/Game/CombatText/Effects/P_Silence.P_Silence'"));

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
	PoisonStatus.Duration = 15.0f;
	StatusEffects.Add(PoisonStatus);  // Add
	// 8
	FCombatEffectStruct BurnStatus;
	BurnStatus.Name = FName(TEXT("BURN"));
	BurnStatus.Text = FText::FromString(FString(TEXT("BURN")));
	BurnStatus.Icon = BurnIconObject.Object;
	BurnStatus.Effect = BurnEffectObject.Object;
	BurnStatus.Duration = 15.0f;
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
	// 11
	FCombatEffectStruct ConfuseStatus;
	ConfuseStatus.Name = FName(TEXT("CONFUSE"));
	ConfuseStatus.Text = FText::FromString(FString(TEXT("CONFUSE")));
	ConfuseStatus.Icon = ConfuseIconObject.Object;
	ConfuseStatus.Effect = ConfuseEffectObject.Object;
	ConfuseStatus.Duration = 15.0f;
	StatusEffects.Add(ConfuseStatus);  // Add
	// 12
	FCombatEffectStruct SilenceStatus;
	SilenceStatus.Name = FName(TEXT("SILENCE"));
	SilenceStatus.Text = FText::FromString(FString(TEXT("SILENCE")));
	SilenceStatus.Icon = SilenceIconObject.Object;
	SilenceStatus.Effect = SilenceEffectObject.Object;
	SilenceStatus.Duration = 15.0f;
	StatusEffects.Add(SilenceStatus);  // Add
}

void AEtherealPlayerController::ActivateStatus_Heal_Implementation()
{
}

void AEtherealPlayerController::ActivateStatus_Reraise_Implementation()
{
}

void AEtherealPlayerController::RemoveStatus_Reraise_Implementation()
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

void AEtherealPlayerController::ActivateStatus_Confuse_Implementation()
{
}

void AEtherealPlayerController::RemoveStatus_Confuse_Implementation()
{
}

void AEtherealPlayerController::ActivateStatus_Silence_Implementation()
{
}

void AEtherealPlayerController::RemoveStatus_Silence_Implementation()
{
}

void AEtherealPlayerController::RemoveStatus_OnDeath_Implementation()
{
}

///////////////////////////////////
// SAVE / LOAD

void AEtherealPlayerController::Save_Implementation()
{
}

void AEtherealPlayerController::Load_Implementation()
{
}

// Saves all Stats to File
void AEtherealPlayerController::Save_Stats()
{
	if (EtherealPlayer)
	{
		if (EtherealSave)
		{
			EtherealSave->Save_PlayerLevel = EtherealPlayer->EtherealPlayerState->PlayerLevel;
			EtherealSave->Save_CurrentGold = EtherealPlayer->EtherealPlayerState->Gold_Current;
			EtherealSave->Save_CurrentEXP = EtherealPlayer->EtherealPlayerState->EXP_Current;
			EtherealSave->Save_KillCount = EtherealPlayer->EtherealPlayerState->KillCount;
			EtherealSave->Save_ChickenKillCount = EtherealPlayer->EtherealPlayerState->ChickenKillCount;
			EtherealSave->Save_TotalSecondsPlayed = EtherealPlayer->EtherealPlayerState->TotalSecondsPlayed;
		}
	}
}

// Loads Stats from Save File
void AEtherealPlayerController::Load_Stats()
{
	if (EtherealPlayer)
	{
		if (EtherealSave)
		{
			EtherealPlayer->EtherealPlayerState->PlayerLevel = EtherealSave->Save_PlayerLevel;
			EtherealPlayer->EtherealPlayerState->Gold_Current = EtherealSave->Save_CurrentGold;
			EtherealPlayer->EtherealPlayerState->EXP_Current = EtherealSave->Save_CurrentEXP;
			EtherealPlayer->EtherealPlayerState->KillCount = EtherealSave->Save_KillCount;
			EtherealPlayer->EtherealPlayerState->ChickenKillCount = EtherealSave->Save_ChickenKillCount;
			EtherealPlayer->EtherealPlayerState->TotalSecondsPlayed = EtherealSave->Save_TotalSecondsPlayed;
			// With the player's level loaded from the save file, we can call SetBaseStats();
			EtherealPlayer->EtherealPlayerState->SetBaseStats();
		}
	}
}

// Saves all Locks to File
void AEtherealPlayerController::Save_Locks()
{
	if (EtherealPlayer)
	{
		if (EtherealSave)
		{
			EtherealSave->Save_HasCompletedTutorial = EtherealPlayer->EtherealPlayerState->HasCompletedTutorial;
			EtherealSave->Save_Locked_Shiitake = EtherealPlayer->EtherealPlayerState->Locked_Shiitake;
			EtherealSave->Save_Locked_Vulcan = EtherealPlayer->EtherealPlayerState->Locked_Vulcan;
			EtherealSave->Save_Locked_Boreal = EtherealPlayer->EtherealPlayerState->Locked_Boreal;
			EtherealSave->Save_Locked_Yggdrasil = EtherealPlayer->EtherealPlayerState->Locked_Yggdrasil;
			EtherealSave->Save_Locked_Empyrean = EtherealPlayer->EtherealPlayerState->Locked_Empyrean;
			EtherealSave->Save_Locked_Celestial = EtherealPlayer->EtherealPlayerState->Locked_Celestial;
			EtherealSave->Save_HasCompletedNexus = EtherealPlayer->EtherealPlayerState->HasCompletedNexus;
		}		
	}	
}

// Loads Locks from Save File
void AEtherealPlayerController::Load_Locks()
{
	if (EtherealPlayer)
	{
		if (EtherealSave)
		{
			EtherealPlayer->EtherealPlayerState->HasCompletedTutorial = EtherealSave->Save_HasCompletedTutorial;
			EtherealPlayer->EtherealPlayerState->Locked_Shiitake = EtherealSave->Save_Locked_Shiitake;
			EtherealPlayer->EtherealPlayerState->Locked_Vulcan = EtherealSave->Save_Locked_Vulcan;
			EtherealPlayer->EtherealPlayerState->Locked_Boreal = EtherealSave->Save_Locked_Boreal;
			EtherealPlayer->EtherealPlayerState->Locked_Yggdrasil = EtherealSave->Save_Locked_Yggdrasil;
			EtherealPlayer->EtherealPlayerState->Locked_Empyrean = EtherealSave->Save_Locked_Empyrean;
			EtherealPlayer->EtherealPlayerState->Locked_Celestial = EtherealSave->Save_Locked_Celestial;
			EtherealPlayer->EtherealPlayerState->HasCompletedNexus = EtherealSave->Save_HasCompletedNexus;
		}		
	}	
}

// Saves all Bindings to File
void AEtherealPlayerController::Save_Bindings()
{
	if (EtherealPlayer)
	{
		if (EtherealSave)
		{
			EtherealSave->Save_WeaponMode = EtherealPlayer->EtherealPlayerState->WeaponMode;
			EtherealSave->Save_Magic_Slot1 = EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot1;
			EtherealSave->Save_Magic_Slot2 = EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot2;
			EtherealSave->Save_Magic_Slot3 = EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot3;
			EtherealSave->Save_Magic_Slot4 = EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot4;
			EtherealSave->Save_Magic_Slot5 = EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot5;
			EtherealSave->Save_Magic_Slot6 = EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot6;
			EtherealSave->Save_Weapon_OneHanded = EtherealPlayer->EtherealPlayerState->Binding_Weapon_OneHanded;
			EtherealSave->Save_Weapon_Shield = EtherealPlayer->EtherealPlayerState->Binding_Weapon_Shield;
			EtherealSave->Save_Weapon_TwoHanded = EtherealPlayer->EtherealPlayerState->Binding_Weapon_TwoHanded;
			EtherealSave->Save_Weapon_Ranged = EtherealPlayer->EtherealPlayerState->Binding_Weapon_Ranged;
			EtherealSave->Save_Weapon_Ammo = EtherealPlayer->EtherealPlayerState->Binding_Weapon_Ammo;
			EtherealSave->Save_Weapon_Casting = EtherealPlayer->EtherealPlayerState->Binding_Weapon_Casting;
			EtherealSave->Save_Item_Current = EtherealPlayer->EtherealPlayerState->Binding_Item_Current;
			EtherealSave->Save_Armor_Head = EtherealPlayer->EtherealPlayerState->Binding_Armor_Head;
			EtherealSave->Save_Armor_Cape = EtherealPlayer->EtherealPlayerState->Binding_Armor_Cape;
			EtherealSave->Save_Armor_Body = EtherealPlayer->EtherealPlayerState->Binding_Armor_Body;
			EtherealSave->Save_Armor_Hand = EtherealPlayer->EtherealPlayerState->Binding_Armor_Hand;
			EtherealSave->Save_Armor_Legs = EtherealPlayer->EtherealPlayerState->Binding_Armor_Legs;
			EtherealSave->Save_Armor_Ring = EtherealPlayer->EtherealPlayerState->Binding_Armor_Ring;
			EtherealSave->Save_Armor_Feet = EtherealPlayer->EtherealPlayerState->Binding_Armor_Feet;
		}
	}
}

// Loads Bindings from Save File
void AEtherealPlayerController::Load_Bindings()
{
	if (EtherealPlayer)
	{
		if (EtherealSave)
		{
			EtherealPlayer->EtherealPlayerState->WeaponMode = EtherealSave->Save_WeaponMode;
			EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot1 = EtherealSave->Save_Magic_Slot1;
			EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot2 = EtherealSave->Save_Magic_Slot2;
			EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot3 = EtherealSave->Save_Magic_Slot3;
			EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot4 = EtherealSave->Save_Magic_Slot4;
			EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot5 = EtherealSave->Save_Magic_Slot5;
			EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot6 = EtherealSave->Save_Magic_Slot6;
			EtherealPlayer->EtherealPlayerState->Binding_Weapon_OneHanded = EtherealSave->Save_Weapon_OneHanded;
			EtherealPlayer->EtherealPlayerState->Binding_Weapon_Shield = EtherealSave->Save_Weapon_Shield;
			EtherealPlayer->EtherealPlayerState->Binding_Weapon_TwoHanded = EtherealSave->Save_Weapon_TwoHanded;
			EtherealPlayer->EtherealPlayerState->Binding_Weapon_Ranged = EtherealSave->Save_Weapon_Ranged;
			EtherealPlayer->EtherealPlayerState->Binding_Weapon_Ammo = EtherealSave->Save_Weapon_Ammo;
			EtherealPlayer->EtherealPlayerState->Binding_Weapon_Casting = EtherealSave->Save_Weapon_Casting;
			EtherealPlayer->EtherealPlayerState->Binding_Item_Current = EtherealSave->Save_Item_Current;
			EtherealPlayer->EtherealPlayerState->Binding_Armor_Head = EtherealSave->Save_Armor_Head;
			EtherealPlayer->EtherealPlayerState->Binding_Armor_Cape = EtherealSave->Save_Armor_Cape;
			EtherealPlayer->EtherealPlayerState->Binding_Armor_Body = EtherealSave->Save_Armor_Body;
			EtherealPlayer->EtherealPlayerState->Binding_Armor_Hand = EtherealSave->Save_Armor_Hand;
			EtherealPlayer->EtherealPlayerState->Binding_Armor_Legs = EtherealSave->Save_Armor_Legs;
			EtherealPlayer->EtherealPlayerState->Binding_Armor_Ring = EtherealSave->Save_Armor_Ring;
			EtherealPlayer->EtherealPlayerState->Binding_Armor_Feet = EtherealSave->Save_Armor_Feet;
		}
	}
}

// Saves all Inventory items to File
void AEtherealPlayerController::Save_Inventory()
{
	if (EtherealPlayer)
	{
		if (EtherealSave)
		{
			EtherealSave->Save_Inventory.Empty();  // clear the save game's inventory array of any previous/stale data

			for (AEtherealGearMaster* Gear : EtherealPlayer->EtherealPlayerState->Inventory)
			{
				EtherealSave->Save_Inventory.AddUnique(Gear->Name);  // add all items in inventory to the save file

				// if the item is a consumable type
				if (Gear->Type == EMasterGearTypes::GT_Consumable)
				{
					AItem_Master* Item = Cast<AItem_Master>(Gear);  // Cast to it

					if (Item)
					{
						// Save Item quantities by name
						switch (Item->Name)
						{
							case EMasterGearList::GL_Reraise:
								EtherealSave->Save_QtyReraise = Item->Quantity;
								break;
							case EMasterGearList::GL_Potion:
								EtherealSave->Save_QtyPotion = Item->Quantity;
								break;
							case EMasterGearList::GL_HiPotion:
								EtherealSave->Save_QtyHiPotion = Item->Quantity;
								break;
							case EMasterGearList::GL_Ether:
								EtherealSave->Save_QtyEther = Item->Quantity;
								break;
							case EMasterGearList::GL_HiEther:
								EtherealSave->Save_QtyHiEther = Item->Quantity;
								break;
							case EMasterGearList::GL_Adrenaline:
								EtherealSave->Save_QtyAdrenaline = Item->Quantity;
								break;
							case EMasterGearList::GL_SentinelBrew:
								EtherealSave->Save_QtySentinelBrew = Item->Quantity;
								break;
							case EMasterGearList::GL_Elixer:
								EtherealSave->Save_QtyElixer = Item->Quantity;
								break;
							case EMasterGearList::GL_Antidote:
								EtherealSave->Save_QtyAntidote = Item->Quantity;
								break;
						}
					}
				}
			}
		}
	}
}

// Loads Inventory from Save File
void AEtherealPlayerController::Load_Inventory()
{
	if (EtherealPlayer)
	{
		if (EtherealSave)
		{
			for (EMasterGearList GearName : EtherealSave->Save_Inventory)
			{
				bool Bound = false;  // set a new bool to determine if we should bind this gear on spawn

				TArray<EMasterGearList> BoundItems;  // sets a disposable array of all the currently bound items

				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot1);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot2);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot3);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot4);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot5);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot6);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Magic_Slot6);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Weapon_OneHanded);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Weapon_Shield);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Weapon_TwoHanded);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Weapon_Ranged);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Weapon_Ammo);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Weapon_Casting);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Item_Current);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Armor_Head);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Armor_Cape);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Armor_Body);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Armor_Hand);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Armor_Legs);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Armor_Ring);
				BoundItems.AddUnique(EtherealPlayer->EtherealPlayerState->Binding_Armor_Feet);

				// for each bound item, check it's name against the item we're about to add
				for (EMasterGearList BoundGearName : BoundItems)
				{
					// if the item is bound...
					if (GearName == BoundGearName)
					{
						Bound = true;  // be sure to bind this item when adding to inventory
					}
				}

				EtherealPlayer->EtherealPlayerState->AddToInventory(GearName, Bound, false);  // Add all items from save file into live inventory			
			}

			for (AEtherealGearMaster* Gear : EtherealPlayer->EtherealPlayerState->Inventory)
			{
				if (Gear->Type == EMasterGearTypes::GT_Consumable)
				{
					AItem_Master* Item = Cast<AItem_Master>(Gear);  // Cast to it

					if (Item)
					{
						// Save Item quantities by name
						switch (Item->Name)
						{
						case EMasterGearList::GL_Reraise:
							Item->Quantity = EtherealSave->Save_QtyReraise;
							break;
						case EMasterGearList::GL_Potion:
							Item->Quantity = EtherealSave->Save_QtyPotion;
							break;
						case EMasterGearList::GL_HiPotion:
							Item->Quantity = EtherealSave->Save_QtyHiPotion;
							break;
						case EMasterGearList::GL_Ether:
							Item->Quantity = EtherealSave->Save_QtyEther;
							break;
						case EMasterGearList::GL_HiEther:
							Item->Quantity = EtherealSave->Save_QtyHiEther;
							break;
						case EMasterGearList::GL_Adrenaline:
							Item->Quantity = EtherealSave->Save_QtyAdrenaline;
							break;
						case EMasterGearList::GL_SentinelBrew:
							Item->Quantity = EtherealSave->Save_QtySentinelBrew;
							break;
						case EMasterGearList::GL_Elixer:
							Item->Quantity = EtherealSave->Save_QtyElixer;
							break;
						case EMasterGearList::GL_Antidote:
							Item->Quantity = EtherealSave->Save_QtyAntidote;
							break;
						}
					}
				}
			}
		}
	}
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

void AEtherealPlayerController::Achievement_LevelCount_Implementation()
{
}

void AEtherealPlayerController::Achievement_GoldCount_Implementation()
{
}

void AEtherealPlayerController::Achievement_KillCount_Implementation()
{
}

void AEtherealPlayerController::Achievement_Chickenlover_Implementation()
{
}

//////////////////////////////////////////////////////
// WIDGETS

void AEtherealPlayerController::RefreshTargetingInfo_Implementation()
{
}
