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
#include "Gear/MasterGearList.h"
#include "Widgets/ChestDisplay.h"
#include "Chest.generated.h"

UCLASS()
class ETHEREAL_API AChest : public AEtherealNPCMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	AChest(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Interact with this NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void CustomInteract();

	// Interact Widget.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TSubclassOf<UUserWidget> W_InteractWidget;
	UChestDisplay* InteractWidget;

	// Base Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UStaticMeshComponent* Base;
	UStaticMesh* SM_Base;

	// The root scene component for the lid.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	USceneComponent* LidRoot;

	// Lid Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UStaticMeshComponent* Lid;
	UStaticMesh* SM_Lid;

	// Open Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* OpenAudio;
	USoundCue* S_OpenAudio;

	// Open Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* OpenFX;
	UParticleSystem* P_OpenFX;

	// Open Camera Shake
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	TSubclassOf<UMatineeCameraShake> OpenCamShake;

	// If the chest has an item, it is referenced here
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	EMasterGearList ItemInChest;

	// If the chest has gold, it is this amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	int32 GoldInChest;

	// Player has opened the chest
	UFUNCTION(BlueprintCallable, Category = Default)
	void OnChestTouched();

	// All checks completed, give the player an item
	UFUNCTION(BlueprintCallable, Category = Default)
	void GiveItem();

	// Player obtains Gold
	UFUNCTION(BlueprintCallable, Category = Default)
	void AddGold();

	// Player obtains an Item
	UFUNCTION(BlueprintCallable, Category = Default)
	void AddItem();

	// Show the widget
	UFUNCTION(BlueprintCallable, Category = Default)
	void ShowWidget(FText Description);

	// Open Timeline.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UTimelineComponent* OpenTimeline;

	// Open Curve.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UCurveFloat* OpenCurve;

	// Timeline Interp Function
	FOnTimelineFloat InterpFunction{};

	// Timeline Float Return
	UFUNCTION(BlueprintCallable, Category = Default)
	void TimelineFloatReturn(float val);
};
