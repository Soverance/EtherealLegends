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
#include "Eternal.generated.h"

UCLASS()
class ETHEREAL_API AEternal : public AEtherealEnemyMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	AEternal(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	// Melee Attack Function
	UFUNCTION(BlueprintCallable, Category = Default)
	void AttackCycle();

	// Death
	UFUNCTION(BlueprintCallable, Category = Default)
	void Death();

	// Eternal Aura Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* AuraFX;
	UParticleSystem* P_AuraFX;

	// Ranged Build Up effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* RangedBuildUpFX;
	UParticleSystem* P_RangedBuildUpFX;

	// Black Hole Build Up effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* BlackHoleBuildUpFX;
	UParticleSystem* P_BlackHoleBuildUpFX;

	// Heavy Build Up effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* HeavyBuildUpFX;
	UParticleSystem* P_HeavyBuildUpFX;

	// Init Aggro - Called by Zhan's death while inside Celestial Nexus
	UFUNCTION(BlueprintCallable, Category = Default)
	void InitAggro();

	// Aggro Drop Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	TSubclassOf<class AActor> AggroDropBP;

	// RaiseToAggro - Handles the spawning of the Eternal enemy
	UFUNCTION(BlueprintCallable, Category = Default)
	void RaiseToAggro();

	// Do Raise Aggro Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoRaiseAggro;

	// Begin Attack cycle
	UFUNCTION(BlueprintCallable, Category = Default)
	void StartAttacking();

	// Do Attack1 anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoAttack1;

	// Do Attack2 anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoAttack2;

	// Do RangedAtk anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoRangedAttack;

	// Do HeavyAtk anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoHeavyAttack;

	// Power Blast Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void Attack1();

	// Blade Spin Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void Attack2();

	// Ranged Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void RangedAttack();

	// Heavy Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void HeavyAttack();

	// Death Location - gathered immediately on death, stored for later use so that we know where to spawn the EndGamePortal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	FVector DeathLocation;

	// Eternal Death
	UFUNCTION(BlueprintCallable, Category = Default)
	void EternalDeath();

	///////////////////////////
	// AUDIO

	// Aggro Voice Audio - "YOUR SOUL IS MINE!"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* AggroVoiceAudio;
	USoundCue* S_AggroVoiceAudio;

	// Ranged Build Up Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* RangedBuildUpAudio;
	USoundCue* S_RangedBuildUpAudio;

	// Black Hole Build Up Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* BlackHoleBuildUpAudio;
	USoundCue* S_BlackHoleBuildUpAudio;

	// Heavy Build Up Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* HeavyBuildUpAudio;
	USoundCue* S_HeavyBuildUpAudio;

	// Laughter Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* LaughterAudio;
	USoundCue* S_LaughterAudio;

	// Death Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* DeathAudio;
	USoundCue* S_DeathAudio;

	///////////////////////////
	// A.I.
	
	// Called when seeing a pawn
	UFUNCTION()
	virtual void OnSeePawn(APawn* Pawn);

	// Called when hearing noise
	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);
};