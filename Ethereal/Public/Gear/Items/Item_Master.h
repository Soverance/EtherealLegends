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

#include "Gear/EtherealGearMaster.h"
#include "Item_Master.generated.h"

// Event Dispatcher for ItemUse
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FItemUse);

UCLASS()
class ETHEREAL_API AItem_Master : public AEtherealGearMaster
{
	GENERATED_BODY()
	
public:

	AItem_Master(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	// Event Dispatcher ItemUse
	UPROPERTY(BlueprintAssignable, Category = "Dispatcher")
	FItemUse OnItemUse;

	/** Uses the item. */
	UFUNCTION(BlueprintCallable, Category = Controls)
	void UseItem();

	/** The current quantity of this item stored in the player's inventory. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Quantity;

	/** What effect this item has on gameplay. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Details)
	FString Effect;
	
	/** This emitter is active when this item is used. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* ItemFX;
	UParticleSystem* P_ItemFX;

	// Item Use Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* ItemAudio;
	USoundCue* S_ItemAudio;
	
};
