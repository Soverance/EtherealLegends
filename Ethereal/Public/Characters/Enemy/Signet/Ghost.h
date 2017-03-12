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
#include "Ghost.generated.h"

UCLASS()
class ETHEREAL_API AGhost : public AEtherealEnemyMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	AGhost(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Interact Box - Player must be within this volume in order to interact with this NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* TwirlBox;
	
	// Melee Attack Function
	UFUNCTION(BlueprintCallable, Category = Default)
	void AttackRound();

	// Death
	UFUNCTION(BlueprintCallable, Category = Default)
	void Death();

	// Swing Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attacks)
	bool DoSwing;

	// Twirl Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attacks)
	bool DoTwirl;

	// Pulse Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attacks)
	bool DoPulse;

	// Bounce Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attacks)
	bool DoBounce;

	// Twirl Hit Check
	UFUNCTION(BlueprintCallable, Category = Default)
	void TwirlHitCheck();

	///////////////////////////
	// A.I.
	
	// Called when seeing a pawn
	UFUNCTION()
	virtual void OnSeePawn(APawn* Pawn);

	// Called when hearing noise
	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);
};
