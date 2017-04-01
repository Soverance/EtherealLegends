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
#include "Nightshade.generated.h"

UCLASS()
class ETHEREAL_API ANightshade : public AEtherealEnemyMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ANightshade(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Spotlight
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light)
	USpotLightComponent* SpotLight;

	// Power Blast collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* PowerBlastBox;

	// Spin Atk collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* SpinAtkBox;

	// Power Blast Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* PowerBlastAudio;
	USoundCue* S_PowerBlastAudio;

	// Spin Atk Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* SpinAtkAudio;
	USoundCue* S_SpinAtkAudio;

	// Death Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* DeathAudio;
	USoundCue* S_DeathAudio;
	
	// Build Up FX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* BuildUpFX;
	UParticleSystem* P_BuildUpFX;

	// Power Blast FX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* PowerBlastFX;
	UParticleSystem* P_PowerBlastFX;

	// Spin Atk FX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* SpinAtkFX;
	UParticleSystem* P_SpinAtkFX;

	// Do Power Blast anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoPowerBlast;

	// Do Spin Atk anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoSpinAtk;

	// Do Radial Blast anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoRadialBlast;
	
	// Melee Attack Function
	UFUNCTION(BlueprintCallable, Category = Default)
	void AttackCycle();

	// Power Blast Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void PowerBlast();

	// Blade Spin Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void SpinAttack();

	// Radial Blast Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void RadialBlast();

	// Death
	UFUNCTION(BlueprintCallable, Category = Default)
	void Death();
	
	///////////////////////////
	// A.I.
	
	// Called when seeing a pawn
	UFUNCTION()
	virtual void OnSeePawn(APawn* Pawn);

	// Called when hearing noise
	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);
};
