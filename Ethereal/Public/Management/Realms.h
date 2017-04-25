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

UENUM(BlueprintType)
enum class ERealms : uint8
{
	R_MainMenu UMETA(DisplayName = "Main Menu"),
	R_Loading UMETA(DisplayName = "Loading Screen"),
	R_Arcadia UMETA(DisplayName = "Arcadia"),
	R_Shiitake UMETA(DisplayName = "Shiitake Temple"),
	R_Vulcan UMETA(DisplayName = "Vulcan Shrine"),
	R_Boreal UMETA(DisplayName = "Boreal Core"),
	R_Yggdrasil UMETA(DisplayName = "Yggdrasil"),
	R_Empyrean UMETA(DisplayName = "Empyrean Gardens"),
	R_Celestial UMETA(DisplayName = "Celestial Nexus"),
	R_Arena UMETA(DisplayName = "Arena"),
};
