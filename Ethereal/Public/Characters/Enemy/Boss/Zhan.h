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
#include "Zhan.generated.h"

UCLASS()
class ETHEREAL_API AZhan : public AEtherealEnemyMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	AZhan(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Laughter Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* LaughterAudio;
	USoundCue* S_LaughterAudio;

	// Power Blast collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* PowerBlastBox;

	// Spin Atk collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* SpinAtkBox;
	
	// Blade Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	USkeletalMeshComponent* Blade;
	USkeletalMesh* SK_Blade;

	// Power Blast Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* PowerBlastAudio;
	USoundCue* S_PowerBlastAudio;

	// Spin Atk Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* SpinAtkAudio;
	USoundCue* S_SpinAtkAudio;

	// Eye FX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* EyeFX;
	UParticleSystem* P_EyeFX;

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

	// If HasFallen is true, then Zhan is on the ground in the Realm, and we can allow his AI senses to aggro the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool HasFallen;

	// Do Fall Aggro Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoFallAggro;

	// Do Power Blast anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoPowerBlast;

	// Do Spin Atk anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoSpinAtk;

	// Do Radial Blast anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool DoRadialBlast;

	// Starting Height Offset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	float StartHeightOffset;

	// Death
	UFUNCTION(BlueprintCallable, Category = Default)
	void Death();

	// Escape FX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* EscapeFX;
	UParticleSystem* P_EscapeFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* EscapeBurstFX;
	UParticleSystem* P_EscapeBurstFX;

	// Portal Explosion Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* PortalExplosionAudio;
	USoundCue* S_PortalExplosionAudio;

	// Escape Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* EscapeAudio;
	USoundCue* S_EscapeAudio;

	// Init Aggro - Called by a Realm Boss when it dies
	UFUNCTION(BlueprintCallable, Category = Default)
	void InitAggro();

	// Aggro Drop Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	TSubclassOf<class AActor> AggroDropBP;

	// Fall To Aggro - handles effects of Zhan enemy pops
	UFUNCTION(BlueprintCallable, Category = Default)
	void FallToAggro();

	// Begin Attack cycle
	UFUNCTION(BlueprintCallable, Category = Default)
	void StartAttacking();

	//  Attack Cycle
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

	// Zhan Escape Realm - called on death
	UFUNCTION(BlueprintCallable, Category = Default)
	void Escape();

	// Zhan Escape Explode to nothing
	UFUNCTION(BlueprintCallable, Category = Default)
	void Explode();

	// Zhan Escape Drop Arcadia Return Portal
	UFUNCTION(BlueprintCallable, Category = Default)
	void DropPortal();

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

	///////////////////////////
	// A.I.

	// Called when seeing a pawn
	UFUNCTION()
	virtual void OnSeePawn(APawn* Pawn);

	// Called when hearing noise
	UFUNCTION()
	virtual void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);
};
