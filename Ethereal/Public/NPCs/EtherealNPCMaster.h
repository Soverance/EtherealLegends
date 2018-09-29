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

#include "GameFramework/Actor.h"
#include "Management/CommonLibrary.h"
#include "Characters/Player/EtherealPlayerMaster.h"
#include "NPCs/InteractAnims.h"
#include "UMG.h"
#include "EtherealNPCMaster.generated.h"

// Forward Declarations
//class AEtherealPlayerMaster;

// Event Dispatcher for Interaction
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteract);

UCLASS()
class ETHEREAL_API AEtherealNPCMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEtherealNPCMaster(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Event Dispatcher DoInteraction - used for child NPCs to call custom code
	UPROPERTY(BlueprintAssignable, Category = "Dispatcher")
	FInteract DoInteraction;

	// The root scene component for all NPC actors
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	USceneComponent* Root;

	// Interact Box - Player must be within this volume in order to interact with this NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* InteractBox;
	
	// Determines whether or not this NPC is usable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool IsUsable = true;

	// Determines what animation the player character will use when interacting with this NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	EInteractAnims InteractAnimType;

	// If interacting with this NPC requires a widget, store it's reference here.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	UWidget* ActionWidget;

	// Reference to the player currently interacting with this NPC.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	AEtherealPlayerMaster* InteractingPlayer;

	// Function called when the player enters the InteractBox
	UFUNCTION(BlueprintCallable, Category = Default)
	void OnInteract(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Function called when the player can no longer interact with this NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void EndInteract(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Check if this NPC is usable or not
	UFUNCTION(BlueprintCallable, Category = Default)
	void CheckIfUsable();

	// Begins interacting with this NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void StartInteraction();
	
	// Stops interacting with this NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void StopInteraction();

	// Interact with this NPC. This function can only be called by the player pressing the "A" button while inside the InteractBox
	UFUNCTION(BlueprintCallable, Category = Default)
	void InteractWithNpc();

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
