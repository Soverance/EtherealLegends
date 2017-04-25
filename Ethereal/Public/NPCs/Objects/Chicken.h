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

#include "NPCs/Characters/NPCCharacterMaster.h"
#include "Chicken.generated.h"

UCLASS()
class ETHEREAL_API AChicken : public AEtherealNPCMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	AChicken(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Targeting Reticle Mesh.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	USkeletalMeshComponent* Mesh;
	USkeletalMesh* SM_Mesh;

	// Burst Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* BurstFX;
	UParticleSystem* P_BurstFX;

	// Kick Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* KickAudio;
	USoundCue* S_KickAudio;

	// Chicken Movement Node 0
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	USceneComponent* Node0;

	// Chicken Movement Node 1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	USceneComponent* Node1;

	// Chicken Movement Node 2
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	USceneComponent* Node2;

	// Chicken Movement Node 3
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	USceneComponent* Node3;

	// Chicken Movement Node 4
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	USceneComponent* Node4;

	// Node Location Array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TArray<FVector> NodeLocations;

	// Interact with this NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void Interact();

	// Blow up the chicken, cause you kicked it like an asshole!
	UFUNCTION(BlueprintCallable, Category = Default)
	void BlowUp();

	// Determines whether or not to drop an item
	UFUNCTION(BlueprintCallable, Category = Default)
	void DropItem();

	// Patrol - simply moves to the next random node
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Default)
	void Patrol();

	// Wait  -  simply waits at the current node.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Default)
	void Wait();

	// Movement Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
	float Speed;

	// Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
	bool IsDead;
};
