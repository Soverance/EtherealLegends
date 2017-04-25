// Â© 2014 - 2017 Soverance Studios
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
#include "Mugbear.generated.h"

UCLASS()
class ETHEREAL_API AMugbear : public AEtherealEnemyMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	AMugbear(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Do Swing Left anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoSwingLeft;

	// Do Swing Right anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoSwingRight;

	// Do Throw anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoThrow;

	// Slam Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* SlamAudio;
	USoundCue* S_SlamAudio;

	// Roar Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* RoarAudio;
	USoundCue* S_RoarAudio;

	// Death Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* DeathAudio;
	USoundCue* S_DeathAudio;
	
	// Melee Attack Function
	UFUNCTION(BlueprintCallable, Category = Default)
	void MeleeAttack();
	
	// Death
	UFUNCTION(BlueprintCallable, Category = Default)
	void Death();

	// Swing Left Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void SwingLeft();

	// Swing Right Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void SwingRight();

	// Throw Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void Throw();
	
	///////////////////////////
	// A.I.
	
	// Called when seeing a pawn
	UFUNCTION()
	virtual void OnSeePawn(APawn* Pawn);

	// Called when hearing noise
	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);
};
