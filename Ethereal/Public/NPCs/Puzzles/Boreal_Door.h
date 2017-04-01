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

#include "NPCs/EtherealNPCMaster.h"
#include "Boreal_Door.generated.h"

// Event Dispatchers
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSatellite1);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSatellite2);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLeftDoor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRightDoor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenDoor);

UENUM(BlueprintType)
enum class ECurrentStatue : uint8
{
	CS_None UMETA(DisplayName = "NONE"),
	CS_LeftDoor UMETA(DisplayName = "LeftDoor"),
	CS_RightDoor UMETA(DisplayName = "RightDoor"),
	CS_Satellite1 UMETA(DisplayName = "Satellite1"),
	CS_Satellite2 UMETA(DisplayName = "Satellite2"),
};

UCLASS()
class ETHEREAL_API ABoreal_Door : public AEtherealNPCMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ABoreal_Door(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Event Dispatcher On Satellite 1
	UPROPERTY(BlueprintAssignable, Category = "Dispatcher")
	FSatellite1 OnSat1;

	// Event Dispatcher On Satellite 2
	UPROPERTY(BlueprintAssignable, Category = "Dispatcher")
	FSatellite2 OnSat2;

	// Event Dispatcher Do Left Door
	UPROPERTY(BlueprintAssignable, Category = "Dispatcher")
	FLeftDoor OnLeftDoor;

	// Event Dispatcher Do Right Door
	UPROPERTY(BlueprintAssignable, Category = "Dispatcher")
	FRightDoor OnRightDoor;

	// Event Dispatcher Do Open Door
	UPROPERTY(BlueprintAssignable, Category = "Dispatcher")
	FOpenDoor OnOpenDoor;

	// Interact with this NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void Interact();

	// Door Drop Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	TSubclassOf<class AActor> DoorDropBP;

	// The Door Drop Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	AActor* DoorDrop;

	// Statue Left Door Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UStaticMeshComponent* Statue_LeftDoor;
	UStaticMesh* SM_Statue_LeftDoor;

	// Statue Right Door Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UStaticMeshComponent* Statue_RightDoor;
	UStaticMesh* SM_Statue_RightDoor;

	// Statue Satellite 1 Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UStaticMeshComponent* Statue_Satellite1;
	UStaticMesh* SM_Statue_Satellite1;

	// Statue Satellite 2 Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UStaticMeshComponent* Statue_Satellite2;
	UStaticMesh* SM_Statue_Satellite2;

	// Interact Box - Player must be within this volume in order to interact with this NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* InteractBox_LeftDoor;

	// Interact Box - Player must be within this volume in order to interact with this NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* InteractBox_RightDoor;

	// Interact Box - Player must be within this volume in order to interact with this NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* InteractBox_Satellite1;

	// Interact Box - Player must be within this volume in order to interact with this NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* InteractBox_Satellite2;

	// Aura Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* AuraFX_LeftDoor;
	UParticleSystem* P_AuraFX_LeftDoor;

	// Aura Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* AuraFX_RightDoor;
	UParticleSystem* P_AuraFX_RightDoor;

	// Aura Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* AuraFX_Satellite1;
	UParticleSystem* P_AuraFX_Satellite1;

	// Aura Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* AuraFX_Satellite2;
	UParticleSystem* P_AuraFX_Satellite2;

	// Flare Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* FlareFX_LeftDoor;
	UParticleSystem* P_FlareFX_LeftDoor;

	// Flare Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* FlareFX_RightDoor;
	UParticleSystem* P_FlareFX_RightDoor;

	// Flare Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* FlareFX_Satellite1;
	UParticleSystem* P_FlareFX_Satellite1;

	// Flare Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* FlareFX_Satellite2;
	UParticleSystem* P_FlareFX_Satellite2;

	// Flare Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* FlareAudio_LeftDoor;
	USoundCue* S_FlareAudio_LeftDoor;

	// Flare Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* FlareAudio_RightDoor;
	USoundCue* S_FlareAudio_RightDoor;

	// Flare Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* FlareAudio_Satellite1;
	USoundCue* S_FlareAudio_Satellite1;

	// Flare Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* FlareAudio_Satellite2;
	USoundCue* S_FlareAudio_Satellite2;

	// Point Light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UPointLightComponent* PointLight_LeftDoor;

	// Point Light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UPointLightComponent* PointLight_RightDoor;

	// Point Light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UPointLightComponent* PointLight_Satellite1;

	// Point Light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UPointLightComponent* PointLight_Satellite2;

	// Double Doors Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	USkeletalMeshComponent* Doors;
	USkeletalMesh* SK_Doors;

	// Doors Arch Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UStaticMeshComponent* DoorsArch;
	UStaticMesh* SM_DoorsArch;

	// Door Open Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* DoorOpenAudio;
	USoundCue* S_DoorOpenAudio;

	// Door Open Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAnimationAsset* DoorOpenAnim;

	// If the Left Door Statue is active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	bool Active_LeftDoor;

	// If the Right Door Statue is active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	bool Active_RightDoor;

	// If the Satellite 1 Statue is active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	bool Active_Satellite1;

	// If the Satellite 2 Statue is active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	bool Active_Satellite2;

	// If the puzzle has been solved. It is solved when LeftDoor and RightDoor are both active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	bool Solved;

	// Is true when the player is carrying a drop - players can only interact with inactive statues while carrying a drop.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	bool IsCarryingDrop;

	// The color of an active statue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	FColor Color_Active;

	// The color of an inactive statue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	FColor Color_Inactive;

	// The current statue being used by the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	ECurrentStatue CurrentStatue;

	// When the player enters the InteractBox related to this statue
	UFUNCTION(BlueprintCallable, Category = Default)
	void Entered_LeftDoor(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// When the player enters the InteractBox related to this statue
	UFUNCTION(BlueprintCallable, Category = Default)
	void Entered_RightDoor(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// When the player enters the InteractBox related to this statue
	UFUNCTION(BlueprintCallable, Category = Default)
	void Entered_Satellite1(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// When the player enters the InteractBox related to this statue
	UFUNCTION(BlueprintCallable, Category = Default)
	void Entered_Satellite2(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Light Timeline.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UTimelineComponent* LeftDoorTimeline;

	// Light Timeline.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UTimelineComponent* RightDoorTimeline;

	// Light Timeline.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UTimelineComponent* Satellite1Timeline;

	// Light Timeline.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UTimelineComponent* Satellite2Timeline;

	// Color Curve.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UCurveFloat* ColorCurve;

	// Timeline Interp Function
	FOnTimelineFloat InterpFunctionLeftDoor{};

	// Timeline Interp Function
	FOnTimelineFloat InterpFunctionRightDoor{};

	// Timeline Interp Function
	FOnTimelineFloat InterpFunctionSatellite1{};

	// Timeline Interp Function
	FOnTimelineFloat InterpFunctionSatellite2{};

	// Timeline Float Return
	UFUNCTION(BlueprintCallable, Category = Default)
	void LeftDoorTimelineFloatReturn(float val);

	// Timeline Float Return
	UFUNCTION(BlueprintCallable, Category = Default)
	void RightDoorTimelineFloatReturn(float val);

	// Timeline Float Return
	UFUNCTION(BlueprintCallable, Category = Default)
	void Satellite1TimelineFloatReturn(float val);

	// Timeline Float Return
	UFUNCTION(BlueprintCallable, Category = Default)
	void Satellite2TimelineFloatReturn(float val);

	// Checks if this puzzle has been solved
	UFUNCTION(BlueprintCallable, Category = Default)
	void CheckForSuccess();
};
