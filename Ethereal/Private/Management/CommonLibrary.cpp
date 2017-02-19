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

#include "Gear/Magic/Spells/Cure.h"
#include "Gear/Magic/Spells/CureII.h"
#include "Gear/Magic/Spells/Regen.h"
#include "Gear/Magic/Spells/Refresh.h"
#include "Gear/Magic/Spells/Blizzard.h"
#include "Gear/Magic/Spells/Comet.h"
#include "Gear/Magic/Spells/Thunder.h"
#include "Gear/Magic/Spells/Fire.h"
#include "Gear/Magic/Spells/Berserk.h"
#include "Gear/Magic/Spells/Barrier.h"
#include "Gear/Magic/Spells/Haste.h"
#include "Gear/Magic/Spells/Dash.h"

#include "Gear/Weapons/OneHanded/IronSword.h"
#include "Gear/Weapons/OneHanded/Joyeuse.h"
#include "Gear/Weapons/OneHanded/Hauteclaire.h"
#include "Gear/Weapons/OneHanded/Excalibur.h"
#include "Gear/Weapons/OneHanded/BalloonSword.h"
#include "Gear/Weapons/OneHanded/BeamSaber.h"
#include "Gear/Weapons/OneHanded/RubberChicken.h"

#include "Gear/Weapons/OneHanded/Shields/Aegis.h"
#include "Gear/Weapons/OneHanded/Shields/DiablosDread.h"
#include "Gear/Weapons/OneHanded/Shields/SpartanShield.h"
#include "Gear/Weapons/OneHanded/Shields/WarAspis.h"

#include "Gear/Weapons/Ranged/ShortBow.h"
#include "Gear/Weapons/Ranged/EagleEye.h"
#include "Gear/Weapons/Ranged/EurytosBow.h"
#include "Gear/Weapons/Ranged/Annihilator.h"

#include "Gear/Weapons/Ranged/Ammo/DemonArrow.h"
#include "Gear/Weapons/Ranged/Ammo/FlameArrow.h"
#include "Gear/Weapons/Ranged/Ammo/IronArrow.h"
#include "Gear/Weapons/Ranged/Ammo/WoodenArrow.h"

#include "Gear/Weapons/TwoHanded/Marauder.h"
#include "Gear/Weapons/TwoHanded/Juggernaut.h"
#include "Gear/Weapons/TwoHanded/Claymore.h"
#include "Gear/Weapons/TwoHanded/Temperance.h"

#include "Gear/Weapons/Casting/MagicOrbs.h"

#include "Gear/Items/Consumable/Potion.h"
#include "Gear/Items/Consumable/HiPotion.h"
#include "Gear/Items/Consumable/Ether.h"
#include "Gear/Items/Consumable/HiEther.h"
#include "Gear/Items/Consumable/Reraise.h"
#include "Gear/Items/Consumable/Elixer.h"
#include "Gear/Items/Consumable/Adrenaline.h"
#include "Gear/Items/Consumable/SentinelBrew.h"
#include "Gear/Items/Consumable/Antidote.h"
#include "Gear/Items/Consumable/EchoHerb.h"

#include "Gear/Armor/Head/ClothCap.h"
#include "Gear/Armor/Head/AdamanHelm.h"
#include "Gear/Armor/Head/WarHelm.h"
#include "Gear/Armor/Head/ValhallaHelm.h"
#include "Gear/Armor/Head/HorsemansHead.h"
#include "Gear/Armor/Head/ExoHelmet.h"
#include "Gear/Armor/Head/LeatherCap.h"
#include "Gear/Armor/Head/CrusaderHelm.h"
#include "Gear/Armor/Head/AssassinsHood.h"

#include "Gear/Armor/Cape/ClothCape.h"
#include "Gear/Armor/Cape/KnightsCape.h"
#include "Gear/Armor/Cape/ThiefsShroud.h"
#include "Gear/Armor/Cape/RestoreCloak.h"

#include "Gear/Armor/Body/ClothTunic.h"
#include "Gear/Armor/Body/AdamanCuirass.h"
#include "Gear/Armor/Body/WarCoat.h"
#include "Gear/Armor/Body/ValhallaBreastplate.h"
#include "Gear/Armor/Body/ExoPlate.h"
#include "Gear/Armor/Body/LeatherVest.h"
#include "Gear/Armor/Body/CrusaderTabard.h"
#include "Gear/Armor/Body/AssassinsVest.h"

