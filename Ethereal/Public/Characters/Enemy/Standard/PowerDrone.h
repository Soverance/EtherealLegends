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

#include "Characters/Enemy/EtherealEnemyMaster.h"
#include "PowerDrone.generated.h"

UCLASS()
class ETHEREAL_API APowerDrone : public AEtherealEnemyMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	APowerDrone(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	// Force Look At Target, must be run on tick
	UFUNCTION(BlueprintCallable, Category = Default)
	void LookAtTarget();

	// Melee Attack Function
	UFUNCTION(BlueprintCallable, Category = Default)
	void MeleeAttack();

	// Fire Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* FireAudio;
	USoundCue* S_FireAudio;

	// Death Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* DeathAudio;
	USoundCue* S_DeathAudio;

	// Explosion FX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* ExplosionFX;
	UParticleSystem* P_ExplosionFX;

	// Laser Blast Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	TSubclassOf<class AActor> LaserBlastBP;

	// Fire Laser Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void FireLaser();

	// Death
	UFUNCTION(BlueprintCallable, Category = Default)
	void CustomDeath();
	
	///////////////////////////
	// A.I.
	
	// Called when seeing a pawn
	UFUNCTION()
	virtual void OnSeePawn(APawn* Pawn);

	// Called when hearing noise
	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);
};
