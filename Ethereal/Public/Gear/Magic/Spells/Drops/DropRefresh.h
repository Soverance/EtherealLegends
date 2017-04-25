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

#include "GameFramework/Actor.h"
#include "DropRefresh.generated.h"

UCLASS()
class ETHEREAL_API ADropRefresh : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADropRefresh(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// The root scene component for all gear actors.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	USceneComponent* Root;

	/** This emitter is active when this spell is in a charging state. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* OrbitFX;
	UParticleSystem* P_OrbitFX;

	// Rotating Movement Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	URotatingMovementComponent* RotatingMovement;

	// Orbit Timeline.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UTimelineComponent* OrbitTimeline;

	// Orbit Curve.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UCurveFloat* OrbitCurve;

	// Timeline Interp Function
	FOnTimelineFloat InterpFunction{};

	// Timeline Float Return
	UFUNCTION(BlueprintCallable, Category = Default)
	void TimelineFloatReturn(float val);

	// Timeline Float Return
	UFUNCTION(BlueprintCallable, Category = Default)
	void DestroyDrop();
	
};
