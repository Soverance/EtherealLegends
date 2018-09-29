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

#include "Gear/Weapons/Weapon_Master.h"
#include "Valkyrie.generated.h"

UCLASS()
class ETHEREAL_API AValkyrie : public AWeapon_Master
{
	GENERATED_BODY()
	
public:

	AValkyrie(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;
	
	// Collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	UBoxComponent* SwordCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("SwordCollider"));

	// Aura FX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* AuraFX;
	UParticleSystem* P_AuraFX;
	
	// Binds the item.
	UFUNCTION(BlueprintCallable, Category = Controls)
	void BindWeapon();

	// Removes the item.
	UFUNCTION(BlueprintCallable, Category = Controls)
	void CustomRemoveWeapon();
};
