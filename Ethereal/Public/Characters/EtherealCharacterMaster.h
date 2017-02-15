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

#include "GameFramework/Character.h"
#include "EtherealGameInstance.h"
#include "Management/CommonLibrary.h"
#include "Management/EtherealAudioManager.h"
#include "CombatText/CombatTextComponent.h"
#include "EtherealCharacterMaster.generated.h"

UCLASS()
class ETHEREAL_API AEtherealCharacterMaster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEtherealCharacterMaster(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;

	// Whether or not this character is dead
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool IsDead;

	// Whether or not the character was hit by an attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool IsHit;

	// Whether or not this character is targetable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Targeting)
	bool Targetable;

	// The combat text component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UCombatTextComponent* CombatTextComponent;

	// Melee Radius Collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	USphereComponent* MeleeRadius;

	// Reference to the instance of EtherealAudioMaster
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	AEtherealAudioManager* AudioManager;

	// A Reference to the Ethereal Game Instance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UEtherealGameInstance* EtherealGameInstance;

	// Targeting Reticle Mesh.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Targeting)
	UStaticMeshComponent* TargetingReticle;
	UStaticMesh* SM_TargetingReticle;

	/** Sets Mesh visibility based on Weapon Type. */
	UFUNCTION(BlueprintCallable, Category = Targeting)
	void ToggleReticle(bool Visible);

	// Show Combat Damage Text
	UFUNCTION(BlueprintCallable, Category = Combat)
	void ShowCombatDamageText(bool IsCritical, float Damage);

	////////////////////////////
	// MAP MARKER

	// Map Marker Particle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* MapMarkerFX;
	UParticleSystem* P_MapMarkerFX;

	// Activates the Map Marker
	UFUNCTION(BlueprintCallable, Category = Map)
	void ShowMapMarker();

	// Deactivates the Map Marker
	UFUNCTION(BlueprintCallable, Category = Map)
	void HideMapMarker();
};
