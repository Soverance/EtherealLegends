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

#include "WeaponModes.generated.h"

UENUM(BlueprintType)
enum class EWeaponModes : uint8
{
	WM_None UMETA(DisplayName = "NONE"),
	WM_OneHanded UMETA(DisplayName = "One-Handed"),
	WM_TwoHanded UMETA(DisplayName = "Two-Handed"),
	WM_Ranged UMETA(DisplayName = "Ranged"),
	WM_Casting UMETA(DisplayName = "Casting"),
};
