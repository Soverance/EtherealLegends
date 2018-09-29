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
#include "ProtoZhan.generated.h"

UCLASS()
class ETHEREAL_API AProtoZhan : public AEtherealEnemyMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	AProtoZhan(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Laughter Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* LaughterAudio;
	USoundCue* S_LaughterAudio;
	
	// Blade Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UStaticMeshComponent* Blade;
	UStaticMesh* SK_Blade;

	// Do Atk1 anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoAtk1;

	// Do Atk2 anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoAtk2;

	// Do Atk3 anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoAtk3;

	// Do Atk4 anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoAtk4;

	// Do Burst anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoBurst;

	// Death
	UFUNCTION(BlueprintCallable, Category = Default)
	void CustomDeath();

	//  Attack Cycle
	UFUNCTION(BlueprintCallable, Category = Default)
	void AttackCycle();

	///////////////////////////
	// A.I.

	// Called when seeing a pawn
	UFUNCTION()
	virtual void OnSeePawn(APawn* Pawn);

	// Called when hearing noise
	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);
};
