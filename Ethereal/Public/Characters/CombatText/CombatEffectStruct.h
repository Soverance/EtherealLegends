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

#include "CombatEffectStruct.generated.h"

USTRUCT(BlueprintType)
struct FCombatEffectStruct
{
	GENERATED_USTRUCT_BODY()

	// Actual Effect Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CombatEffect)
	FName Name;

	// Text to display when this effect becomes active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RealmData)
	FText Text;

	// Icon to display on the Battle HUD when this effect is active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RealmData)
	UTexture2D* Icon;

	// Particle to display when this effect becomes active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RealmData)
	UParticleSystem* Effect;

	// Duration of this effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RealmData)
	float Duration;
};
