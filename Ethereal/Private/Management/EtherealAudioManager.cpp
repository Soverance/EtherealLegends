// © 2014 - 2016 Soverance Studios
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
#include "EtherealGameInstance.h"
#include "EtherealAudioManager.h"


// Sets default values
AEtherealAudioManager::AEtherealAudioManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Get Assets for Battle Music
	static ConstructorHelpers::FObjectFinder<USoundCue> StandardAudioObject(TEXT("SoundCue'/Game/Audio/Music/Battle_Standard.Battle_Standard'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> BossAudioObject(TEXT("SoundCue'/Game/Audio/Music/Battle_Boss.Battle_Boss'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ZhanIntroAudioObject(TEXT("SoundCue'/Game/Audio/Party/Zhan_Intro_Cue.Zhan_Intro_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> EternalIntroAudioObject(TEXT("SoundCue'/Game/Elemental/Sound/shrt_music_02_Cue.shrt_music_02_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ZhanBattleAudioObject(TEXT("SoundCue'/Game/Audio/Music/Battle_Zhan.Battle_Zhan'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> EternalBattleAudioObject(TEXT("SoundCue'/Game/Audio/Music/Battle_Eternal_Cue.Battle_Eternal_Cue'"));

	// Get Assets for Background Music
	static ConstructorHelpers::FObjectFinder<USoundCue> MainMenuAudioObject(TEXT("SoundCue'/Game/Audio/Music/Music_MainMenu.Music_MainMenu'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ArcadiaAudioObject(TEXT("SoundCue'/Game/Audio/Music/Music_Arcadia.Music_Arcadia'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ShiitakeAudioObject(TEXT("SoundCue'/Game/Audio/Music/Music_ShiitakeTemple.Music_ShiitakeTemple'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> VulcanAudioObject(TEXT("SoundCue'/Game/Audio/Music/Music_VulcanShrine.Music_VulcanShrine'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> BorealAudioObject(TEXT("SoundCue'/Game/Audio/Music/Music_BorealCore.Music_BorealCore'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> YggdrasilAudioObject(TEXT("SoundCue'/Game/Audio/Music/Music_Yggdrasil.Music_Yggdrasil'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> EmpyreanAudioObject(TEXT("SoundCue'/Game/Audio/Music/Music_EmpyreanGardens.Music_EmpyreanGardens'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> CelestialAudioObject(TEXT("SoundCue'/Game/Audio/Music/Music_CelestialNexus.Music_CelestialNexus'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ArenaAudioObject(TEXT("SoundCue'/Game/Audio/Music/Music_Arena.Music_Arena'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> CreditsAudioObject(TEXT("SoundCue'/Game/Audio/Music/Music_Credits_Final_Cue.Music_Credits_Final_Cue'"));

	// Get Assets for Sound Effects
	static ConstructorHelpers::FObjectFinder<USoundCue> LevelUpAudioObject(TEXT("SoundCue'/Game/Audio/Music/LevelUp_Fanfare.LevelUp_Fanfare'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> GameOverAudioObject(TEXT("SoundCue'/Game/Audio/Party/Ethereal_GameOver_Cue.Ethereal_GameOver_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> StartGameAudioObject(TEXT("SoundCue'/Game/Audio/Eth_Menu/Ethereal_StartGame_Cue.Ethereal_StartGame_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> SelectAudioObject(TEXT("SoundCue'/Game/Audio/Eth_Menu/Ethereal_MenuSelect_Cue.Ethereal_MenuSelect_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> SwitchAudioObject(TEXT("SoundCue'/Game/Audio/Eth_Menu/Ethereal_MenuSwitch_Cue.Ethereal_MenuSwitch_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> CursorAudioObject(TEXT("SoundCue'/Game/Audio/Eth_Menu/Ethereal_MenuCursor_Cue.Ethereal_MenuCursor_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> CancelAudioObject(TEXT("SoundCue'/Game/Audio/Eth_Menu/Ethereal_MenuCancel_Cue.Ethereal_MenuCancel_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> BindingAttachAudioObject(TEXT("SoundCue'/Game/Audio/Eth_Menu/Ethereal_Binding_Attach_Cue.Ethereal_Binding_Attach_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ErrorAudioObject(TEXT("SoundCue'/Game/Audio/Eth_Menu/Ethereal_MenuError_Cue.Ethereal_MenuError_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> NPCNotifyAudioObject(TEXT("SoundCue'/Game/Audio/Eth_Menu/Ethereal_NPCNotify_Cue.Ethereal_NPCNotify_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ShopBuyAudioObject(TEXT("SoundCue'/Game/Sounds/Interactive_Objects/ShopBuy_Cue.ShopBuy_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> InventoryPickupAudioObject(TEXT("SoundCue'/Game/Sounds/Interactive_Objects/GearDrop_Audio.GearDrop_Audio'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ArmorEquipAudioObject(TEXT("SoundCue'/Game/Sounds/Weapon_AssaultRifle/Mono/EquipArmor_Cue.EquipArmor_Cue'"));

	// Get Assets for Footstep Effects
	static ConstructorHelpers::FObjectFinder<USoundCue> DefaultFootstepAudioObject(TEXT("SoundCue'/Game/EtherealParty/OldWizard/Audio/Absolut_Footstep_Cue.Absolut_Footstep_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DustFootstepAudioObject(TEXT("SoundCue'/Game/Audio/Footsteps/footsteps_shoe_dirt_Light_Cue.footsteps_shoe_dirt_Light_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DirtFootstepAudioObject(TEXT("SoundCue'/Game/Audio/Footsteps/footsteps_shoe_dirt_Heavy_Cue.footsteps_shoe_dirt_Heavy_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> MudFootstepAudioObject(TEXT("SoundCue'/Game/Audio/Footsteps/Footstep_Mud_Cue.Footstep_Mud_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> GrassFootstepAudioObject(TEXT("SoundCue'/Game/Audio/Footsteps/footsteps_shoe_grass_Heavy_Cue.footsteps_shoe_grass_Heavy_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> LightGrassFootstepAudioObject(TEXT("SoundCue'/Game/Audio/Footsteps/footsteps_shoe_grass_Light_Cue.footsteps_shoe_grass_Light_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> SnowLightFootstepAudioObject(TEXT("SoundCue'/Game/Audio/Footsteps/footsteps_shoe_snow_Light_Cue.footsteps_shoe_snow_Light_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> SnowHeavyFootstepAudioObject(TEXT("SoundCue'/Game/Audio/Footsteps/footsteps_shoe_snow_Heavy_Cue.footsteps_shoe_snow_Heavy_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> EmbersFootstepAudioObject(TEXT("SoundCue'/Game/Audio/Footsteps/footsteps_shoe_metal_Heavy_Cue.footsteps_shoe_metal_Heavy_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> FireFootstepAudioObject(TEXT("SoundCue'/Game/EtherealParty/OldWizard/Audio/Absolut_Footstep_Cue.Absolut_Footstep_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> LeavesFootstepAudioObject(TEXT("SoundCue'/Game/EtherealParty/OldWizard/Audio/Absolut_Footstep_Cue.Absolut_Footstep_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> SparksFootstepAudioObject(TEXT("SoundCue'/Game/EtherealParty/OldWizard/Audio/Absolut_Footstep_Cue.Absolut_Footstep_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ShockFootstepAudioObject(TEXT("SoundCue'/Game/EtherealParty/OldWizard/Audio/Absolut_Footstep_Cue.Absolut_Footstep_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> WaterSmallFootstepAudioObject(TEXT("SoundCue'/Game/Audio/Footsteps/Footstep_Water_Cue.Footstep_Water_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> WaterLargeFootstepAudioObject(TEXT("SoundCue'/Game/Audio/Footsteps/Footstep_Water_Cue.Footstep_Water_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> LightFootstepAudioObject(TEXT("SoundCue'/Game/EtherealParty/OldWizard/Audio/Absolut_Footstep_Cue.Absolut_Footstep_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DarkFootstepAudioObject(TEXT("SoundCue'/Game/EtherealParty/OldWizard/Audio/Absolut_Footstep_Cue.Absolut_Footstep_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> RingFootstepAudioObject(TEXT("SoundCue'/Game/Audio/Footsteps/Footstep_Ring_Cue.Footstep_Ring_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> EnergyFootstepAudioObject(TEXT("SoundCue'/Game/EtherealParty/OldWizard/Audio/Absolut_Footstep_Cue.Absolut_Footstep_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ElectricFootstepAudioObject(TEXT("SoundCue'/Game/EtherealParty/OldWizard/Audio/Absolut_Footstep_Cue.Absolut_Footstep_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> StaticFootstepAudioObject(TEXT("SoundCue'/Game/EtherealParty/OldWizard/Audio/Absolut_Footstep_Cue.Absolut_Footstep_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> WoodLightFootstepAudioObject(TEXT("SoundCue'/Game/Audio/Footsteps/footsteps_shoe_wood_Light_Cue.footsteps_shoe_wood_Light_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> WoodHeavyFootstepAudioObject(TEXT("SoundCue'/Game/Audio/Footsteps/footsteps_shoe_wood_Heavy_Cue.footsteps_shoe_wood_Heavy_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> MetalLightFootstepAudioObject(TEXT("SoundCue'/Game/Audio/Footsteps/footsteps_shoe_metal_Light_Cue.footsteps_shoe_metal_Light_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> MetalHeavyFootstepAudioObject(TEXT("SoundCue'/Game/Audio/Footsteps/footsteps_shoe_metal_Heavy_Cue.footsteps_shoe_metal_Heavy_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ConcreteLightFootstepAudioObject(TEXT("SoundCue'/Game/Audio/Footsteps/footsteps_shoe_concrete_Light_Cue.footsteps_shoe_concrete_Light_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> ConcreteHeavyFootstepAudioObject(TEXT("SoundCue'/Game/Audio/Footsteps/footsteps_shoe_concrete_Heavy_Cue.footsteps_shoe_concrete_Heavy_Cue'"));

	// Store audio objects
	S_Battle_Standard = StandardAudioObject.Object;
	S_Battle_Boss = BossAudioObject.Object;
	S_Zhan_Intro = ZhanIntroAudioObject.Object;
	S_Eternal_Intro = EternalIntroAudioObject.Object;
	S_Zhan_Battle = ZhanBattleAudioObject.Object;
	S_Eternal_Battle = EternalBattleAudioObject.Object;
	S_BGM_MainMenu = MainMenuAudioObject.Object;
	S_BGM_Arcadia = ArcadiaAudioObject.Object;
	S_BGM_Shiitake = ShiitakeAudioObject.Object;
	S_BGM_Vulcan = VulcanAudioObject.Object;
	S_BGM_Boreal = BorealAudioObject.Object;
	S_BGM_Yggdrasil = YggdrasilAudioObject.Object;
	S_BGM_Empyrean = EmpyreanAudioObject.Object;
	S_BGM_Celestial = CelestialAudioObject.Object;
	S_BGM_Arena = ArenaAudioObject.Object;
	S_BGM_Credits = CreditsAudioObject.Object;
	S_SFX_LevelUp = LevelUpAudioObject.Object;
	S_SFX_GameOver = GameOverAudioObject.Object;
	//////////////////////////////////////////////
	// Menu effects
	S_SFX_StartGame = StartGameAudioObject.Object;
	S_SFX_Select = SelectAudioObject.Object;
	S_SFX_Switch = SwitchAudioObject.Object;
	S_SFX_Cursor = CursorAudioObject.Object;
	S_SFX_Cancel = CancelAudioObject.Object;
	S_SFX_BindingAttach = BindingAttachAudioObject.Object;
	S_SFX_Error = ErrorAudioObject.Object;
	S_NPC_Notify = NPCNotifyAudioObject.Object;
	S_SFX_ShopBuy = ShopBuyAudioObject.Object;
	S_SFX_InventoryPickup = InventoryPickupAudioObject.Object;
	S_SFX_ArmorEquip = ArmorEquipAudioObject.Object;
	//////////////////////////////////////////////
	// Footstep effects
	S_SFX_DefaultFootstep = DefaultFootstepAudioObject.Object;
	S_SFX_Dust = DustFootstepAudioObject.Object;
	S_SFX_Dirt = DirtFootstepAudioObject.Object;
	S_SFX_Mud = MudFootstepAudioObject.Object;
	S_SFX_Grass = GrassFootstepAudioObject.Object;
	S_SFX_LightGrass = LightGrassFootstepAudioObject.Object;
	S_SFX_SnowLight = SnowLightFootstepAudioObject.Object;
	S_SFX_SnowHeavy = SnowHeavyFootstepAudioObject.Object;
	S_SFX_Embers = EmbersFootstepAudioObject.Object;
	S_SFX_Fire = FireFootstepAudioObject.Object;
	S_SFX_Leaves = LeavesFootstepAudioObject.Object;
	S_SFX_Sparks = SparksFootstepAudioObject.Object;
	S_SFX_Shock = ShockFootstepAudioObject.Object;
	S_SFX_WaterSmall = WaterSmallFootstepAudioObject.Object;
	S_SFX_WaterLarge = WaterLargeFootstepAudioObject.Object;
	S_SFX_Light = LightFootstepAudioObject.Object;
	S_SFX_Dark = DarkFootstepAudioObject.Object;
	S_SFX_Ring = RingFootstepAudioObject.Object;
	S_SFX_Energy = EnergyFootstepAudioObject.Object;
	S_SFX_Electric = ElectricFootstepAudioObject.Object;
	S_SFX_Static = StaticFootstepAudioObject.Object;
	S_SFX_WoodLight = WoodLightFootstepAudioObject.Object;
	S_SFX_WoodHeavy = WoodHeavyFootstepAudioObject.Object;
	S_SFX_MetalLight = MetalLightFootstepAudioObject.Object;
	S_SFX_MetalHeavy = MetalHeavyFootstepAudioObject.Object;
	S_SFX_ConcreteLight = ConcreteLightFootstepAudioObject.Object;
	S_SFX_ConcreteHeavy = ConcreteHeavyFootstepAudioObject.Object;

	// Creates a scene component and sets it as the root
	Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = Root;

	// Construct the CurrentAudio component
	CurrentAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("CurrentAudio"));

	// Construct Other Audio components
	Battle_Standard = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("Battle_Standard"));
	Battle_Boss = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("Battle_Boss"));
	Zhan_Intro = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("Zhan_Intro"));
	Eternal_Intro = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("Eternal_Intro"));
	Zhan_Battle = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("Zhan_Battle"));
	Eternal_Battle = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("Eternal_Battle"));
	BGM_MainMenu = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BGM_MainMenu"));
	BGM_Arcadia = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BGM_Arcadia"));
	BGM_Shiitake = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BGM_Shiitake"));
	BGM_Vulcan = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BGM_Vulcan"));
	BGM_Boreal = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BGM_Boreal"));
	BGM_Yggdrasil = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BGM_Yggdrasil"));
	BGM_Empyrean = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BGM_Empyrean"));
	BGM_Celestial = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BGM_Celestial"));
	BGM_Arena = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BGM_Arena"));
	BGM_Credits = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("BGM_Credits"));
	SFX_LevelUp = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_LevelUp"));
	SFX_GameOver = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_GameOver"));
	SFX_StartGame = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_StartGame"));
	SFX_Select = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Select"));
	SFX_Switch = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Switch"));
	SFX_Cursor = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Cursor"));
	SFX_Cancel = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Cancel"));
	SFX_BindingAttach = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_BindingAttach"));
	SFX_Error = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Error"));
	NPC_Notify = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("NPC_Notify"));
	SFX_ShopBuy = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_ShopBuy"));
	SFX_InventoryPickup = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_InventoryPickup"));
	SFX_ArmorEquip = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_ArmorEquip"));
	//////////////////////////
	// Footstep audio components
	SFX_DefaultFootstep = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_DefaultFootstep"));
	SFX_Dust = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Dust"));
	SFX_Dirt = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Dirt"));
	SFX_Mud = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Mud"));
	SFX_Grass = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Grass"));
	SFX_LightGrass = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_LightGrass"));
	SFX_SnowLight = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_SnowLight"));
	SFX_SnowHeavy = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_SnowHeavy"));
	SFX_Embers = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Embers"));
	SFX_Fire = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Fire"));
	SFX_Leaves = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Leaves"));
	SFX_Sparks = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Sparks"));
	SFX_Shock = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Shock"));
	SFX_WaterSmall = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_WaterSmall"));
	SFX_WaterLarge = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_WaterLarge"));
	SFX_Light = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Light"));
	SFX_Dark = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Dark"));
	SFX_Ring = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Ring"));
	SFX_Energy = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Energy"));
	SFX_Electric = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Electric"));
	SFX_Static = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_Static"));
	SFX_WoodLight = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_WoodLight"));
	SFX_WoodHeavy = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_WoodHeavy"));
	SFX_MetalLight = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_MetalLight"));
	SFX_MetalHeavy = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_MetalHeavy"));
	SFX_ConcreteLight = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_ConcreteLight"));
	SFX_ConcreteHeavy = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("SFX_ConcreteHeavy"));

	// Set Audio Objects to use their sound assets
	Battle_Standard->Sound = S_Battle_Standard;
	Battle_Boss->Sound = S_Battle_Boss;
	Zhan_Intro->Sound = S_Zhan_Intro;
	Eternal_Intro->Sound = S_Eternal_Intro;
	Zhan_Battle->Sound = S_Zhan_Battle;
	Eternal_Battle->Sound = S_Eternal_Battle;
	BGM_MainMenu->Sound = S_BGM_MainMenu;
	BGM_Arcadia->Sound = S_BGM_Arcadia;
	BGM_Shiitake->Sound = S_BGM_Shiitake;
	BGM_Vulcan->Sound = S_BGM_Vulcan;
	BGM_Boreal->Sound = S_BGM_Boreal;
	BGM_Yggdrasil->Sound = S_BGM_Yggdrasil;
	BGM_Empyrean->Sound = S_BGM_Empyrean;
	BGM_Celestial->Sound = S_BGM_Celestial;
	BGM_Arena->Sound = S_BGM_Arena;
	BGM_Credits->Sound = S_BGM_Credits;
	SFX_LevelUp->Sound = S_SFX_LevelUp;
	SFX_GameOver->Sound = S_SFX_GameOver;
	SFX_StartGame->Sound = S_SFX_StartGame;
	SFX_Select ->Sound = S_SFX_Select;
	SFX_Switch->Sound = S_SFX_Switch;
	SFX_Cursor->Sound = S_SFX_Cursor;
	SFX_Cancel->Sound = S_SFX_Cancel;
	SFX_BindingAttach->Sound = S_SFX_BindingAttach;
	SFX_Error->Sound = S_SFX_Error;
	NPC_Notify->Sound = S_NPC_Notify;
	SFX_ShopBuy->Sound = S_SFX_ShopBuy;
	SFX_InventoryPickup->Sound = S_SFX_InventoryPickup;
	SFX_ArmorEquip->Sound = S_SFX_ArmorEquip;
	//////////////////////////////////////////////////////
	// Footstep effects
	SFX_DefaultFootstep->Sound = S_SFX_DefaultFootstep;
	SFX_Dust->Sound = S_SFX_Dust;
	SFX_Dirt->Sound = S_SFX_Dirt;
	SFX_Mud->Sound = S_SFX_Mud;
	SFX_Grass->Sound = S_SFX_Grass;
	SFX_LightGrass->Sound = S_SFX_LightGrass;
	SFX_SnowLight->Sound = S_SFX_SnowLight;
	SFX_SnowHeavy->Sound = S_SFX_SnowHeavy;
	SFX_Embers->Sound = S_SFX_Embers;
	SFX_Fire->Sound = S_SFX_Fire;
	SFX_Leaves->Sound = S_SFX_Leaves;
	SFX_Sparks->Sound = S_SFX_Sparks;
	SFX_Shock->Sound = S_SFX_Shock;
	SFX_WaterSmall->Sound = S_SFX_WaterSmall;
	SFX_WaterLarge->Sound = S_SFX_WaterLarge;
	SFX_Light->Sound = S_SFX_Light;
	SFX_Dark->Sound = S_SFX_Dark;
	SFX_Ring->Sound = S_SFX_Ring;
	SFX_Energy->Sound = S_SFX_Energy;
	SFX_Electric->Sound = S_SFX_Electric;
	SFX_Static->Sound = S_SFX_Static;
	SFX_WoodLight->Sound = S_SFX_WoodLight;
	SFX_WoodHeavy->Sound = S_SFX_WoodHeavy;
	SFX_MetalLight->Sound = S_SFX_MetalLight;
	SFX_MetalHeavy->Sound = S_SFX_MetalHeavy;
	SFX_ConcreteLight->Sound = S_SFX_ConcreteLight;
	SFX_ConcreteHeavy->Sound = S_SFX_ConcreteHeavy;


	// Deactivate all audio on construction
	CurrentAudio->bAutoActivate = false;
	Battle_Standard->bAutoActivate = false;
	Battle_Boss->bAutoActivate = false;
	Zhan_Intro->bAutoActivate = false;
	Eternal_Intro->bAutoActivate = false;
	Zhan_Battle->bAutoActivate = false;
	Eternal_Battle->bAutoActivate = false;
	BGM_MainMenu->bAutoActivate = false;
	BGM_Arcadia->bAutoActivate = false;
	BGM_Shiitake->bAutoActivate = false;
	BGM_Vulcan->bAutoActivate = false;
	BGM_Boreal->bAutoActivate = false;
	BGM_Yggdrasil->bAutoActivate = false;
	BGM_Empyrean->bAutoActivate = false;
	BGM_Celestial->bAutoActivate = false;
	BGM_Arena->bAutoActivate = false;
	BGM_Credits->bAutoActivate = false;
	SFX_LevelUp->bAutoActivate = false;
	SFX_GameOver->bAutoActivate = false;
	SFX_StartGame->bAutoActivate = false;
	SFX_Select ->bAutoActivate = false;
	SFX_Switch->bAutoActivate = false;
	SFX_Cursor->bAutoActivate = false;
	SFX_Cancel->bAutoActivate = false;
	SFX_BindingAttach->bAutoActivate = false;
	SFX_Error->bAutoActivate = false;
	NPC_Notify->bAutoActivate = false;
	SFX_ShopBuy->bAutoActivate = false;
	SFX_InventoryPickup->bAutoActivate = false;
	SFX_ArmorEquip->bAutoActivate = false;

	SFX_DefaultFootstep->bAutoActivate = false;
	SFX_Dust->bAutoActivate = false;
	SFX_Dirt->bAutoActivate = false;
	SFX_Mud->bAutoActivate = false;
	SFX_Grass->bAutoActivate = false;
	SFX_LightGrass->bAutoActivate = false;
	SFX_SnowLight->bAutoActivate = false;
	SFX_SnowHeavy->bAutoActivate = false;
	SFX_Embers->bAutoActivate = false;
	SFX_Fire->bAutoActivate = false;
	SFX_Leaves->bAutoActivate = false;
	SFX_Sparks->bAutoActivate = false;
	SFX_Shock->bAutoActivate = false;
	SFX_WaterSmall->bAutoActivate = false;
	SFX_WaterLarge->bAutoActivate = false;
	SFX_Light->bAutoActivate = false;
	SFX_Dark->bAutoActivate = false;
	SFX_Ring->bAutoActivate = false;
	SFX_Energy->bAutoActivate = false;
	SFX_Electric->bAutoActivate = false;
	SFX_Static->bAutoActivate = false;
	SFX_WoodLight->bAutoActivate = false;
	SFX_WoodHeavy->bAutoActivate = false;
	SFX_MetalLight->bAutoActivate = false;
	SFX_MetalHeavy->bAutoActivate = false;
	SFX_ConcreteLight->bAutoActivate = false;
	SFX_ConcreteHeavy->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AEtherealAudioManager::BeginPlay()
{
	Super::BeginPlay();

	// Get a GameInstance reference and set volume controls for all audio components
	UEtherealGameInstance* GameInstance = Cast<UEtherealGameInstance>(GetGameInstance());
	
	if (GameInstance)
	{
		GameInstance->SetAudioVolume(BGM_MainMenu, EAudioTypes::AT_Music);
		GameInstance->SetAudioVolume(BGM_Arcadia, EAudioTypes::AT_Music);
		GameInstance->SetAudioVolume(BGM_Shiitake, EAudioTypes::AT_Music);
		GameInstance->SetAudioVolume(BGM_Vulcan, EAudioTypes::AT_Music);
		GameInstance->SetAudioVolume(BGM_Boreal, EAudioTypes::AT_Music);
		GameInstance->SetAudioVolume(BGM_Yggdrasil, EAudioTypes::AT_Music);
		GameInstance->SetAudioVolume(BGM_Empyrean, EAudioTypes::AT_Music);
		GameInstance->SetAudioVolume(BGM_Celestial, EAudioTypes::AT_Music);
		GameInstance->SetAudioVolume(BGM_Arena, EAudioTypes::AT_Music);
		GameInstance->SetAudioVolume(BGM_Credits, EAudioTypes::AT_Music);

		GameInstance->SetAudioVolume(Battle_Standard, EAudioTypes::AT_Music);
		GameInstance->SetAudioVolume(Battle_Boss, EAudioTypes::AT_Music);
		GameInstance->SetAudioVolume(Zhan_Intro, EAudioTypes::AT_Music);
		GameInstance->SetAudioVolume(Eternal_Intro, EAudioTypes::AT_Music);
		GameInstance->SetAudioVolume(Zhan_Battle, EAudioTypes::AT_Music);
		GameInstance->SetAudioVolume(Eternal_Battle, EAudioTypes::AT_Music);

		GameInstance->SetAudioVolume(SFX_LevelUp, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_GameOver, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_StartGame, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Select, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Switch, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Cursor, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Cancel, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_BindingAttach, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Error, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(NPC_Notify, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_ShopBuy, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_InventoryPickup, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_ArmorEquip, EAudioTypes::AT_SoundEffect);

		GameInstance->SetAudioVolume(SFX_DefaultFootstep, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Dust, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Dirt, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Mud, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Grass, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_LightGrass, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_SnowLight, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_SnowHeavy, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Embers, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Fire, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Leaves, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Sparks, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Shock, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_WaterSmall, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_WaterLarge, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Light, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Dark, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Energy, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Electric, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_Static, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_WoodLight, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_WoodHeavy, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_MetalLight, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_MetalHeavy, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_ConcreteLight, EAudioTypes::AT_SoundEffect);
		GameInstance->SetAudioVolume(SFX_ConcreteHeavy, EAudioTypes::AT_SoundEffect);

	}
}

// BATTLE MUSIC FUNCTIONS

// Play the Battle Music, based on the selection type.
void AEtherealAudioManager::Play_BattleMusic(EBattleTypes Selection)
{
	switch (Selection)
	{
	case EBattleTypes::BT_Standard:
		if (CurrentAudio != BGM_Arena)
		{
			Play_Battle_Standard();
		}		
		break;
	case EBattleTypes::BT_Boss:
		if (CurrentAudio != BGM_Arena)
		{
			Play_Battle_Boss();
		}		
		break;
	case EBattleTypes::BT_ZhanIntro:
		Play_Zhan_Intro();
		break;
	case EBattleTypes::BT_ZhanBattle:
		Play_Zhan_Battle();
		break;
	}
}

// Play Standard Battle Music
void AEtherealAudioManager::Play_Battle_Standard()
{
	if (Battle_Standard->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio			
		}
		Battle_Standard->FadeIn(0.5f, 1);  // fade in the battle music
		CurrentAudio = Battle_Standard;  // Set the current audio to be the Standard Battle Music
	}
}

// Play Boss Battle Music
void AEtherealAudioManager::Play_Battle_Boss()
{
	if (Battle_Boss->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		Battle_Boss->FadeIn(0.5f, 1);  // fade in the battle music
		CurrentAudio = Battle_Boss;  // Set the current audio to be the Standard Battle Music
	}
}

// Play Zhan Intro Music
void AEtherealAudioManager::Play_Zhan_Intro()
{
	if (Zhan_Intro->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}

		Zhan_Intro->FadeIn(0.5f, 1);  // fade in the music
		CurrentAudio = Zhan_Intro;  // Set the current audio to be this Music		
	}
}

// Play Eternal Intro Music
void AEtherealAudioManager::Play_Eternal_Intro()
{
	if (Eternal_Intro->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}

		Eternal_Intro->FadeIn(0.5f, 1);  // fade in the music
		CurrentAudio = Eternal_Intro;  // Set the current audio to be this Music		
	}
}

// Play Zhan Battle Music
void AEtherealAudioManager::Play_Zhan_Battle()
{
	if (Zhan_Battle->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		Zhan_Battle->FadeIn(0.5f, 1);  // fade in the music
		CurrentAudio = Zhan_Battle;  // Set the current audio to be this Music
	}
}

// Play Zhan Battle Music
void AEtherealAudioManager::Play_Eternal_Battle()
{
	if (Eternal_Battle->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		Eternal_Battle->FadeIn(0.5f, 1);  // fade in the music
		CurrentAudio = Eternal_Battle;  // Set the current audio to be this Music
	}
}

// LEVEL BACKGROUND MUSIC FUNCTIONS

// Play Background Music, based on Level
void AEtherealAudioManager::Play_BGM(ERealms Level)
{
	switch (Level)
	{
	case ERealms::R_MainMenu:
		Play_BGM_MainMenu();
		break;
	case ERealms::R_Loading:
		Play_BGM_MainMenu();
		break;
	case ERealms::R_Arcadia:
		Play_BGM_Arcadia();
		break;
	case ERealms::R_Shiitake:
		Play_BGM_Shiitake();
		break;
	case ERealms::R_Vulcan:
		Play_BGM_Vulcan();
		break;
	case ERealms::R_Boreal:
		Play_BGM_Boreal();
		break;
	case ERealms::R_Yggdrasil:
		Play_BGM_Yggdrasil();
		break;
	case ERealms::R_Empyrean:
		Play_BGM_Empyrean();
		break;
	case ERealms::R_Celestial:
		Play_BGM_Celestial();
		break;
	case ERealms::R_Arena:
		Play_BGM_Arena();
		break;
	}
}

// Play Main Menu Background Music
void AEtherealAudioManager::Play_BGM_MainMenu()
{
	if (BGM_MainMenu->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		BGM_MainMenu->FadeIn(0.5f, 1);  // fade in the music
		CurrentAudio = BGM_MainMenu;  // Set the current audio to be this Music
	}
}

// Play Arcadia Background Music
void AEtherealAudioManager::Play_BGM_Arcadia()
{
	if (BGM_Arcadia->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		BGM_Arcadia->FadeIn(0.5f, 1);  // fade in the music
		CurrentAudio = BGM_Arcadia;  // Set the current audio to be this Music
	}
}

// Play Shiitake Temple Background Music
void AEtherealAudioManager::Play_BGM_Shiitake()
{
	if (BGM_Shiitake->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		BGM_Shiitake->FadeIn(0.5f, 1);  // fade in the music
		CurrentAudio = BGM_Shiitake;  // Set the current audio to be this Music
	}
}

// Play Vulcan Shrine Background Music
void AEtherealAudioManager::Play_BGM_Vulcan()
{
	if (BGM_Vulcan->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		BGM_Vulcan->FadeIn(0.5f, 1);  // fade in the music
		CurrentAudio = BGM_Vulcan;  // Set the current audio to be this Music
	}
}

// Play Boreal Core Background Music
void AEtherealAudioManager::Play_BGM_Boreal()
{
	if (BGM_Boreal->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		BGM_Boreal->FadeIn(0.5f, 1);  // fade in the music
		CurrentAudio = BGM_Boreal;  // Set the current audio to be this Music
	}
}

// Play Yggdrasil Background Music
void AEtherealAudioManager::Play_BGM_Yggdrasil()
{
	if (BGM_Yggdrasil->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		BGM_Yggdrasil->FadeIn(0.5f, 1);  // fade in the music
		CurrentAudio = BGM_Yggdrasil;  // Set the current audio to be this Music
	}
}

// Play Empyrean Gardens Background Music
void AEtherealAudioManager::Play_BGM_Empyrean()
{
	if (BGM_Empyrean->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		BGM_Empyrean->FadeIn(0.5f, 1);  // fade in the music
		CurrentAudio = BGM_Empyrean;  // Set the current audio to be this Music
	}
}

// Play Celestial Nexus Background Music
void AEtherealAudioManager::Play_BGM_Celestial()
{
	if (BGM_Celestial->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		BGM_Celestial->FadeIn(0.5f, 1);  // fade in the music
		CurrentAudio = BGM_Celestial;  // Set the current audio to be this Music
	}
}

// Play Arena Background Music
void AEtherealAudioManager::Play_BGM_Arena()
{
	if (BGM_Arena->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		BGM_Arena->FadeIn(0.5f, 1);  // fade in the music
		CurrentAudio = BGM_Arena;  // Set the current audio to be this Music
	}
}

// Play Credits Background Music
void AEtherealAudioManager::Play_BGM_Credits()
{
	if (BGM_Credits->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(1.0f, 0);  // Fade out the current audio
		}
		BGM_Credits->FadeIn(0.5f, 1);  // fade in the music
		CurrentAudio = BGM_Credits;  // Set the current audio to be this Music
	}
}

// SOUND EFFECTS FUNCTIONS

// Play Level Up Sound Effect
void AEtherealAudioManager::Play_SFX_LevelUp()
{
	SFX_LevelUp->Play();  // Play the Music
}

void AEtherealAudioManager::Play_SFX_GameOver()
{
	if (SFX_GameOver->IsPlaying())
	{
		return;  // If Music is already playing, do nothing.
	}
	else
	{
		if (CurrentAudio)
		{
			CurrentAudio->FadeOut(0.25f, 0);  // Fade out the current audio
		}
		//SFX_GameOver->FadeIn(0.5f, 1);  // fade in the music
		SFX_GameOver->Play();  // Play the Music
		CurrentAudio = SFX_GameOver;  // Set the current audio to be this Music
	}
}

// Play Start Game Menu SFX
void AEtherealAudioManager::Play_SFX_StartGame()
{
	SFX_StartGame->Play();
}

// Play Select Menu SFX
void AEtherealAudioManager::Play_SFX_Select()
{
	SFX_Select->Play();
}

// Play Switch Menu SFX
void AEtherealAudioManager::Play_SFX_Switch()
{
	SFX_Switch->Play();
}

// Play Cursor Menu SFX
void AEtherealAudioManager::Play_SFX_Cursor()
{
	SFX_Cursor->Play();
}

// Play Cancel Menu SFX
void AEtherealAudioManager::Play_SFX_Cancel()
{
	SFX_Cancel->Play();
}

// Play Binding Attach Menu SFX
void AEtherealAudioManager::Play_SFX_BindingAttach()
{
	SFX_BindingAttach->Play();
}

// Play Error Menu SFX
void AEtherealAudioManager::Play_SFX_Error()
{
	SFX_Error->Play();
}

// Play NPC Notify SFX
void AEtherealAudioManager::Play_NPC_Notify()
{
	NPC_Notify->Play();
}

// Play Targeting Notify SFX
void AEtherealAudioManager::Play_Target_Notify()
{
	SFX_Cursor->Play(); // plays the menu UI cursor audio
}

// Play ShopBuy Menu SFX
void AEtherealAudioManager::Play_SFX_ShopBuy()
{
	SFX_ShopBuy->Play();
}

// Play InventoryPickup SFX
void AEtherealAudioManager::Play_SFX_InventoryPickup()
{
	SFX_InventoryPickup->Play();
}

// Play Armor Equip SFX
void AEtherealAudioManager::Play_SFX_ArmorEquip()
{
	SFX_ArmorEquip->Play();
}
