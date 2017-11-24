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

#include "Ethereal.h"
#include "RealmSelect.h"

#define LOCTEXT_NAMESPACE "EtherealText"

URealmSelect::URealmSelect(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// ICONS
	static ConstructorHelpers::FObjectFinder<UTexture2D> WaterIcon(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Levels/LevelIcon-Water.LevelIcon-Water'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> FireIcon(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Levels/LevelIcon-Fire.LevelIcon-Fire'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> IceIcon(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Levels/LevelIcon-Ice.LevelIcon-Ice'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> EarthIcon(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Levels/LevelIcon-Earth.LevelIcon-Earth'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SkyIcon(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Levels/LevelIcon-Sky.LevelIcon-Sky'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SpaceIcon(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Levels/LevelIcon-Space.LevelIcon-Space'"));
	// REALM PREVIEWS
	static ConstructorHelpers::FObjectFinder<UTexture2D> ShiitakePreview(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Levels/LevelBackground_ShiitakeTemple.LevelBackground_ShiitakeTemple'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> VulcanPreview(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Levels/LevelBackground_VulcanShrine.LevelBackground_VulcanShrine'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> BorealPreview(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Levels/LevelBackground_BorealCore.LevelBackground_BorealCore'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> YggdrasilPreview(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Levels/LevelBackground_Yggdrasil.LevelBackground_Yggdrasil'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> EmpyreanPreview(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Levels/LevelBackground_EmpyreanGardens.LevelBackground_EmpyreanGardens'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> CelestialPreview(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Levels/LevelBackground_CelestialNexus.LevelBackground_CelestialNexus'"));


	// Shiitake Temple Info
	Shiitake.Realm = ERealms::R_Shiitake;
	Shiitake.NameText = LOCTEXT("RealmName_Shiitake", "Shiitake Temple");
	Shiitake.MapName = FName(TEXT("ShiitakeTemple"));
	Shiitake.Locked = true;
	Shiitake.RecLevel = 10;
	Shiitake.Description = LOCTEXT("RealmDescription_Shiitake", "A watery sanctuary overtaken by fungi, the Shiitake Temple was flooded during Zhan's betrayal. Today only the top floor is accessible.");
	Shiitake.ListIcon = WaterIcon.Object;
	Shiitake.RealmPreview = ShiitakePreview.Object;
	Realms.Add(Shiitake);

	// Vulcan Shrine Info
	Vulcan.Realm = ERealms::R_Vulcan;
	Vulcan.NameText = LOCTEXT("RealmName_Vulcan", "Vulcan Shrine");
	Vulcan.MapName = FName(TEXT("VulcanShrine"));
	Vulcan.Locked = true;
	Vulcan.RecLevel = 20;
	Vulcan.Description = LOCTEXT("RealmDescription_Vulcan", "Vulcan Shrine, a hellish landscape of fire and rock. The volcanoes have been continuously erupting since Zhan defeated the Ethereal Knights.");
	Vulcan.ListIcon = FireIcon.Object;
	Vulcan.RealmPreview = VulcanPreview.Object;
	Realms.Add(Vulcan);

	// Boreal Core Info
	Boreal.Realm = ERealms::R_Boreal;
	Boreal.NameText = LOCTEXT("RealmName_Boreal", "Boreal Core");
	Boreal.MapName = FName(TEXT("BorealCore"));
	Boreal.Locked = true;
	Boreal.RecLevel = 30;
	Boreal.Description = LOCTEXT("RealmDescription_Boreal", "A frozen cave that houses an ancient crystal core. The core's energy was once harnessed by Zhan, allowing him to overpower the Ethereal Knights.");
	Boreal.ListIcon = IceIcon.Object;
	Boreal.RealmPreview = BorealPreview.Object;
	Realms.Add(Boreal);

	// Yggdrasil Info
	Yggdrasil.Realm = ERealms::R_Yggdrasil;
	Yggdrasil.NameText = LOCTEXT("RealmName_Yggdrasil", "Yggdrasil");
	Yggdrasil.MapName = FName(TEXT("Yggdrasil"));
	Yggdrasil.Locked = true;
	Yggdrasil.RecLevel = 40;
	Yggdrasil.Description = LOCTEXT("RealmDescription_Yggdrasil", "Yggdrasil - The World Tree. A once glorious wildlife refuge, now poisoned by Zhan's malice.");
	Yggdrasil.ListIcon = EarthIcon.Object;
	Yggdrasil.RealmPreview = YggdrasilPreview.Object;
	Realms.Add(Yggdrasil);

	// Empyrean Gardens Info
	Empyrean.Realm = ERealms::R_Empyrean;
	Empyrean.NameText = LOCTEXT("RealmName_Empyrean", "Empyrean Gardens");
	Empyrean.MapName = FName(TEXT("EmpyreanGardens"));
	Empyrean.Locked = true;
	Empyrean.RecLevel = 50;
	Empyrean.Description = LOCTEXT("RealmDescription_Empyrean", "The majestic Empyrean Gardens, a technological achievement of infrastructure floating in the skies high above Arcadia.");
	Empyrean.ListIcon = SkyIcon.Object;
	Empyrean.RealmPreview = EmpyreanPreview.Object;
	Realms.Add(Empyrean);

	// Celestial Nexus Info
	Celestial.Realm = ERealms::R_Celestial;
	Celestial.NameText = LOCTEXT("RealmName_Celestial", "Celestial Nexus");
	Celestial.MapName = FName(TEXT("CelestialNexus"));
	Celestial.Locked = true;
	Celestial.RecLevel = 60;
	Celestial.Description = LOCTEXT("RealmDescription_Celestial", "The center of all Ethereal Realms, a temporal space of infinite possibility. It is here where Zhan first began his uprising, and it is here where it must end.");
	Celestial.ListIcon = SpaceIcon.Object;
	Celestial.RealmPreview = CelestialPreview.Object;
	Realms.Add(Celestial);
}

#undef LOCTEXT_NAMESPACE
