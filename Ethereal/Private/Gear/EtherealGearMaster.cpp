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
#include "Characters/Player/WeaponModes.h"
#include "EtherealGearMaster.h"

// Sets default values
AEtherealGearMaster::AEtherealGearMaster(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Creates a scene component and sets it as the root
	Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = Root;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsBound = false;
}

// Called when the game starts or when spawned
void AEtherealGearMaster::ConfigureGear(AEtherealPlayerMaster* Player)
{
	// Sets the Ethereal Player Master reference
	OwnerReference = Player;
	
	if (OwnerReference)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Owner Reference in this Gear Item was successfully initialized from code.");
	}
}

// Binds this Gear to the Player. This is an in game function, called by the player binding the Gear using the Pause Menu
void AEtherealGearMaster::Bind()
{
	if (!IsBound)
	{
		IsBound = true;
		OnBindGear.Broadcast();
		AddGearStats();

		// Do additional stuff for binding all weapons
		// In this case, binding a weapon replaces the anim state and main weapon binding variable.
		// Usually, items are only bound through the Pause/Bindings menu. However, occasionally the AddToInventory function can be called with ShouldBind true, where this code may be necessary
		// I believe the only time it matters is when you are first given the iron sword when beginning a new game with no previous save file
		// We're not doing anything else for any other items at this time, though this can be further expanded for a lot of stuff
		switch (Type)
		{
		case EMasterGearTypes::GT_None:
			// Do nothing, just break
			break;
		case EMasterGearTypes::GT_OneHanded:
			OwnerReference->WeaponMode = EWeaponModes::WM_OneHanded;
			OwnerReference->EtherealPlayerState->Binding_Weapon_Main = Name;
			break;
		case EMasterGearTypes::GT_TwoHanded:
			OwnerReference->WeaponMode = EWeaponModes::WM_TwoHanded;
			OwnerReference->EtherealPlayerState->Binding_Weapon_Main = Name;
			break;
		case EMasterGearTypes::GT_Ranged:
			OwnerReference->WeaponMode = EWeaponModes::WM_Ranged;
			OwnerReference->EtherealPlayerState->Binding_Weapon_Main = Name;
			break;
		case EMasterGearTypes::GT_Casting:
			OwnerReference->WeaponMode = EWeaponModes::WM_Casting;
			OwnerReference->EtherealPlayerState->Binding_Weapon_Main = Name;
			break;
		}
	}
}

// Binds this Gear to the Player. This is an in game function, called by the player binding the Gear using the Pause Menu
void AEtherealGearMaster::Unbind()
{
	if (IsBound)
	{
		IsBound = false;
		OnRemoveGear.Broadcast();
		OwnerReference->EtherealPlayerState->RemoveGearStats(Name);

		switch (Type)
		{
		case EMasterGearTypes::GT_None:
			OwnerReference->WeaponMode = EWeaponModes::WM_None;
			break;
		case EMasterGearTypes::GT_OneHanded:
			OwnerReference->WeaponMode = EWeaponModes::WM_None;
			break;
		case EMasterGearTypes::GT_TwoHanded:
			OwnerReference->WeaponMode = EWeaponModes::WM_None;
			break;
		case EMasterGearTypes::GT_Ranged:
			OwnerReference->WeaponMode = EWeaponModes::WM_None;
			break;
		case EMasterGearTypes::GT_Casting:
			OwnerReference->WeaponMode = EWeaponModes::WM_None;
			break;
		}
	}	
}

// ADD GEAR STATS
void AEtherealGearMaster::AddGearStats()
{
	// Add stats from gear to the player's stats
	OwnerReference->EtherealPlayerState->ATK = (OwnerReference->EtherealPlayerState->ATK + ATK);
	OwnerReference->EtherealPlayerState->DEF = (OwnerReference->EtherealPlayerState->DEF + DEF);
	OwnerReference->EtherealPlayerState->SPD = (OwnerReference->EtherealPlayerState->SPD + SPD);
	OwnerReference->EtherealPlayerState->HP_Max = (OwnerReference->EtherealPlayerState->HP_Max + HP);
	OwnerReference->EtherealPlayerState->MP_Max = (OwnerReference->EtherealPlayerState->MP_Max + MP);
}