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

#include "NPCs/EtherealNPCMaster.h"
#include "Shiitake_Door.generated.h"

UCLASS()
class ETHEREAL_API AShiitake_Door : public AEtherealNPCMaster
{
	GENERATED_BODY()

public:
	
	// Sets default values for this actor's properties
	AShiitake_Door(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	// Interact with this NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void CustomInteract();

	// Gate 1 Interact Box - Player must be within this volume in order to interact with gate 1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* InteractBox_Gate1;

	// Gear Mesh.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UStaticMeshComponent* Gate1_Gear;
	UStaticMesh* SM_Gate1_Gear;

	// Gate Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* GateAudio;
	USoundCue* S_GateAudio;

	// Column Left Mesh.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UStaticMeshComponent* Gate1_ColumnLeft;
	UStaticMesh* SM_Gate1_ColumnLeft;

	// Column Right Mesh.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UStaticMeshComponent* Gate1_ColumnRight;
	UStaticMesh* SM_Gate1_ColumnRight;

	// Gate Mesh.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UStaticMeshComponent* Gate1;
	UStaticMesh* SM_Gate1;

	// Rotating Movement Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	URotatingMovementComponent* RotatingMovement;

	// Determines whether or not the Gate is open
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	FVector GateStartLocation;

	// Gate Timeline.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UTimelineComponent* GateTimeline;

	// Jump Curve.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UCurveFloat* GateCurve;

	// Timeline Interp Function
	FOnTimelineFloat InterpFunction{};

	// Timeline Float Return
	UFUNCTION(BlueprintCallable, Category = Default)
	void TimelineFloatReturn(float val);

	// Stop Gears
	UFUNCTION(BlueprintCallable, Category = Default)
	void StopGears();
};
