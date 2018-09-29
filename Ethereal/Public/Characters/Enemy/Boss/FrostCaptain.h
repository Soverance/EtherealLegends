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
#include "Characters/Enemy/Boss/Placements/FrostCaptain_Placement.h"
#include "FrostCaptain.generated.h"

UCLASS()
class ETHEREAL_API AFrostCaptain : public AEtherealEnemyMaster
{
	GENERATED_BODY()

public:
	
	// Sets default values for this actor's properties
	AFrostCaptain(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Aggro Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* AggroAudio;
	USoundCue* S_AggroAudio;

	// Snort Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* SnortAudio;
	USoundCue* S_SnortAudio;

	// Stomp Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* StompAudio;
	USoundCue* S_StompAudio;

	// Roar Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* RoarAudio;
	USoundCue* S_RoarAudio;

	// First Drop Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* FirstDropAudio;
	USoundCue* S_FirstDropAudio;

	// Second Drop Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* SecondDropAudio;
	USoundCue* S_SecondDropAudio;

	// Death Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* DeathAudio;
	USoundCue* S_DeathAudio;

	// Do haymaker anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoHaymaker;

	// Haymaker attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void CastHaymaker();

	// Do stomp anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoStomp;

	// Stomp Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void CastStomp();

	// Do blizzard anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoBlizzard;

	// Blizzard attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void CastBlizzard();

	// Do leap anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoLeap;

	// Do aggro anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoAggro;

	// Death
	UFUNCTION(BlueprintCallable, Category = Default)
	void CustomDeath();

	// Attack Function
	UFUNCTION(BlueprintCallable, Category = Default)
	void AttackRound();

	// Keep track of how many times the core has been powered. Max is twice.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	int PoweredCoreCount;

	// Check if the core should become powered
	UFUNCTION(BlueprintCallable, Category = Default)
	void ShouldPowerCore();

	// Power the Core
	UFUNCTION(BlueprintCallable, Category = Default)
	void PowerCore();

	// Placement actor fpr this boss
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Placement)
	AFrostCaptain_Placement* Placement;
	
	///////////////////////////
	// A.I.
	
	// Called when seeing a pawn
	UFUNCTION()
	virtual void OnSeePawn(APawn* Pawn);

	// Called when hearing noise
	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);
};
