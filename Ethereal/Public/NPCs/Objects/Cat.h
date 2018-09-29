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
#include "Cat.generated.h"

UCLASS()
class ETHEREAL_API ACat : public AEtherealNPCMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ACat(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Targeting Reticle Mesh.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	USkeletalMeshComponent* Mesh;
	USkeletalMesh* SM_Mesh;

	// Kick Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* CatAudio;
	USoundCue* S_CatAudio;

	// Interact with this NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void CustomInteract();

	// Blow up the chicken, cause you kicked it like an asshole!
	UFUNCTION(BlueprintCallable, Category = Default)
	void BlowUp();

	// Determines whether or not to drop an item
	UFUNCTION(BlueprintCallable, Category = Default)
	void DropItem();

	// Movement Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
	float Speed;

	// Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
	bool DoRoar;
};
