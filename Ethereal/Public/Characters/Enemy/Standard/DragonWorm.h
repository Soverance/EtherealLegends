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

#include "Characters/Enemy/EtherealEnemyMaster.h"
#include "DragonWorm.generated.h"

UCLASS()
class ETHEREAL_API ADragonWorm : public AEtherealEnemyMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ADragonWorm(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Custom Hit Collider, since this enemy has a larger base than the capsule collider allows for
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	USphereComponent* CustomHitRadius;

	// Does a Fireball Spit attack animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoSpit;

	// Does a Melee Swing attack animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoSwing;

	// Lava Blob Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UStaticMeshComponent* RockBase;
	UStaticMesh* SM_RockBase;

	// Lava Blob Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UStaticMeshComponent* LavaBlob;
	UStaticMesh* SM_LavaBlob;

	// Aggro Flare FX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* AggroFlare;
	UParticleSystem* P_AggroFlare;

	// Aggro Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* AggroAudio;
	USoundCue* S_AggroAudio;

	// Spit Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* SpitAudio;
	USoundCue* S_SpitAudio;

	// Death Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* DeathAudio;
	USoundCue* S_DeathAudio;
	
	// Attack Cycle
	UFUNCTION(BlueprintCallable, Category = Default)
	void StartAttackCycle();
	
	// Death
	UFUNCTION(BlueprintCallable, Category = Default)
	void Death();

	// Worm Aggro
	UFUNCTION(BlueprintCallable, Category = Default)
	void WormAggro();

	// Run to Target
	UFUNCTION(BlueprintCallable, Category = Default)
	void WormDeaggro();
	
	///////////////////////////
	// A.I.
	
	// Called when seeing a pawn
	UFUNCTION()
	virtual void OnSeePawn(APawn* Pawn);

	// Called when hearing noise
	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);
};
