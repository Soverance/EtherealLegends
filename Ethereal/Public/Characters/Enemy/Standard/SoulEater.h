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
#include "SoulEater.generated.h"

UCLASS()
class ETHEREAL_API ASoulEater : public AEtherealEnemyMaster
{
	GENERATED_BODY()
	
public:

	ASoulEater(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Do a Roar animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool Roar;
	
	// Do a melee attack animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool Attack;

	// Melee Attack Function
	UFUNCTION(BlueprintCallable, Category = Default)
	void MeleeAttack();

	// Disappear Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* DeathAudio;
	USoundCue* S_DeathAudio;

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
