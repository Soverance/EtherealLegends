// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "MasterGearList.h"
#include "MasterGearTypes.h"
#include "EtherealGearMaster.generated.h"

UCLASS()
class ETHEREAL_API AEtherealGearMaster : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AEtherealGearMaster();

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
};
