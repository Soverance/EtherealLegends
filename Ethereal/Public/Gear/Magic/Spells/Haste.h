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

#include "Gear/Magic/Magic_Master.h"
#include "Haste.generated.h"

UCLASS()
class ETHEREAL_API AHaste : public AMagic_Master
{
	GENERATED_BODY()
	
public:

	AHaste(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	/** Casts this spell. */
	UFUNCTION(BlueprintCallable, Category = Controls)
	void Cancel();

	/** Charge Spell. */
	UFUNCTION(BlueprintCallable, Category = Casting)
	virtual void ChargeHaste();

	/** Cast Spell. */
	UFUNCTION(BlueprintCallable, Category = Casting)
	virtual void CastHaste();

	/** Add SPD Boost effect. */
	UFUNCTION(BlueprintCallable, Category = Casting)
	virtual void IncreaseSPD();

	/** Remove SPD Boost effect. */
	UFUNCTION(BlueprintCallable, Category = Casting)
	virtual void DecreaseSPD();

	/** SPD added to the player's base stat by casting this spell. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Casting)
	float StoredSPDBoost;
};
