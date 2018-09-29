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
#include "Golem.generated.h"

UCLASS()
class ETHEREAL_API AGolem : public AEtherealEnemyMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	AGolem(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Aggro Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* AggroAudio;
	USoundCue* S_AggroAudio;

	// Melee Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* MeleeAudio;
	USoundCue* S_MeleeAudio;

	// Stomp Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* StompAudio;
	USoundCue* S_StompAudio;

	// Death Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* DeathAudio;
	USoundCue* S_DeathAudio;
	
	// Lightning Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* LightningAudio;
	USoundCue* S_LightningAudio;

	// Lightning FX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* LightningFX;
	UParticleSystem* P_LightningFX;

	// Do Hide anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoHide;

	// Do Melee1 anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoMelee1;

	// Do Melee2 anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoMelee2;

	// Do Stomp anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoStomp;

	// Golem Aggro - unhide self
	UFUNCTION(BlueprintCallable, Category = Default)
	void GolemAggro();

	// Golem Deaggro - go back to hiding
	UFUNCTION(BlueprintCallable, Category = Default)
	void GolemDeaggro();
	
	// Melee Attack Function
	UFUNCTION(BlueprintCallable, Category = Default)
	void MeleeAttack();

	// Melee1 Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void Melee1();

	// Melee2 Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void Melee2();

	// Stomp Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void Stomp();

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
