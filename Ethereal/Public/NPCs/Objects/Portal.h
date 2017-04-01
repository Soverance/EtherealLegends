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

#include "NPCs/EtherealNPCMaster.h"
#include "Portal.generated.h"

UCLASS(Blueprintable)
class ETHEREAL_API APortal : public AEtherealNPCMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	APortal(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Interact with this NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void Interact();

	// Base Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UStaticMeshComponent* Base;
	UStaticMesh* SM_Base;

	// Portal Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* PortalAudio;
	USoundCue* S_PortalAudio;

	// Holosphere Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* HolosphereFX;
	UParticleSystem* P_HolosphereFX;

	// Holospire Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* HolospireFX;
	UParticleSystem* P_HolospireFX;

	// Holo Burst Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* BurstFX;
	UParticleSystem* P_BurstFX;

	// Do the Burst effect when activating the portal
	UFUNCTION(BlueprintCallable, Category = Default)
	void DoBurstEffect();

	// Interact Widget.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TSubclassOf<UUserWidget> W_InteractWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UUserWidget* InteractWidget;

	// Hide the Interact Widget for this NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void DisableInteractWidget();
};
