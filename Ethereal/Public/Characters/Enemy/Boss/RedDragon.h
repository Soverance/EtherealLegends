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
#include "Placements/RedDragon_Placement.h"
#include "RedDragon.generated.h"

UCLASS()
class ETHEREAL_API ARedDragon : public AEtherealEnemyMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ARedDragon(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/** Hit Box. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* HitBox;

	/** Melee Radius Breath */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* MeleeRadius_Breath;

	/** Melee Radius Tail. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* MeleeRadius_Tail;

	// Breath Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* BreathAudio;
	USoundCue* S_BreathAudio;

	// Spit Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* TailWhipAudio;
	USoundCue* S_TailWhipAudio;

	// Death Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* FlapAudio;
	USoundCue* S_FlapAudio;

	// Death Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* DeathAudio;
	USoundCue* S_DeathAudio;

	// Placement actor that contains the Spline the Dragon will fly on
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Placement)
	ARedDragon_Placement* Placement;

	// Does a Fire Breath attack when on the ground.  Only available if player is found in front of the dragon.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoBreath;

	// Does a Tail Swipe attack when on the ground. Only available if player is behind the dragon.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoSwipe;

	// Will be true while in flight
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool InFlight;

	// Set true to do a fast flap animation, usually used before taking flight
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool FastFlap;

	// Does a breath attack anim while in the air
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool FlightBreath;

	// Keeps track of how many times the dragon has taken flight. The max is two flights per battle.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	int FlightCount;

	// The distance the dragon has travelled along the flight spline
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	float DistanceOnSpline;
	
	// Attack Cycle Function
	UFUNCTION(BlueprintCallable, Category = Default)
	void AttackCycle();

	// Death
	UFUNCTION(BlueprintCallable, Category = Default)
	void Death();

	// Reset Anims, turns all anim bools false
	UFUNCTION(BlueprintCallable, Category = Default)
	void ResetAnims();

	// Decide if the dragon should take flight, or attempt to run towards the player.
	UFUNCTION(BlueprintCallable, Category = Default)
	void FireBreath();

	// Decide if the dragon should take flight, or attempt to run towards the player.
	UFUNCTION(BlueprintCallable, Category = Default)
	void TailSwipe();

	// Decide if the dragon should take flight, or attempt to run towards the player.
	UFUNCTION(BlueprintCallable, Category = Default)
	void DetermineFlight();

	// Decide if the dragon should take flight, or attempt to run towards the player.
	UFUNCTION(BlueprintCallable, Category = Default)
	void TakeFlight();

	// Forces the dragon to follow the spline while in flight. Must be run on tick.
	UFUNCTION(BlueprintCallable, Category = Default)
	void FollowSplineInFlight();
	
	///////////////////////////
	// A.I.

	// Called when seeing a pawn
	UFUNCTION()
	virtual void OnSeePawn(APawn* Pawn);

	// Called when hearing noise
	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);
};
