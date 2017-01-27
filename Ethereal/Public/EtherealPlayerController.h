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

#include "GameFramework/PlayerController.h"
#include "Characters/CombatText/CombatEffectStruct.h"
#include "EtherealSaveGame.h"
#include "EtherealPlayerController.generated.h"

// Forward Declarations
class AEtherealPlayerMaster;

UCLASS()
class ETHEREAL_API AEtherealPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	AEtherealPlayerController();

	//////////////////////////////////////////
	// DEFAULT VARIABLES

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	AEtherealPlayerMaster* EtherealPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UEtherealSaveGame* EtherealSave;

	//////////////////////////////////////////
	// STATUS EFFECTS

	// True if Sentinel Brew is active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatusEffects)
	bool Active_SentinelBrew;

	// True if Adrenaline is active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatusEffects)
	bool Active_Adrenaline;
		
	// All Possible Status Effects are stored here
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatusEffects)
	TArray<FCombatEffectStruct> StatusEffects;

	/////////////////////////////////////////
	// Status Effect Blueprint Events
	// Because I have not yet translated them from BP to C++

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = StatusEffects)
	void ActivateStatus_Heal();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = StatusEffects)
	void ActivateStatus_Reraise();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = StatusEffects)
	void ActivateStatus_Regen();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = StatusEffects)
	void ActivateStatus_Refresh();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = StatusEffects)
	void ActivateStatus_Barrier();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = StatusEffects)
	void RemoveStatus_Barrier();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = StatusEffects)
	void ActivateStatus_Berserk();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = StatusEffects)
	void ActivateStatus_Haste();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = StatusEffects)
	void ActivateStatus_Poison();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = StatusEffects)
	void RemoveStatus_Poison();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = StatusEffects)
	void ActivateStatus_Burn();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = StatusEffects)
	void ActivateStatus_Sentinel();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = StatusEffects)
	void ActivateStatus_Adrenaline();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = StatusEffects)
	void RemoveStatus_OnDeath();

	///////////////////////////////////////////////////////
	// SAVING AND LOADING

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = SaveSystem)
	void Save();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = SaveSystem)
	void Load();

	// Save Stats
	UFUNCTION(BlueprintCallable, Category = SaveSystem)
	void Save_Stats();

	// Load Stats
	UFUNCTION(BlueprintCallable, Category = SaveSystem)
	void Load_Stats();

	// Save Locks
	UFUNCTION(BlueprintCallable, Category = SaveSystem)
	void Save_Locks();

	// Load Locks
	UFUNCTION(BlueprintCallable, Category = SaveSystem)
	void Load_Locks();

	// Save Bindings
	UFUNCTION(BlueprintCallable, Category = SaveSystem)
	void Save_Bindings();

	// Load Bindings
	UFUNCTION(BlueprintCallable, Category = SaveSystem)
	void Load_Bindings();

	// Save Inventory
	UFUNCTION(BlueprintCallable, Category = SaveSystem)
	void Save_Inventory();

	// Load Inventory
	UFUNCTION(BlueprintCallable, Category = SaveSystem)
	void Load_Inventory();

	///////////////////////////////////////////////////////
	// ACHIEVEMENTS

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Achievements)
	void Achievement_Complete_Tutorial();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Achievements)
	void Achievement_Realm_Shiitake();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Achievements)
	void Achievement_Realm_Vulcan();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Achievements)
	void Achievement_Realm_Boreal();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Achievements)
	void Achievement_Realm_Yggdrasil();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Achievements)
	void Achievement_Realm_Empyrean();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Achievements)
	void Achievement_Realm_Celestial();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Achievements)
	void Achievement_GoldCount();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Achievements)
	void Achievement_KillCount();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Achievements)
	void Achievement_Chickenlover();

	//////////////////////////////////////////////////////
	// WIDGETS

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Widgets)
	void RefreshTargetingInfo();
};
