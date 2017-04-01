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

#include "NPCs/Characters/NPCCharacterMaster.h"
#include "Lilster.generated.h"

UCLASS()
class ETHEREAL_API ALilster : public ANPCCharacterMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ALilster(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Targeting Reticle Mesh.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	USkeletalMeshComponent* Mesh;
	USkeletalMesh* SM_Mesh;

	// Interact with this NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void Interact();

	// Interact Widget.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TSubclassOf<UUserWidget> W_InteractWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UUserWidget* InteractWidget;

	// Add the Shop widget to viewport
	UFUNCTION(BlueprintCallable, Category = Default)
	void EnableConsumableShop();

	// Hide the Interact Widget for this NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void DisableConsumableShop();

	// Spawns all items the Priest can possibly have in his inventory
	UFUNCTION(BlueprintCallable, Category = Default)
	void SpawnDefaultShopItems();

	// Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
	bool Shrug;

	// Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
	bool GiveObject;

	// Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
	bool SayNo;

	// Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
	bool Yawn;
};
