// 2014 - 2017 Soverance Studios
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
#include "DestructibleComponent.h"
#include "DestructibleMesh.h"
#include "DemonStatue.generated.h"

UCLASS()
class ETHEREAL_API ADemonStatue : public AEtherealEnemyMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ADemonStatue(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/** Stomp Radius Collider. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	USphereComponent* StompRadius;

	/** Stomp Radius Collider. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UDestructibleComponent* DemonDoor;
	UDestructibleMesh* DM_DemonDoor;

	// Jump Timeline.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UTimelineComponent* JumpTimeline;

	// Jump Curve.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UCurveFloat* JumpCurve;

	// Timeline Interp Function
	FOnTimelineFloat InterpFunction{};

	// Timeline Float Return
	UFUNCTION(BlueprintCallable, Category = Default)
	void TimelineFloatReturn(float val);

	/////////////////////////////////////
	// EYES

	// Toggle Eyes
	UFUNCTION(BlueprintCallable, Category = Default)
	void ToggleEyes(bool ShowEyes);
	
	/** Statue Right Eye Flare. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* EyeFlareFX_R;
	UParticleSystem* P_EyeFlareFX_R;

	/** Statue Left Eye Flare. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* EyeFlareFX_L;
	UParticleSystem* P_EyeFlareFX_L;

	/** Statue Right Eye Idle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* EyeIdleFX_R;
	UParticleSystem* P_EyeIdleFX_R;

	// Statue Left Eye Idle.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* EyeIdleFX_L;
	UParticleSystem* P_EyeIdleFX_L;

	//////////////////////////////////////
	// SOUL EATER SPAWN

	// True if SoulEaters have been spawned.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	bool AreSpawned;

	// Spawn Soul Eaters upon aggro
	UFUNCTION(BlueprintCallable, Category = Default)
	void SpawnSoulEaters();

	// Soul Eater Spawn FX Left.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* SoulSpawnFX_L;
	UParticleSystem* P_SoulSpawnFX_L;

	// Soul Eater Spawn FX Right.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* SoulSpawnFX_R;
	UParticleSystem* P_SoulSpawnFX_R;

	/////////////////////////////////////
	// COMBAT
	
	/** Stomp Blast. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* StompBlastFX;
	UParticleSystem* P_StompBlastFX;

	// Stomp Decal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UDecalComponent* StompDecal;

	// Statue Jump Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* JumpAudio;
	USoundCue* S_JumpAudio;

	// Statue Stomp Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* StompAudio;
	USoundCue* S_StompAudio;

	// Soul Eater Spawn Explosion Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* ExplosionAudio;
	USoundCue* S_ExplosionAudio;

	// Death
	UFUNCTION(BlueprintCallable, Category = Default)
	void Death();

	// Stomp Attack
	UFUNCTION(BlueprintCallable, Category = Default)
	void StompAttack();

	// Stomp Blast
	UFUNCTION(BlueprintCallable, Category = Default)
	void StompBlast();

	// A.I.

	// Called when seeing a pawn
	UFUNCTION()
	virtual void OnSeePawn(APawn* Pawn);

	// Called when hearing noise
	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);
};
