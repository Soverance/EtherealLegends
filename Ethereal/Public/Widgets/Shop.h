// © 2014 - 2017 Soverance Studios
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

#include "Blueprint/UserWidget.h"
#include "NPCs/Characters/NPCCharacterMaster.h"
#include "Shop.generated.h"

UCLASS()
class ETHEREAL_API UShop : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	// Reset To Defaults
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Widgets)
	void ResetToDefaults();

	// If this is an NPC Shop character, set the appropriate ShopIndex to display the corresponding shop widget
	// 0: Items  -  1: Magic  -  2: Weapons  -  3: Armor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shop)
	int32 ShopIndex;

	// The owning NPC reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shop)
	ANPCCharacterMaster* OwnerNPC;
};
