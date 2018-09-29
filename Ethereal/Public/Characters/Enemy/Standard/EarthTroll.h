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
#include "EarthTroll.generated.h"

UCLASS()
class ETHEREAL_API AEarthTroll : public AEtherealEnemyMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	AEarthTroll(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Spit Box collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* SpitBox;

	// Troll Hammer Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UStaticMeshComponent* Hammer;
	UStaticMesh* SM_Hammer;

	// Vomit FX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* VomitFX;
	UParticleSystem* P_VomitFX;

	// Do a Roar anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoRoar;

	// Do Sling anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoSling;

	// Do Swipe anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoSwipe;

	// Do Spit anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoSpit;

	// Aggro Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* AggroAudio;
	USoundCue* S_AggroAudio;

	// Swipe Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* SwipeAudio;
	USoundCue* S_SwipeAudio;

	// Spit Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* SpitAudio;
	USoundCue* S_SpitAudio;

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
	
	// Melee Attack Function
	UFUNCTION(BlueprintCallable, Category = Default)
	void MeleeAttack();
	
	// Death
	UFUNCTION(BlueprintCallable, Category = Default)
	void CustomDeath();

	// Sling Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void Sling();

	// Swipe Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void Swipe();

	// Spit Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void Spit();
	
	///////////////////////////
	// A.I.
	
	// Called when seeing a pawn
	UFUNCTION()
	virtual void OnSeePawn(APawn* Pawn);

	// Called when hearing noise
	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);
};
