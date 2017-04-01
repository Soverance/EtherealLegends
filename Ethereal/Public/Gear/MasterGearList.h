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

#pragma once

#include "MasterGearList.generated.h"

 UENUM(BlueprintType)
 enum class EMasterGearList : uint8
 {
	// NONE
 	GL_None UMETA(DisplayName = "NONE"),

	// MAGIC
 	GL_Cure UMETA(DisplayName = "Cure"),
 	GL_Cure2 UMETA(DisplayName = "Cure II"),
 	GL_Return UMETA(DisplayName = "Return"),
 	GL_Regen UMETA(DisplayName = "Regen"),
 	GL_Refresh UMETA(DisplayName = "Refresh"),
 	GL_Esuna UMETA(DisplayName = "Esuna"),
 	GL_Comet UMETA(DisplayName = "Comet"),
 	GL_Blizzard UMETA(DisplayName = "Blizzard"),
 	GL_Thunder UMETA(DisplayName = "Thunder"),
 	GL_Fire UMETA(DisplayName = "Fire"),
 	GL_Poison UMETA(DisplayName = "Poison"),
 	GL_Sleep UMETA(DisplayName = "Sleep"),
 	GL_Berserk UMETA(DisplayName = "Berserk"),
 	GL_Barrier UMETA(DisplayName = "Barrier"),
 	GL_Haste UMETA(DisplayName = "Haste"),
 	GL_Slow UMETA(DisplayName = "Slow"),
 	GL_Counter UMETA(DisplayName = "Counter"),
 	GL_Stun UMETA(DisplayName = "Stun"),
 	GL_Dash UMETA(DisplayName = "Dash"),
 	GL_Gravity UMETA(DisplayName = "Gravity"),

	// One Handed
 	GL_IronSword UMETA(DisplayName = "Iron Sword"),
	GL_RuneBlade UMETA(DisplayName = "Rune Blade"),
	GL_Joyeuse UMETA(DisplayName = "Joyeuse"),
 	GL_Hauteclaire UMETA(DisplayName = "Hauteclaire"),
	GL_Excalibur UMETA(DisplayName = "Excalibur"),
	GL_Valkyrie UMETA(DisplayName = "Valkyrie"),

	 // Novelty
	GL_BalloonSword UMETA(DisplayName = "Balloon Sword"),
	GL_BeamSaber UMETA(DisplayName = "Beam Saber"),
	GL_RubberChicken UMETA(DisplayName = "Rubber Chicken"),
	
	// Shields
	GL_WarAspis UMETA(DisplayName = "War Aspis"),
 	GL_SpartanShield UMETA(DisplayName = "Spartan Shield"),
	GL_DiablosDread UMETA(DisplayName = "Diablo's Dread"),
	GL_Aegis UMETA(DisplayName = "Aegis"),
	GL_DragonShield UMETA(DisplayName = "Dragon Shield"),
	GL_DeathsVoid UMETA(DisplayName = "Deaths Void"),

	// Ranged
	GL_ShortBow UMETA(DisplayName = "ShortBow"),
	GL_EagleEye UMETA(DisplayName = "EagleEye"),
	GL_EurytosBow UMETA(DisplayName = "Eurytos' Bow"),
 	GL_Annihilator UMETA(DisplayName = "Annihilator"),
	GL_RuneBow UMETA(DisplayName = "Rune Bow"),

	// Ammo
	GL_PulseArrow UMETA(DisplayName = "Pulse Arrow"),
	GL_DemonArrow UMETA(DisplayName = "Demon Arrow"),
	GL_FlameArrow UMETA(DisplayName = "Flame Arrow"),
	GL_IronArrow UMETA(DisplayName = "Iron Arrow"),
	GL_WoodenArrow UMETA(DisplayName = "Wooden Arrow"),

	// Two Handed
	GL_Juggernaut UMETA(DisplayName = "Juggernaut"),
	GL_Claymore UMETA(DisplayName = "Claymore"),
 	GL_Marauder UMETA(DisplayName = "Marauder"),
	GL_Conquerer UMETA(DisplayName = "Conquerer"),
 	GL_Temperance UMETA(DisplayName = "Temperance"),
	GL_Apocalypse UMETA(DisplayName = "Apocalypse"),

	// Casting Orbs
 	GL_MagicOrbs UMETA(DisplayName = "Magic Orbs"),

	///////////////////////////////////////
	// CONSUMABLE ITEMS
 	GL_Reraise UMETA(DisplayName = "Reraise"),
 	GL_Potion UMETA(DisplayName = "Potion"),
 	GL_HiPotion UMETA(DisplayName = "Hi-Potion"),
 	GL_Ether UMETA(DisplayName = "Ether"),
 	GL_HiEther UMETA(DisplayName = "Hi-Ether"),
 	GL_Adrenaline UMETA(DisplayName = "Adrenaline"),
 	GL_SentinelBrew UMETA(DisplayName = "Sentinel Brew"),
 	GL_Elixer UMETA(DisplayName = "Elixer"),
	GL_Antidote UMETA(DisplayName = "Antidote"),
	GL_EchoHerb UMETA(DisplayName = "Echo Herb"),

	//////////////////////////////////////
	// ARMOR SETS

	// Head
	GL_ClothCap UMETA(DisplayName = "Cloth Cap"),
	GL_AdamanHelm UMETA(DisplayName = "Adaman Helm"),
	GL_WarHelm UMETA(DisplayName = "War Helm"),
	GL_ValhallaHelm UMETA(DisplayName = "Valhalla Helm"),
	GL_HorsemansHead UMETA(DisplayName = "Horseman's Head"),
	GL_ExoHelmet UMETA(DisplayName = "Exo Helmet"),
	GL_LeatherCap UMETA(DisplayName = "Leather Cap"),
	GL_CrusaderHelm UMETA(DisplayName = "Crusader Helm"),
	GL_AssassinsHood UMETA(DisplayName = "Assassins Hood"),
	GL_CrimsonHelm UMETA(DisplayName = "Crimson Helm"),
	GL_HuntersHood UMETA(DisplayName = "Hunters Hood"),

	// Cape
	GL_ClothCape UMETA(DisplayName = "Cloth Cape"),
	GL_KnightsCape UMETA(DisplayName = "Knight's Cape"),
	GL_ThiefsShroud UMETA(DisplayName = "Thief's Shroud"),
	GL_RestoreCloak UMETA(DisplayName = "Restore Cloak"),

	// Body
	GL_ClothTunic UMETA(DisplayName = "Cloth Tunic"),
	GL_AdamanCuirass UMETA(DisplayName = "Adaman Cuirass"),
	GL_WarCoat UMETA(DisplayName = "War Coat"),
	GL_ValhallaBreastplate UMETA(DisplayName = "Valhalla Breastplate"),
	GL_ExoPlate UMETA(DisplayName = "Exo Plate"),
	GL_LeatherVest UMETA(DisplayName = "Leather Vest"),
	GL_CrusaderTabard UMETA(DisplayName = "Crusader Tabard"),
	GL_AssassinsVest UMETA(DisplayName = "Assassins Vest"),
	GL_CrimsonBreastplate UMETA(DisplayName = "Crimson Breastplate"),
	GL_HuntersCoat UMETA(DisplayName = "Hunters Coat"),

	// Hands
	GL_ClothGloves UMETA(DisplayName = "Cloth Gloves"),
	GL_AdamanGauntlets UMETA(DisplayName = "Adaman Gauntlets"),
	GL_WarGloves UMETA(DisplayName = "War Gloves"),
	GL_ValhallaGauntlets UMETA(DisplayName = "Valhalla Gauntlets"),
	GL_ExoGages UMETA(DisplayName = "Exo Gages"),
	GL_LeatherGloves UMETA(DisplayName = "Leather Gloves"),
	GL_CrusaderMitts UMETA(DisplayName = "Crusader Mitts"),
	GL_AssassinsCuffs UMETA(DisplayName = "Assassins Cuffs"),
	GL_CrimsonGauntlets UMETA(DisplayName = "Crimson Gauntlets"),
	GL_HuntersGloves UMETA(DisplayName = "Hunters Gloves"),

	// Legs
	GL_ClothPants UMETA(DisplayName = "Cloth Pants"),
	GL_AdamanCuisses UMETA(DisplayName = "Adaman Cuisses"),
	GL_WarBrais UMETA(DisplayName = "War Brais"),
	GL_ValhallaFlanchard UMETA(DisplayName = "Valhalla Flanchard"),
	GL_ExoBreeches UMETA(DisplayName = "Exo Breeches"),
	GL_LeatherChaps UMETA(DisplayName = "Leather Chaps"),
	GL_CrusaderChain UMETA(DisplayName = "Crusader Chain"),
	GL_AssassinsBrais UMETA(DisplayName = "Assassins Brais"),
	GL_CrimsonSlacks UMETA(DisplayName = "Crimson Slacks"),
	GL_HuntersPants UMETA(DisplayName = "Hunters Pants"),

	// Feet
	GL_ClothShoes UMETA(DisplayName = "Cloth Shoes"),
	GL_AdamanSabatons UMETA(DisplayName = "Adaman Sabatons"),
	GL_WarBoots UMETA(DisplayName = "War Boots"),
	GL_ValhallaGreaves UMETA(DisplayName = "Valhalla Greaves"),
	GL_ExoBoots UMETA(DisplayName = "Exo Boots"),
	GL_LeatherBoots UMETA(DisplayName = "Leather Boots"),
	GL_CrusaderSandals UMETA(DisplayName = "Crusader Sandals"),
	GL_AssassinsBoots UMETA(DisplayName = "Assassins Boots"),
	GL_CrimsonGreaves UMETA(DisplayName = "Crimson Greaves"),
	GL_HuntersBoots UMETA(DisplayName = "Hunters Boots"),

	// Rings
	GL_SilverRing UMETA(DisplayName = "Silver Ring"),
	GL_DarksteelRing UMETA(DisplayName = "Darksteel Ring"),
	GL_ShadowRing UMETA(DisplayName = "Shadow Ring"),
	GL_RestoreRing UMETA(DisplayName = "Restore Ring"),
	GL_SneakRing UMETA(DisplayName = "Sneak Ring"),
	GL_FeralBand UMETA(DisplayName = "Feral Band"),
	GL_DefendingRing UMETA(DisplayName = "Defending Ring"),

	// SIGNET RINGS
	GL_AquaSignet UMETA(DisplayName = "Aqua Signet"),
	GL_FlameSignet UMETA(DisplayName = "Flame Signet"),
	GL_IceSignet UMETA(DisplayName = "Ice Signet"),
	GL_EarthSignet UMETA(DisplayName = "Earth Signet"),
	GL_SkySignet UMETA(DisplayName = "Sky Signet"),
	GL_StarSignet UMETA(DisplayName = "Star Signet"),	
 };
