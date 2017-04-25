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

#include "Magic_AnimTypes.generated.h"

UENUM(BlueprintType)
enum class EMagic_AnimTypes : uint8
{
	AT_None UMETA(DisplayName = "NONE"),
	AT_Dash UMETA(DisplayName = "Dash"),
	AT_Standard UMETA(DisplayName = "Standard"),
	AT_GroundUp UMETA(DisplayName = "Ground Up"),
	AT_TopDown UMETA(DisplayName = "Top Down"),
	AT_ForwardBlast UMETA(DisplayName = "Forward Blast"),
};
