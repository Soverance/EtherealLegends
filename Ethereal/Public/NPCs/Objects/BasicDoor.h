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
#include "BasicDoor.generated.h"

UCLASS()
class ETHEREAL_API ABasicDoor : public AEtherealNPCMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ABasicDoor(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Interact with this NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void CustomInteract();
	
	// Open Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* OpenAudio;
	USoundCue* S_OpenAudio;
};