#include "Gear/Armor/Hand/ClothGloves.h"
#include "Gear/Armor/Hand/AdamanGauntlets.h"
#include "Gear/Armor/Hand/WarGloves.h"
#include "Gear/Armor/Hand/ValhallaGauntlets.h"
#include "Gear/Armor/Hand/ExoGages.h"
#include "Gear/Armor/Hand/LeatherGloves.h"
#include "Gear/Armor/Hand/CrusaderMitts.h"
#include "Gear/Armor/Hand/AssassinsCuffs.h"

#include "Gear/Armor/Legs/ClothPants.h"
#include "Gear/Armor/Legs/AdamanCuisses.h"
#include "Gear/Armor/Legs/WarBrais.h"
#include "Gear/Armor/Legs/ValhallaFlanchard.h"
#include "Gear/Armor/Legs/ExoBreeches.h"
#include "Gear/Armor/Legs/LeatherChaps.h"
#include "Gear/Armor/Legs/CrusaderChain.h"
#include "Gear/Armor/Legs/AssassinsBrais.h"

#include "Gear/Armor/Ring/SilverRing.h"
#include "Gear/Armor/Ring/DarksteelRing.h"
#include "Gear/Armor/Ring/ShadowRing.h"
#include "Gear/Armor/Ring/RestoreRing.h"
#include "Gear/Armor/Ring/SneakRing.h"

#include "Gear/Armor/Feet/ClothShoes.h"
#include "Gear/Armor/Feet/AdamanSabatons.h"
#include "Gear/Armor/Feet/WarBoots.h"
#include "Gear/Armor/Feet/ValhallaGreaves.h"
#include "Gear/Armor/Feet/ExoBoots.h"
#include "Gear/Armor/Feet/LeatherBoots.h"
#include "Gear/Armor/Feet/CrusaderSandals.h"
#include "Gear/Armor/Feet/AssassinsBoots.h"

#include "CommonLibrary.h"

UCommonLibrary::UCommonLibrary()
{

}

AActor* UCommonLibrary::SpawnActorIntoLevel(UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, FName Level, FVector Location, FRotator Rotation, bool SpawnEvenIfColliding)
{
	if (!ActorClass) return NULL;  // return if no actor

	// use a context object to get the world
	UWorld* const World = GEngine->GetWorldFromContextObject(WorldContextObject);
	if (!World) return NULL;  // return if no world

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.bDeferConstruction = false;
	if (SpawnEvenIfColliding)
	{
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	}	

	// Get Level from Name
	ULevel* FoundLevel = NULL;

	for (const ULevelStreaming* EachLevel : World->StreamingLevels)
	{
		if (!EachLevel) continue;

		ULevel* LevelPtr = EachLevel->GetLoadedLevel();

		//Valid?
		if (!LevelPtr) continue;

		if (EachLevel->GetWorldAssetPackageFName() == Level)
		{
			FoundLevel = LevelPtr;
			break;
		}
	}

	if (FoundLevel)
	{
		SpawnParameters.OverrideLevel = FoundLevel;
	}

	return World->SpawnActor(ActorClass, &Location, &Rotation, SpawnParameters);
}

