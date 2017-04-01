// © 2014 - 2017 Soverance Studios
// http://www.soverance.com

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http ://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "MasterGearTypes.generated.h"

UENUM(BlueprintType)
enum class EMasterGearTypes : uint8
{
	GT_None UMETA(DisplayName = "NONE"),
	// Weapons
	GT_OneHanded UMETA(DisplayName = "One-Handed"),
	GT_TwoHanded UMETA(DisplayName = "Two-Handed"),
	GT_Ranged UMETA(DisplayName = "Ranged"),
	GT_Casting UMETA(DisplayName = "Casting"),
	GT_Shield UMETA(DisplayName = "Shield"),
	GT_Ammo UMETA(DisplayName = "Ammunition"),
	// Magic
	GT_White UMETA(DisplayName = "White Magic"),
	GT_Black UMETA(DisplayName = "Black Magic"),
	GT_Support UMETA(DisplayName = "Support Magic"),
	GT_Ancient UMETA(DisplayName = "Ancient Magic"),
	// Armor
	GT_Head UMETA(DisplayName = "Head"),
	GT_Cape UMETA(DisplayName = "Cape"),
	GT_Body UMETA(DisplayName = "Body"),
	GT_Hand UMETA(DisplayName = "Hands"),
	GT_Legs UMETA(DisplayName = "Legs"),
	GT_Ring UMETA(DisplayName = "Ring"),
	GT_Feet UMETA(DisplayName = "Feet"),
	// Items
	GT_Consumable UMETA(DisplayName = "Consumable"),
	GT_KeyItem UMETA(DisplayName = "Key Item"),
};
