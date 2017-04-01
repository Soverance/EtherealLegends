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
#include "CombatEffectStruct.h"
#include "VisualEffect.generated.h"

UCLASS()
class ETHEREAL_API AVisualEffect : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AVisualEffect(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/** The root scene component for all Visual Effect actors. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	USceneComponent* Root;
	
	// Status FX.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* StatusFX;
	UParticleSystem* P_StatusFX;

	// Status FX.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	FCombatEffectStruct CombatEffect;

	/** Casts this spell. */
	UFUNCTION(BlueprintCallable, Category = Controls)
	void StartFX(FCombatEffectStruct Effect);
};
