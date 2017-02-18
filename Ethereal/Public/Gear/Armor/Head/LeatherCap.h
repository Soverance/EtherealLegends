// Ã‚Â© 2014 - 2016 Soverance Studios
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

#include "Gear/Armor/Armor_Master.h"
#include "LeatherCap.generated.h"

UCLASS()
class ETHEREAL_API ALeatherCap : public AArmor_Master
{
	GENERATED_BODY()
	
public:

	ALeatherCap(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// This applies any special effect associated with the item
	UFUNCTION(BlueprintCallable, Category = Controls)
	void DoSpecialEffect();

	// This removes any special effect associated with the item
	UFUNCTION(BlueprintCallable, Category = Controls)
	void RemoveSpecialEffect();
};
