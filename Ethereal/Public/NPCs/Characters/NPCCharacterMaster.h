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

#include "NPCs/EtherealNPCMaster.h"
#include "NPCCharacterMaster.generated.h"

// Event Dispatcher for Disabling Shop Widgets
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDisableShop);

UCLASS()
class ETHEREAL_API ANPCCharacterMaster : public AEtherealNPCMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ANPCCharacterMaster(const FObjectInitializer& ObjectInitializer);

	// Event Dispatcher DisableShop - used for child NPCs to call custom code
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Dispatcher")
	FDisableShop DisableShop;

	// If this is an NPC Shop character, set the appropriate ShopIndex to display the corresponding shop widget
	// 0: Items  -  1: Magic  -  2: Weapons  -  3: Armor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	int32 ShopIndex;

	// Shop Inventory Array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	TArray<AEtherealGearMaster*> ShopInventory;
};
