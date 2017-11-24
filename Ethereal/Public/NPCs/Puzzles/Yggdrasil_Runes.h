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
#include "DestructibleComponent.h"
#include "DestructibleMesh.h"
#include "Yggdrasil_Runes.generated.h"

UENUM(BlueprintType)
enum class ECurrentRune : uint8
{
	CR_None UMETA(DisplayName = "NONE"),
	CR_Alcove UMETA(DisplayName = "Alcove"),
	CR_Treetop UMETA(DisplayName = "Treetop"),
	CR_Rotunda UMETA(DisplayName = "Rotunda"),
};

UCLASS()
class ETHEREAL_API AYggdrasil_Runes : public AEtherealNPCMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	AYggdrasil_Runes(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Interact with this NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void Interact();


	// RUNES

	// Interact Box - Player must be within this volume in order to interact with this NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* InteractBox_Alcove;

	// Interact Box - Player must be within this volume in order to interact with this NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* InteractBox_Rotunda;

	// Interact Box - Player must be within this volume in order to interact with this NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* InteractBox_Treetop;

	
	// Rune Alcove Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UStaticMeshComponent* Rune_Alcove;
	UStaticMesh* SM_Rune_Alcove;

	// Rune Rotunda Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UStaticMeshComponent* Rune_Rotunda;
	UStaticMesh* SM_Rune_Rotunda;

	// Rune Treetop Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UStaticMeshComponent* Rune_Treetop;
	UStaticMesh* SM_Rune_Treetop;

	// Rune Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* AlcoveFX;
	UParticleSystem* P_AlcoveFX;

	// Rune Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* RotundaFX;
	UParticleSystem* P_RotundaFX;

	// Rune Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* TreetopFX;
	UParticleSystem* P_TreetopFX;

	// Rune Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* AlcoveAudio;
	USoundCue* S_AlcoveAudio;

	// Rune Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* RotundaAudio;
	USoundCue* S_RotundaAudio;

	// Rune Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* TreetopAudio;
	USoundCue* S_TreetopAudio;

	// Point Light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UPointLightComponent* PointLight_Alcove;

	// Point Light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UPointLightComponent* PointLight_Rotunda;

	// Point Light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UPointLightComponent* PointLight_Treetop;


	// TREE


	// Point Light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UPointLightComponent* PointLight_LeftEye;

	// Point Light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UPointLightComponent* PointLight_RightEye;

	// Left Eye Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* LeftEyeFX;
	UParticleSystem* P_LeftEyeFX;

	// Right Eye Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* RightEyeFX;
	UParticleSystem* P_RightEyeFX;

	// Tree Trunk Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UStaticMeshComponent* TreeTrunk;
	UStaticMesh* SM_TreeTrunk;

	// Tree Top Branches Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UStaticMeshComponent* TreeBranches;
	UStaticMesh* SM_TreeBranches;

	// Tree Head Destructible Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UDestructibleComponent* TreeHead;
	UDestructibleMesh* DM_TreeHead;

	// Energy Pillar Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* EnergyPillarFX;
	UParticleSystem* P_EnergyPillarFX;

	// Pillar Aura Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* PillarAuraFX;
	UParticleSystem* P_PillarAuraFX;

	// Lift Indicator Aura Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* LiftIndicatorFX;
	UParticleSystem* P_LiftIndicatorFX;

	// Head Explosion Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* HeadExplosionAudio;
	USoundCue* S_HeadExplosionAudio;

	// Energy Charge Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* EnergyChargeAudio;
	USoundCue* S_EnergyChargeAudio;

	// Rune Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* AuraAudio;
	USoundCue* S_AuraAudio;

	// The root for the Tree
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	USceneComponent* TreeBase;

	// VARIABLES


	// Whether this puzzle has been solved
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	bool Solved;

	// Whether Alcove Rune has been activated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	bool Active_Alcove;

	// Whether Rotunda Rune has been activated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	bool Active_Rotunda;

	// Whether Treetop Rune has been activated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	bool Active_Treetop;

	// The current rune being used by the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	ECurrentRune CurrentRune;

	// When the player enters the InteractBox related to this statue
	UFUNCTION(BlueprintCallable, Category = Default)
	void Entered_Alcove(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// When the player enters the InteractBox related to this statue
	UFUNCTION(BlueprintCallable, Category = Default)
	void Entered_Rotunda(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// When the player enters the InteractBox related to this statue
	UFUNCTION(BlueprintCallable, Category = Default)
	void Entered_Treetop(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Action)
	void ResetRuneInteraction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Action)
	void InteractWithRune();
};
