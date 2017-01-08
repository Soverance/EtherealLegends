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

#pragma once

#include "GameFramework/SaveGame.h"
#include "MasterGearList.h"
#include "Characters/Player/WeaponModes.h"
#include "EtherealSaveGame.generated.h"

UCLASS()
class ETHEREAL_API UEtherealSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UEtherealSaveGame();

	// Save Slot Name
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	//////////////////////////////////////////////////////
	// INFORMATIONAL

	

	///////////////////////////////////////
	// BINDINGS

	// MAGIC

	// MAGIC Tier 1 Slot 1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Magic_Slot1;

	// MAGIC Tier 1 Slot 2
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Magic_Slot2;

	// MAGIC Tier 1 Slot 3
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Magic_Slot3;

	// MAGIC Tier 2 Slot 1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Magic_Slot4;

	// MAGIC Tier 2 Slot 2
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Magic_Slot5;

	// MAGIC Tier 2 Slot 3
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Magic_Slot6;

	// WEAPONS

	// The current Weapon Mode, used for determining animations for the currently bound weapon.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	EWeaponModes Save_WeaponMode;

	// One-Handed Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Weapon_OneHanded;

	// Shield Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Weapon_Shield;

	// Two-Handed Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Weapon_TwoHanded;

	// Ranged Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Weapon_Ranged;

	// Ammo Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Weapon_Ammo;

	// Casting Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Weapon_Casting;

	// ARMOR

	// Armor - Head
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Armor_Head;

	// Armor - Cape
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Armor_Cape;

	// Armor - Body
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Armor_Body;

	// Armor - Hands
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Armor_Hand;

	// Armor - Legs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Armor_Legs;

	// Armor - Ring
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Armor_Ring;

	// Armor - Feet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Armor_Feet;

	/////////////////////////////////////////
	//  STATS
	
	// Player Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Save_PlayerLevel;

	// Current Gold
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Save_CurrentGold;

	// Current EXP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Save_CurrentEXP;

	// Kill Count
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Save_KillCount;	

	// Total Seconds Played
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float Save_TotalSecondsPlayed;

	// Inventory Array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	TArray<EMasterGearList> Save_Inventory;

	// Current Item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	EMasterGearList Save_Item_Current;
	
	/////////////////////////////////////////////
	// CONSUMABLE ITEM QUANTITIES

	// Potion Quantity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quantities)
	int32 Save_QtyPotion;

	// Hi Potion Quantity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quantities)
	int32 Save_QtyHiPotion;

	// Ether Quantity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quantities)
	int32 Save_QtyEther;

	// Hi Ether Quantity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quantities)
	int32 Save_QtyHiEther;

	// Elixer Quantity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quantities)
	int32 Save_QtyElixer;

	// Reraise Quantity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quantities)
	int32 Save_QtyReraise;

	// Adrenaline Quantity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quantities)
	int32 Save_QtyAdrenaline;

	// SentinelBrew Quantity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quantities)
	int32 Save_QtySentinelBrew;

	// Antidote Quantity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quantities)
	int32 Save_QtyAntidote;

	/////////////////////////////////////////////
	// UNLOCKS

	// Whether or not the player has completed the tutorial.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unlocks)
	bool Save_HasCompletedTutorial;

	// Shiitake Temple
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unlocks)
	bool Save_Unlocked_Shiitake;

	// Vulcan Shrine
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unlocks)
	bool Save_Unlocked_Vulcan;

	// Boreal Core
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unlocks)
	bool Save_Unlocked_Boreal;

	// Yggdrasil
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unlocks)
	bool Save_Unlocked_Yggdrasil;

	// Empyrean Gardens
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unlocks)
	bool Save_Unlocked_EmpyreanGardens;

	// Celestial Nexus
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unlocks)
	bool Save_Unlocked_Celestial;
};
