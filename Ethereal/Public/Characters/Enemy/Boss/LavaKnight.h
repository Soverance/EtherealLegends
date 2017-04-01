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
#include "LavaKnight.generated.h"

UCLASS()
class ETHEREAL_API ALavaKnight : public AEtherealEnemyMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ALavaKnight(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Weapon Skeletal Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
	USkeletalMeshComponent* WeaponSkeletalMesh;
	USkeletalMesh* SK_WeaponSkeletalMesh;
	
	// Death Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* DeathAudio;
	USoundCue* S_DeathAudio;

	// Atk1 Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoAtk1;

	// Atk2 Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoAtk2;
	
	// Casting1 Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoCasting1;

	// Casting2 Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoCasting2;

	// Kick Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoKick;

	// PowerUp Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoPowerUp;

	// Combo Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoCombo;

	// Attack Cycle Function
	UFUNCTION(BlueprintCallable, Category = Default)
	void AttackCycle();

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