// Creates a Gear Item, when given a name
AEtherealGearMaster* UCommonLibrary::CreateGear(UObject* GearOwner, EMasterGearList ItemToCreate, FName MapName, FVector Location, FRotator Rotation)
{
	UClass* GearClass = NULL;  // an empty class to use for spawning this item
	AActor* Item = NULL; // an empty item to return

	switch (ItemToCreate)  // This switch will run through and spawn a piece of Gear based on the name
	{
	case EMasterGearList::GL_None:
		// Do nothing, because the item is set to NONE!
		break;

		///////////////////////////////
		// MAGIC

	case EMasterGearList::GL_Cure:
		GearClass = ACure::StaticClass();
		break;
	case EMasterGearList::GL_Cure2:
		GearClass = ACureII::StaticClass();
		break;
	case EMasterGearList::GL_Raise:
		// Do nothing, because Raise does not yet exist
		break;
	case EMasterGearList::GL_Regen:
		GearClass = ARegen::StaticClass();
		break;
	case EMasterGearList::GL_Refresh:
		GearClass = ARefresh::StaticClass();
		break;
	case EMasterGearList::GL_Esuna:
		// Do nothing, because Esuna does not yet exist
		break;
	case EMasterGearList::GL_Comet:
		GearClass = AComet::StaticClass();
		break;
	case EMasterGearList::GL_Blizzard:
		GearClass = ABlizzard::StaticClass();
		break;
	case EMasterGearList::GL_Thunder:
		GearClass = AThunder::StaticClass();
		break;
	case EMasterGearList::GL_Fire:
		GearClass = AFire::StaticClass();
		break;
	case EMasterGearList::GL_Poison:
		// Do nothing, because Poison does not yet exist
		break;
	case EMasterGearList::GL_Sleep:
		// Do nothing, because Sleep does not yet exist
		break;
	case EMasterGearList::GL_Berserk:
		GearClass = ABerserk::StaticClass();
		break;
	case EMasterGearList::GL_Barrier:
		GearClass = ABarrier::StaticClass();
		break;
	case EMasterGearList::GL_Haste:
		GearClass = AHaste::StaticClass();
		break;
	case EMasterGearList::GL_Slow:
		// Do nothing, because Slow does not yet exist
		break;
	case EMasterGearList::GL_Counter:
		// Do nothing, because Counter does not yet exist
		break;
	case EMasterGearList::GL_Stun:
		// Do nothing, because Stun does not yet exist
		break;
	case EMasterGearList::GL_Dash:
		GearClass = ADash::StaticClass();
		break;
	case EMasterGearList::GL_Gravity:
		// Do nothing, because Gravity does not yet exist
		break;

		///////////////////////////////
		// ONE-HANDED

	case EMasterGearList::GL_IronSword:
		GearClass = AIronSword::StaticClass();
		break;
	case EMasterGearList::GL_Joyeuse:
		GearClass = AJoyeuse::StaticClass();
		break;
	case EMasterGearList::GL_Hauteclaire:
		GearClass = AHauteclaire::StaticClass();
		break;
	case EMasterGearList::GL_Excalibur:
		GearClass = AExcalibur::StaticClass();
		break;
	case EMasterGearList::GL_BalloonSword:
		GearClass = ABalloonSword::StaticClass();
		break;
	case EMasterGearList::GL_BeamSaber:
		GearClass = ABeamSaber::StaticClass();
		break;
	case EMasterGearList::GL_RubberChicken:
		GearClass = ARubberChicken::StaticClass();
		break;

		///////////////////////////////
		// SHIELDS

	case EMasterGearList::GL_WarAspis:
		GearClass = AWarAspis::StaticClass();
		break;
	case EMasterGearList::GL_SpartanShield:
		GearClass = ASpartanShield::StaticClass();
		break;
	case EMasterGearList::GL_DiablosDread:
		GearClass = ADiablosDread::StaticClass();
		break;
	case EMasterGearList::GL_Aegis:
		GearClass = AAegis::StaticClass();
		break;

		///////////////////////////////
		// RANGED

	case EMasterGearList::GL_ShortBow:
		GearClass = AShortBow::StaticClass();
		break;
	case EMasterGearList::GL_EagleEye:
		GearClass = AEagleEye::StaticClass();
		break;
	case EMasterGearList::GL_EurytosBow:
		GearClass = AEurytosBow::StaticClass();
		break;
	case EMasterGearList::GL_Annihilator:
		GearClass = AAnnihilator::StaticClass();
		break;

		///////////////////////////////
		// AMMUNITION

	case EMasterGearList::GL_DemonArrow:
		GearClass = ADemonArrow::StaticClass();
		break;
	case EMasterGearList::GL_FlameArrow:
		GearClass = AFlameArrow::StaticClass();
		break;
	case EMasterGearList::GL_IronArrow:
		GearClass = AIronArrow::StaticClass();
		break;
	case EMasterGearList::GL_WoodenArrow:
		GearClass = AWoodenArrow::StaticClass();
		break;

		///////////////////////////////
		// TWO-HANDED

	case EMasterGearList::GL_Juggernaut:
		GearClass = AJuggernaut::StaticClass();
		break;
	case EMasterGearList::GL_Claymore:
		GearClass = AClaymore::StaticClass();
		break;
	case EMasterGearList::GL_Marauder:
		GearClass = AMarauder::StaticClass();
		break;
	case EMasterGearList::GL_Temperance:
		GearClass = ATemperance::StaticClass();
		break;

		///////////////////////////////
		// CASTING ORBS

	case EMasterGearList::GL_MagicOrbs:
		GearClass = AMagicOrbs::StaticClass();
		break;

		///////////////////////////////
		// CONSUMABLE ITEMS

	case EMasterGearList::GL_Potion:
		GearClass = APotion::StaticClass();
		break;
	case EMasterGearList::GL_HiPotion:
		GearClass = AHiPotion::StaticClass();
		break;
	case EMasterGearList::GL_Ether:
		GearClass = AEther::StaticClass();
		break;
	case EMasterGearList::GL_HiEther:
		GearClass = AHiEther::StaticClass();
		break;
	case EMasterGearList::GL_Elixer:
		GearClass = AElixer::StaticClass();
		break;
	case EMasterGearList::GL_Reraise:
		GearClass = AReraise::StaticClass();
		break;
	case EMasterGearList::GL_Adrenaline:
		GearClass = AAdrenaline::StaticClass();
		break;
	case EMasterGearList::GL_SentinelBrew:
		GearClass = ASentinelBrew::StaticClass();
		break;
	case EMasterGearList::GL_Antidote:
		GearClass = AAntidote::StaticClass();
		break;
	case EMasterGearList::GL_EchoHerb:
		GearClass = AEchoHerb::StaticClass();
		break;

		///////////////////////////////
		// ARMOR - HEAD
	case EMasterGearList::GL_ClothCap:
		GearClass = AClothCap::StaticClass();
		break;
	case EMasterGearList::GL_AdamanHelm:
		GearClass = AAdamanHelm::StaticClass();
		break;
	case EMasterGearList::GL_WarHelm:
		GearClass = AWarHelm::StaticClass();
		break;
	case EMasterGearList::GL_ValhallaHelm:
		GearClass = AValhallaHelm::StaticClass();
		break;
	case EMasterGearList::GL_HorsemansHead:
		GearClass = AHorsemansHead::StaticClass();
		break;
	case EMasterGearList::GL_ExoHelmet:
		GearClass = AExoHelmet::StaticClass();
		break;
	case EMasterGearList::GL_LeatherCap:
		GearClass = ALeatherCap::StaticClass();
		break;
	case EMasterGearList::GL_CrusaderHelm:
		GearClass = ACrusaderHelm::StaticClass();
		break;
	case EMasterGearList::GL_AssassinsHood:
		GearClass = AAssassinsHood::StaticClass();
		break;

		///////////////////////////////
		// ARMOR - CAPE
	case EMasterGearList::GL_ClothCape:
		GearClass = AClothCape::StaticClass();
		break;
	case EMasterGearList::GL_KnightsCape:
		GearClass = AKnightsCape::StaticClass();
		break;
	case EMasterGearList::GL_ThiefsShroud:
		GearClass = AThiefsShroud::StaticClass();
		break;
	case EMasterGearList::GL_RestoreCloak:
		GearClass = ARestoreCloak::StaticClass();
		break;

		///////////////////////////////
		// ARMOR - BODY
	case EMasterGearList::GL_ClothTunic:
		GearClass = AClothTunic::StaticClass();
		break;
	case EMasterGearList::GL_AdamanCuirass:
		GearClass = AAdamanCuirass::StaticClass();
		break;
	case EMasterGearList::GL_WarCoat:
		GearClass = AWarCoat::StaticClass();
		break;
	case EMasterGearList::GL_ValhallaBreastplate:
		GearClass = AValhallaBreastplate::StaticClass();
		break;
	case EMasterGearList::GL_ExoPlate:
		GearClass = AExoPlate::StaticClass();
		break;
	case EMasterGearList::GL_LeatherVest:
		GearClass = ALeatherVest::StaticClass();
		break;
	case EMasterGearList::GL_CrusaderTabard:
		GearClass = ACrusaderTabard::StaticClass();
		break;
	case EMasterGearList::GL_AssassinsVest:
		GearClass = AAssassinsVest::StaticClass();
		break;

		//////////////////////////////
		// ARMOR - HANDS
	case EMasterGearList::GL_ClothGloves:
		GearClass = AClothGloves::StaticClass();
		break;
	case EMasterGearList::GL_AdamanGauntlets:
		GearClass = AAdamanGauntlets::StaticClass();
		break;
	case EMasterGearList::GL_WarGloves:
		GearClass = AWarGloves::StaticClass();
		break;
	case EMasterGearList::GL_ValhallaGauntlets:
		GearClass = AValhallaGauntlets::StaticClass();
		break;
	case EMasterGearList::GL_ExoGages:
		GearClass = AExoGages::StaticClass();
		break;
	case EMasterGearList::GL_LeatherGloves:
		GearClass = ALeatherGloves::StaticClass();
		break;
	case EMasterGearList::GL_CrusaderMitts:
		GearClass = ACrusaderMitts::StaticClass();
		break;
	case EMasterGearList::GL_AssassinsCuffs:
		GearClass = AAssassinsCuffs::StaticClass();
		break;

		///////////////////////////////
		// ARMOR - LEGS
	case EMasterGearList::GL_ClothPants:
		GearClass = AClothPants::StaticClass();
		break;
	case EMasterGearList::GL_AdamanCuisses:
		GearClass = AAdamanCuisses::StaticClass();
		break;
	case EMasterGearList::GL_WarBrais:
		GearClass = AWarBrais::StaticClass();
		break;
	case EMasterGearList::GL_ValhallaFlanchard:
		GearClass = AValhallaFlanchard::StaticClass();
		break;
	case EMasterGearList::GL_ExoBreeches:
		GearClass = AExoBreeches::StaticClass();
		break;
	case EMasterGearList::GL_LeatherChaps:
		GearClass = ALeatherChaps::StaticClass();
		break;
	case EMasterGearList::GL_CrusaderChain:
		GearClass = ACrusaderChain::StaticClass();
		break;
	case EMasterGearList::GL_AssassinsBrais:
		GearClass = AAssassinsBrais::StaticClass();
		break;

		///////////////////////////////
		// ARMOR - RING
	case EMasterGearList::GL_SilverRing:
		GearClass = ASilverRing::StaticClass();
		break;
	case EMasterGearList::GL_DarksteelRing:
		GearClass = ADarksteelRing::StaticClass();
		break;
	case EMasterGearList::GL_ShadowRing:
		GearClass = AShadowRing::StaticClass();
		break;
	case EMasterGearList::GL_RestoreRing:
		GearClass = ARestoreRing::StaticClass();
		break;
	case EMasterGearList::GL_SneakRing:
		GearClass = ASneakRing::StaticClass();
		break;

		///////////////////////////////
		// ARMOR - FEET
	case EMasterGearList::GL_ClothShoes:
		GearClass = AClothShoes::StaticClass();
		break;
	case EMasterGearList::GL_AdamanSabatons:
		GearClass = AAdamanSabatons::StaticClass();
		break;
	case EMasterGearList::GL_WarBoots:
		GearClass = AWarBoots::StaticClass();
		break;
	case EMasterGearList::GL_ValhallaGreaves:
		GearClass = AValhallaGreaves::StaticClass();
		break;
	case EMasterGearList::GL_ExoBoots:
		GearClass = AExoBoots::StaticClass();
		break;
	case EMasterGearList::GL_LeatherBoots:
		GearClass = ALeatherBoots::StaticClass();
		break;
	case EMasterGearList::GL_CrusaderSandals:
		GearClass = ACrusaderSandals::StaticClass();
		break;
	case EMasterGearList::GL_AssassinsBoots:
		GearClass = AAssassinsBoots::StaticClass();
		break;
	}

	// Spawn the AActor item
	Item = SpawnActorIntoLevel(GearOwner, GearClass, MapName, Location, Rotation, true);

	// Cast the item to GearMaster class
	AEtherealGearMaster* Gear = Cast<AEtherealGearMaster>(Item);

	// if cast was successful, return Gear
	if (Gear)
	{
		return Gear;
	}
	else
	{
		return NULL;  // Cast was not successful, return null
	}
}
