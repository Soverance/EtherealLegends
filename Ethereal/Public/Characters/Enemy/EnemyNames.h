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

#include "EnemyNames.generated.h"

UENUM(BlueprintType)
enum class EEnemyNames : uint8
{
	EN_None UMETA(DisplayName = "NONE"),

	// Arcadia
	EN_UndeadWarrior UMETA(DisplayName = "Undead Warrior"),
	EN_SkeletonKing UMETA(DisplayName = "Skeleton King"),

	// Shiitake Temple
	EN_SoulEater UMETA(DisplayName = "Soul Eater"),
	EN_DemonStatue UMETA(DisplayName = "Demon Statue"),
	EN_Watcher UMETA(DisplayName = "Watcher"),
	EN_DeathCap UMETA(DisplayName = "Death Cap"),

	// Vulcan Shrine
	EN_Gruntling UMETA(DisplayName = "Gruntling"),
	EN_Goblin UMETA(DisplayName = "Goblin"),
	EN_DragonWorm UMETA(DisplayName = "Dragon Worm"),
	EN_RedDragon UMETA(DisplayName = "Red Dragon"),
	EN_LavaKnight UMETA(DisplayName = "Lava Knight"),

	// Boreal Core
	EN_Spider UMETA(DisplayName = "Spider"),
	EN_GiantSpider UMETA(DisplayName = "Giant Spider"),
	EN_FrostGiant UMETA(DisplayName = "Frost Giant"),
	EN_FrostCaptain UMETA(DisplayName = "Frost Captain"),

	// Yggdrasil
	EN_Flytrap UMETA(DisplayName = "Flytrap"),
	EN_Mugbear UMETA(DisplayName = "Mugbear"),
	EN_EarthTroll UMETA(DisplayName = "Earth Troll"),
	EN_GaiaTortoise UMETA(DisplayName = "Gaia Tortoise"),
	EN_GaiaTitan UMETA(DisplayName = "Gaia Titan"),

	// Empyrean Gardens
	EN_Golem UMETA(DisplayName = "Golem"),
	EN_PowerDrone UMETA(DisplayName = "Power Drone"),
	EN_Nightshade UMETA(DisplayName = "Nightshade"),
	EN_Samaritan UMETA(DisplayName = "Samaritan"),

	// Celestial Nexus	
	EN_Eternal UMETA(DisplayName = "The Eternal"),
	EN_Zhan UMETA(DisplayName = "Zhan"),

	// Signet Notorious Monsters
	EN_Daemon UMETA(DisplayName = "Daemon"),
	EN_EarthGolem UMETA(DisplayName = "Earth Golem"),
	EN_Ghost UMETA(DisplayName = "Ghost"),
	EN_IceKnight UMETA(DisplayName = "Ice Knight"),
	EN_SkyDragon UMETA(DisplayName = "Sky Dragon"),
	EN_ProtoZhan UMETA(DisplayName = "Proto Zhan"),
};
