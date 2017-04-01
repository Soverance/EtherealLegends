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

UENUM(BlueprintType)
enum class ECombatTextTypes : uint8
{
	TT_Text UMETA(DisplayName = "Text"),
	TT_Damage UMETA(DisplayName = "Damage"),
	TT_CritDmg UMETA(DisplayName = "Critical Damage"),
	TT_HP UMETA(DisplayName = "HP Restore"),
	TT_CritHP UMETA(DisplayName = "Critical HP Restore"),
	TT_MP UMETA(DisplayName = "MP Restore"),
	TT_CritMP UMETA(DisplayName = "Critical MP Restore"),
	TT_Drop UMETA(DisplayName = "Gear Drop"),
};
