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
#include "DropBarrier.generated.h"

UCLASS()
class ETHEREAL_API ADropBarrier : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADropBarrier(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// The root scene component for all gear actors.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	USceneComponent* Root;

	// Barrier Collision Sphere
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	USphereComponent* BarrierSphere;

	// Barrier Collision Sphere
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UPointLightComponent* BarrierLight;
	
	// This is the dome of the Barrier effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* DomeFX;
	UParticleSystem* P_DomeFX;

	// Main Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* MainAudio;
	USoundCue* S_MainAudio;

	// Main Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* ActiveAudio;
	USoundCue* S_ActiveAudio;

	// Main Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* RemoveAudio;
	USoundCue* S_RemoveAudio;

	// The Defense Multipler - comes from the Barrier spell itself
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float DefenseMultiplier;

	// The Duration - comes from the Barrier spell itself
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float Duration;

	// Only true if the player is inside the barrier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	bool BarrierActive;

	// The Player's original DEF value, before activating barrier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 OriginalDefense;

	// The Bonus Defense to add to the Player's current DEF
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 BonusDefense;

	// Function called when the player enters the Sphere
	UFUNCTION(BlueprintCallable, Category = Default)
	void OnInteract(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Function called when the player can no longer interact with this object
	UFUNCTION(BlueprintCallable, Category = Default)
	void EndInteract(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Restores all HP and MP to full
	UFUNCTION(BlueprintCallable, Category = Stats)
	void DestroyBarrierDrop();
};
