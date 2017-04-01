// Â© 2014 - 2017 Soverance Studios
// http://www.soverance.com

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http ://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "Gear/EtherealGearMaster.h"
#include "Weapon_Master.generated.h"

UCLASS()
class ETHEREAL_API AWeapon_Master : public AEtherealGearMaster
{
	GENERATED_BODY()
	
public:

	AWeapon_Master(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;
	
	/** Weapon Meshes. */
	// Weapon Skeletal Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
	USkeletalMeshComponent* WeaponSkeletalMesh;
	USkeletalMesh* SK_WeaponSkeletalMesh;
	// Weapon Static Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
	UStaticMeshComponent* WeaponStaticMesh;
	UStaticMesh* SM_WeaponStaticMesh;
	// Weapon Offhand (used mainly for Magic Orb type weapons).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
	UStaticMeshComponent* WeaponOffhandMesh;
	UStaticMesh* SM_WeaponOffhandMesh;

	UFUNCTION(BlueprintCallable, Category = Combat)
	void OnHit(UObject* CharacterMaster);

	// Whether or not this weapon will be shown during the binding process
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
	bool IsShown;

	// Makes this Weapon Visible
	UFUNCTION(BlueprintCallable, Category = Controls)
	virtual void ShowWeapon(bool SkeletalWeapon, bool StaticWeapon, bool OffhandWeapon);

	// Hides this weapon from the player's view
	UFUNCTION(BlueprintCallable, Category = Controls)
	virtual void HideWeapon();

	// Unbinds this item, hiding it from the player.
	UFUNCTION(BlueprintCallable, Category = Controls)
	virtual void RemoveWeapon();
};
