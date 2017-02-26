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
#include "Gear/EtherealGearMaster.h"
#include "Tutorial.h"

#define LOCTEXT_NAMESPACE "EtherealText"

void UTutorial::FirstContact()
{
	BindActions();  // Bind the player's Input Actions

	TutorialIndex = 0;  // set TutorialIndex

	// Configure Tutorial Text Paragraphs
	Paragraph1 = LOCTEXT("Tutorial_Paragraph1", "Magic, Weapons, and Armor are all items that can be equipped through the Pause Menu.");
	Paragraph2 = LOCTEXT("Tutorial_Paragraph2", "Equipping items has various effects on gameplay, all described in the item's information panel.");
	Paragraph3 = LOCTEXT("Tutorial_Paragraph3", "Weapons and Armor have four grades of quality to help determine their power :  Common, Uncommon, Rare, and Epic.");
	Paragraph4 = LOCTEXT("Tutorial_Paragraph4", "Magic has no such distinction.");
	Paragraph5 = LOCTEXT("Tutorial_Paragraph5", "Equip better items to increase in power and gain new abilities!");
	Paragraph6 = LOCTEXT("Tutorial_Paragraph6", "To attack, simply press the 'ACTION' button.");
	Paragraph7 = LOCTEXT("Tutorial_Paragraph7", "Hold down the 'ACTION' button to continuously attack.");
	Paragraph8 = LOCTEXT("Tutorial_Paragraph8", "Lock on to enemies to improve accuracy.");
	Paragraph9 = LOCTEXT("Tutorial_Paragraph9", "Increase your Defense by holding the 'BLOCK' button.");
	Paragraph10 = LOCTEXT("Tutorial_Paragraph10", "The path behind me leads into the graveyard, where the undead rise.");
	Paragraph11 = LOCTEXT("Tutorial_Paragraph11", "Defeat the Skeleton King and I will open the gate to the Portal.");
	Paragraph12 = LOCTEXT("Tutorial_Paragraph12", "Use consumable items, such as Potions, by pressing the 'USE ITEM' button.");
	Paragraph13 = LOCTEXT("Tutorial_Paragraph13", "Only one consumable item may be active at a time.");
	Paragraph14 = LOCTEXT("Tutorial_Paragraph14", "Swap between usable items with the 'CYCLE' button.");
	Paragraph15 = LOCTEXT("Tutorial_Paragraph15", "You may carry up to 99 of each consumable item.");
	Paragraph16 = LOCTEXT("Tutorial_Paragraph16", "You must equip spells before you can cast them. You may equip up to six spells at a time.");
	Paragraph17 = LOCTEXT("Tutorial_Paragraph17", "During gameplay, your six spells are divided into two separate tiers. Press and hold the 'MAGIC TIER' button to access the second tier.");
	Paragraph18 = LOCTEXT("Tutorial_Paragraph18", "Once a spell has been bound to a slot, press and hold the corresponding button to begin charging the spell.");
	Paragraph19 = LOCTEXT("Tutorial_Paragraph19", "After the spell is fully charged, release the button to cast the spell.");
	Paragraph20 = LOCTEXT("Tutorial_Paragraph20", "You defeated the Skeleton King!?  Well done!");
	Paragraph21 = LOCTEXT("Tutorial_Paragraph21", "Beyond the gate lies a portal to other Realms. Use it to find Zhan, and bring him to Justice.");
	Paragraph22 = LOCTEXT("Tutorial_Paragraph22", "There are three available weapon modes :  One-Handed, Two-Handed, and Ranged.");
	Paragraph23 = LOCTEXT("Tutorial_Paragraph23", "You may equip only one weapon of each type.");
	Paragraph24 = LOCTEXT("Tutorial_Paragraph24", "Swap between equipped weapons with the 'CYCLE' button.");
	Paragraph25 = LOCTEXT("Tutorial_Paragraph25", "One-Handed users may also equip a Shield, while Ranged users must equip Ammo.");
}

void UTutorial::BindActions_Implementation()
{
}

void UTutorial::SkipTo_Conversation03_Implementation()
{
}

void UTutorial::SkipTo_Conversation07_Implementation()
{
}

void UTutorial::ShowConversation_00_Implementation()
{
}

void UTutorial::ShowConversation_01_Implementation()
{
}

void UTutorial::ShowConversation_02_Implementation()
{
}

void UTutorial::ShowConversation_04_Implementation()
{
}

void UTutorial::ShowConversation_05_Implementation()
{
}

void UTutorial::ShowConversation_06_Implementation()
{
}

void UTutorial::ShowConversation_07_Implementation()
{
}

void UTutorial::ShowConversation_08_Implementation()
{
}

// Gives the tutorial items to the player
void UTutorial::GiveDefaultItems()
{
	// Give the Sword
	FTimerHandle SwordTimer;
	Gatekeeper->GetWorldTimerManager().SetTimer(SwordTimer, this, &UTutorial::GiveItem1, 0.2f, false);

	// Give the Shield
	FTimerHandle ShieldTimer;
	Gatekeeper->GetWorldTimerManager().SetTimer(ShieldTimer, this, &UTutorial::GiveItem2, 1.0f, false);
}

// Gives the tutorial items to the player
void UTutorial::GiveItem1()
{
	Gatekeeper->InteractingPlayer->EtherealPlayerState->AddToInventory(EMasterGearList::GL_WarAspis, false, true);
}

// Gives the tutorial items to the player
void UTutorial::GiveItem2()
{
	Gatekeeper->InteractingPlayer->EtherealPlayerState->AddToInventory(EMasterGearList::GL_SilverRing, false, true);
}

#undef LOCTEXT_NAMESPACE
