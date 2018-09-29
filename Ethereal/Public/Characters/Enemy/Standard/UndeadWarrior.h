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
#include "NPCs/Characters/Gatekeeper.h"
#include "UndeadWarrior.generated.h"

UCLASS()
class ETHEREAL_API AUndeadWarrior : public AEtherealEnemyMaster
{
	GENERATED_BODY()
	
public:

	AUndeadWarrior(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// A reference to the Gatekeeper, so that this enemy can spawn a necessary tutorial panel upon it's death
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	AGatekeeper* Gatekeeper;

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

	// Killing an Undead Warrior for the first time is generally done in the tutorial, and we'll show a tutorial panel after the first kill
	UFUNCTION(BlueprintCallable, Category = Default)
	void ShowTutorialConvo();

	///////////////////////////
	// A.I.

	// Called when seeing a pawn
	UFUNCTION()
	virtual void OnSeePawn(APawn* Pawn);

	// Called when hearing noise
	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);
};
