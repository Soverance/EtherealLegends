// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#pragma once
#include "MasterGearTypes.generated.h"
/**
*
*/

UENUM(BlueprintType)
enum class EMasterGearTypes : uint8
{
	GT_None UMETA(DisplayName = "NONE"),
	GT_OneHanded UMETA(DisplayName = "One-Handed"),
	GT_TwoHanded UMETA(DisplayName = "Two-Handed"),
	GT_Ranged UMETA(DisplayName = "Ranged"),
	GT_CastingOrb UMETA(DisplayName = "Casting Orb"),
	GT_Theurgy UMETA(DisplayName = "Theurgy"),
	GT_Necromancy UMETA(DisplayName = "Necromancy"),
	GT_Support UMETA(DisplayName = "Support"),
	GT_Ancient UMETA(DisplayName = "Ancient"),
	GT_Shield UMETA(DisplayName = "Shield"),
	GT_Ammo UMETA(DisplayName = "Ammunition"),
	GT_Head UMETA(DisplayName = "Head"),
	GT_Cape UMETA(DisplayName = "Cape"),
	GT_Body UMETA(DisplayName = "Body"),
	GT_Hands UMETA(DisplayName = "Hands"),
	GT_Legs UMETA(DisplayName = "Legs"),
	GT_Feet UMETA(DisplayName = "Feet"),
	GT_Consumable UMETA(DisplayName = "Consumable"),
	GT_KeyItem UMETA(DisplayName = "Key Item"),
};
