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
#include "Gatekeeper.generated.h"

// Forward Declaration
class UTutorial;

UCLASS()
class ETHEREAL_API AGatekeeper : public AEtherealNPCMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	AGatekeeper(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Interact Box - Player must be within this volume in order to interact with this NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* CombatBox_Right;

	// Interact Box - Player must be within this volume in order to interact with this NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UBoxComponent* CombatBox_Left;

	// Function called when the player enters the InteractBox
	UFUNCTION(BlueprintCallable, Category = Default)
	void EnterCombatTutorialZone(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Function called when the player can no longer interact with this NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void ExitCombatTutorialZone(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Mesh.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	USkeletalMeshComponent* Mesh;
	USkeletalMesh* SM_Mesh;

	// Interact with this NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void CustomInteract();

	// SpawnTutorialWidget
	UFUNCTION(BlueprintCallable, Category = Default)
	void SpawnTutorialWidget();

	// Show tutorial conversation
	UFUNCTION(BlueprintCallable, Category = Default)
	void ShowConversation();

	// Interact Widget Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TSubclassOf<UUserWidget> W_InteractWidget;
	UUserWidget* InteractWidget;

	// Tutorial Widget Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UTutorial* Tutorial;

	// Whether the player has STARTED the tutorial
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	bool StartedTutorial;

	// Whether the player has COMPLETED the tutorial. Gets set true when you read the last tutorial panel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	bool CompletedTutorial;

	// Explain Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	bool DoExplain;

	// Huh Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	bool DoHuh;

	// Warning Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	bool DoWarning;	
};
