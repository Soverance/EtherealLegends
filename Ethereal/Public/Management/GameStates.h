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
enum class EGameStates : uint8
{
	GS_Startup UMETA(DisplayName = "Startup"),
	GS_MainMenu UMETA(DisplayName = "Main Menu"),
	GS_Menu UMETA(DisplayName = "Menu"),
	GS_Shop UMETA(DisplayName = "Shop"),
	GS_Loading UMETA(DisplayName = "Loading Screen"),
	GS_Playing UMETA(DisplayName = "Playing Game"),
	GS_Error UMETA(DisplayName = "Error Dialog"),
	GS_Credits UMETA(DisplayName = "Credits Screen"),
	GS_Dead UMETA(DisplayName = "Dead Player"),
	GS_Unknown UMETA(DisplayName = "Unknown"),
};
