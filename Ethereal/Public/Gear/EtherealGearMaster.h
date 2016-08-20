// © 2014 - 2016 Soverance Studios
// www.soverance.com

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

#include "GameFramework/Actor.h"
#include "MasterGearList.h"
#include "MasterGearTypes.h"
#include "EtherealGearMaster.generated.h"

// Forward Declarations
class AEtherealPlayerMaster;

UCLASS()
class ETHEREAL_API AEtherealGearMaster : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AEtherealGearMaster();

	// BeginPlay Override
	virtual void BeginPlay() override;

	/** The root scene component for all gear actors. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	USceneComponent* Root;

	/** Determines whether or not this Gear item is bound to a slot. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	bool IsBound;

	/** Gear Item Unique Name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Details)
	EMasterGearList Name;

	/** Gear Item Type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Details)
	EMasterGearTypes Type;

	/** Gear description displayed on the Bindings screen. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Details)
	FString Description;

	/** How much MP this spell costs to cast. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float MPCost;

	/** ATK added to the player's base stat by equipping this item. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float ATK;

	/** DEF added to the player's base stat by equipping this item. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float DEF;

	/** SPD added to the player's base stat by equipping this item. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float SPD;

	/** HP added to the player's base stat by equipping this item. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float HP;

	/** MP added to the player's base stat by equipping this item. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float MP;

	/** Large Icon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Details)
	UTexture2D* LargeIcon;

	/** Small Icon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Details)
	UTexture2D* SmallIcon;

	/** Player Master Reference */
	// Uses a forward declaration to avoid circular dependency
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	AEtherealPlayerMaster* OwnerReference;

	FORCEINLINE void SetupSMComponentsWithCollision(UStaticMeshComponent* Comp)
	{
		if (!Comp) return;

		Comp->bOwnerNoSee = false;
		Comp->bCastDynamicShadow = true;
		Comp->CastShadow = true;
		Comp->BodyInstance.SetObjectType(ECC_WorldDynamic);
		Comp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Comp->BodyInstance.SetResponseToAllChannels(ECR_Ignore);
		Comp->SetVisibility(false);
		Comp->SetHiddenInGame(false);
	}

	FORCEINLINE void SetupSKComponentsWithCollision(USkeletalMeshComponent* Comp)
	{
		if (!Comp) return;

		Comp->bOwnerNoSee = false;
		Comp->bCastDynamicShadow = true;
		Comp->CastShadow = true;
		Comp->BodyInstance.SetObjectType(ECC_WorldDynamic);
		Comp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Comp->BodyInstance.SetResponseToAllChannels(ECR_Ignore);
		Comp->SetVisibility(false);
		Comp->SetHiddenInGame(false);
	}
};
