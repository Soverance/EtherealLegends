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

#include "Gear/Weapons/Weapon_Master.h"
#include "BeamSaber.generated.h"

UCLASS()
class ETHEREAL_API ABeamSaber : public AWeapon_Master
{
	GENERATED_BODY()
	
public:

	ABeamSaber(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	UBoxComponent* SwordCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("SwordCollider"));

	// Beam Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
	UStaticMeshComponent* BeamMesh;
	UStaticMesh* SM_BeamMesh;

	// Ignition Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* IgnitionAudio;
	USoundCue* S_IgnitionAudio;

	// Off Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* OffAudio;
	USoundCue* S_OffAudio;

	// Idle Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* IdleAudio;
	USoundCue* S_IdleAudio;

	// Binds the item.
	UFUNCTION(BlueprintCallable, Category = Controls)
	void BindWeapon();

	// Activates the saber's Beam.
	UFUNCTION(BlueprintCallable, Category = Controls)
	void ActivateBeam();

	// Deactivates the saber's Beam.
	UFUNCTION(BlueprintCallable, Category = Controls)
	void DisableBeam();

	// Beam Timeline.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UTimelineComponent* BeamTimeline;

	// Beam Curve.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UCurveFloat* BeamCurve;

	// Timeline Interp Function
	FOnTimelineFloat InterpFunction{};

	// Timeline Float Return
	UFUNCTION(BlueprintCallable, Category = Default)
	void TimelineFloatReturn(float val);

	// Unbinds this item, hiding it from the player.
	UFUNCTION(BlueprintCallable, Category = Controls)
	void CustomRemoveWeapon();
};
