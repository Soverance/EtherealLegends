// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#pragma once

#include "Gear/EtherealGearMaster.h"
#include "Weapon_Master.generated.h"

/**
 * 
 */
UCLASS()
class ETHEREAL_API AWeapon_Master : public AEtherealGearMaster
{
	GENERATED_BODY()
	
public:

	AWeapon_Master(const FObjectInitializer& ObjectInitializer);

	/** Whether or not this weapon is visible on screen. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool IsVisible;
	/** Sets Mesh visibility based on Weapon Type. */
	UFUNCTION(BlueprintCallable, Category = Controls)
	void SetVisible();
	/** Weapon Static Mesh. */
	//UFUNCTION(BlueprintCallable, Category = Meshes)
	UStaticMeshComponent* WeaponStaticMesh;
	UStaticMesh* SM_WeaponStaticMesh;

	FORCEINLINE void SetupSMComponentsWithCollision(UStaticMeshComponent* Comp)
	{
		if (!Comp) return;

		Comp->bOwnerNoSee = false;
		Comp->bCastDynamicShadow = true;
		Comp->CastShadow = true;
		Comp->BodyInstance.SetObjectType(ECC_WorldDynamic);
		Comp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Comp->BodyInstance.SetResponseToAllChannels(ECR_Ignore);
		Comp->SetHiddenInGame(false);
	}
};
