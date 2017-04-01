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

#include "GameFramework/Actor.h"
#include "Management/BattleTypes.h"
#include "Management/AudioTypes.h"
#include "Management/Realms.h"
#include "EtherealAudioManager.generated.h"

UCLASS()
class ETHEREAL_API AEtherealAudioManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEtherealAudioManager(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The root component for this actor.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	USceneComponent* Root;

	// CurrentAudio, which is simply a container used for referencing the currently playing audio track. Used during transitions between tracks.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UAudioComponent* CurrentAudio;

	// BATTLE MUSIC  ---------------------------------

	// Play the Battle Music, based on type selection.
	UFUNCTION(BlueprintCallable, Category = BattleMusic)
	void Play_BattleMusic(EBattleTypes Selection);
	
	// Standard Battle Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BattleMusic)
	UAudioComponent* Battle_Standard;
	USoundCue* S_Battle_Standard;

	// Play Standard Battle Music
	UFUNCTION(BlueprintCallable, Category = BattleMusic)
	void Play_Battle_Standard();

	// Boss Battle Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BattleMusic)
	UAudioComponent* Battle_Boss;
	USoundCue* S_Battle_Boss;

	// Play Boss Battle Music
	UFUNCTION(BlueprintCallable, Category = BattleMusic)
	void Play_Battle_Boss();

	// Signet Battle Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BattleMusic)
	UAudioComponent* Battle_Signet;
	USoundCue* S_Battle_Signet;

	// Play Signet Battle Music
	UFUNCTION(BlueprintCallable, Category = BattleMusic)
	void Play_Battle_Signet();

	// Zhan Intro Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BattleMusic)
	UAudioComponent* Zhan_Intro;
	USoundCue* S_Zhan_Intro;	

	// Play Zhan Intro Music
	UFUNCTION(BlueprintCallable, Category = BattleMusic)
	void Play_Zhan_Intro();

	// Eternal Intro Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BattleMusic)
	UAudioComponent* Eternal_Intro;
	USoundCue* S_Eternal_Intro;

	// Play Eternal Intro Music
	UFUNCTION(BlueprintCallable, Category = BattleMusic)
	void Play_Eternal_Intro();

	// Zhan Battle Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BattleMusic)
	UAudioComponent* Zhan_Battle;
	USoundCue* S_Zhan_Battle;

	// Play Zhan Battle Music
	UFUNCTION(BlueprintCallable, Category = BattleMusic)
	void Play_Zhan_Battle();

	// Eternal Battle Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BattleMusic)
	UAudioComponent* Eternal_Battle;
	USoundCue* S_Eternal_Battle;

	// Play Eternal Battle Music
	UFUNCTION(BlueprintCallable, Category = BattleMusic)
	void Play_Eternal_Battle();

	// BACKGROUND MUSIC  -------------------------------------

	// Play Background Music
	UFUNCTION(BlueprintCallable, Category = BackgroundMusic)
	void Play_BGM(ERealms Level);

	// Main Menu Background Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BackgroundMusic)
	UAudioComponent* BGM_MainMenu;
	USoundCue* S_BGM_MainMenu;

	// Play Main Menu Background Music
	UFUNCTION(BlueprintCallable, Category = BackgroundMusic)
	void Play_BGM_MainMenu();

	// Arcadia Background Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BackgroundMusic)
	UAudioComponent* BGM_Arcadia;
	USoundCue* S_BGM_Arcadia;

	// Play Shiitake Temple Background Music
	UFUNCTION(BlueprintCallable, Category = BackgroundMusic)
	void Play_BGM_Arcadia();

	// Shiitake Temple Background Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BackgroundMusic)
	UAudioComponent* BGM_Shiitake;
	USoundCue* S_BGM_Shiitake;

	// Play Shiitake Temple Background Music
	UFUNCTION(BlueprintCallable, Category = BackgroundMusic)
	void Play_BGM_Shiitake();

	// Vulcan Shrine Background Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BackgroundMusic)
	UAudioComponent* BGM_Vulcan;
	USoundCue* S_BGM_Vulcan;

	// Play Vulcan Shrine Background Music
	UFUNCTION(BlueprintCallable, Category = BackgroundMusic)
	void Play_BGM_Vulcan();

	// Boreal Core Background Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BackgroundMusic)
	UAudioComponent* BGM_Boreal;
	USoundCue* S_BGM_Boreal;

	// Play Boreal Core Background Music
	UFUNCTION(BlueprintCallable, Category = BackgroundMusic)
	void Play_BGM_Boreal();

	// Yggdrasil Background Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BackgroundMusic)
	UAudioComponent* BGM_Yggdrasil;
	USoundCue* S_BGM_Yggdrasil;

	// Play Yggdrasil Background Music
	UFUNCTION(BlueprintCallable, Category = BackgroundMusic)
	void Play_BGM_Yggdrasil();

	// Empyrean Gardens Background Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BackgroundMusic)
	UAudioComponent* BGM_Empyrean;
	USoundCue* S_BGM_Empyrean;

	// Play Empyrean Gardens Background Music
	UFUNCTION(BlueprintCallable, Category = BackgroundMusic)
	void Play_BGM_Empyrean();

	// Celestial Nexus Background Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BackgroundMusic)
	UAudioComponent* BGM_Celestial;
	USoundCue* S_BGM_Celestial;

	// Play Celestial Nexus Background Music
	UFUNCTION(BlueprintCallable, Category = BackgroundMusic)
	void Play_BGM_Celestial();

	// Arena Background Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BackgroundMusic)
	UAudioComponent* BGM_Arena;
	USoundCue* S_BGM_Arena;

	// Play Arena Background Music
	UFUNCTION(BlueprintCallable, Category = BackgroundMusic)
	void Play_BGM_Arena();

	// Credits Background Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BackgroundMusic)
	UAudioComponent* BGM_Credits;
	USoundCue* S_BGM_Credits;

	// Play Credits Background Music
	UFUNCTION(BlueprintCallable, Category = BackgroundMusic)
	void Play_BGM_Credits();

	//////////////////////////////////////////////////////
	// SOUND EFFECTS  -----------------------------------------

	// Level Up Fanfare Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundEffects)
	UAudioComponent* SFX_LevelUp;
	USoundCue* S_SFX_LevelUp;	

	// Play Level Up Sound Effect. 
	UFUNCTION(BlueprintCallable, Category = SoundEffects)
	void Play_SFX_LevelUp();

	// InventoryPickup SFX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundEffects)
	UAudioComponent* SFX_InventoryPickup;
	USoundCue* S_SFX_InventoryPickup;

	// Play InventoryPickup SFX - only played if the item name gets displayed on screen!
	UFUNCTION(BlueprintCallable, Category = SoundEffects)
	void Play_SFX_InventoryPickup();

	// Game Over Notify Music
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundEffects)
	UAudioComponent* SFX_GameOver;
	USoundCue* S_SFX_GameOver;

	// Game Over music
	UFUNCTION(BlueprintCallable, Category = SoundEffects)
	void Play_SFX_GameOver();

	/////////////////////////////////////////////////////
	// MENU SOUND EFFECTS

	// Menu Start Game SFX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundEffects)
	UAudioComponent* SFX_StartGame;
	USoundCue* S_SFX_StartGame;

	// Play Start Game SFX
	UFUNCTION(BlueprintCallable, Category = SoundEffects)
	void Play_SFX_StartGame();

	// Menu Select SFX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundEffects)
	UAudioComponent* SFX_Select;
	USoundCue* S_SFX_Select;

	// Play Select SFX
	UFUNCTION(BlueprintCallable, Category = SoundEffects)
	void Play_SFX_Select();

	// Menu Switch SFX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundEffects)
	UAudioComponent* SFX_Switch;
	USoundCue* S_SFX_Switch;

	// Play Switch SFX
	UFUNCTION(BlueprintCallable, Category = SoundEffects)
	void Play_SFX_Switch();

	// Menu Cursor SFX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundEffects)
	UAudioComponent* SFX_Cursor;
	USoundCue* S_SFX_Cursor;

	// Play Cursor SFX
	UFUNCTION(BlueprintCallable, Category = SoundEffects)
	void Play_SFX_Cursor();

	// Menu Cancel SFX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundEffects)
	UAudioComponent* SFX_Cancel;
	USoundCue* S_SFX_Cancel;

	// Play Cancel SFX
	UFUNCTION(BlueprintCallable, Category = SoundEffects)
	void Play_SFX_Cancel();

	// Menu Binding Attach SFX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundEffects)
	UAudioComponent* SFX_BindingAttach;
	USoundCue* S_SFX_BindingAttach;

	// Play Binding Attach SFX
	UFUNCTION(BlueprintCallable, Category = SoundEffects)
	void Play_SFX_BindingAttach();

	// Menu Error SFX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundEffects)
	UAudioComponent* SFX_Error;
	USoundCue* S_SFX_Error;

	// Play Error SFX
	UFUNCTION(BlueprintCallable, Category = SoundEffects)
	void Play_SFX_Error();

	// NPC Notify SFX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundEffects)
	UAudioComponent* NPC_Notify;
	USoundCue* S_NPC_Notify;

	// Play NPC Notify SFX
	UFUNCTION(BlueprintCallable, Category = SoundEffects)
	void Play_NPC_Notify();

	// Play Targeting Notify SFX
	UFUNCTION(BlueprintCallable, Category = SoundEffects)
	void Play_Target_Notify();

	// Menu ShopBuy SFX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundEffects)
	UAudioComponent* SFX_ShopBuy;
	USoundCue* S_SFX_ShopBuy;

	// Play ShopBuy SFX
	UFUNCTION(BlueprintCallable, Category = SoundEffects)
	void Play_SFX_ShopBuy();
	
	// Armor Equip SFX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SoundEffects)
	UAudioComponent* SFX_ArmorEquip;
	USoundCue* S_SFX_ArmorEquip;

	// Play Armor Equip SFX
	UFUNCTION(BlueprintCallable, Category = SoundEffects)
	void Play_SFX_ArmorEquip();

	///////////////////////////////////////////
	// FOOTSTEP SOUND EFFECTS

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_DefaultFootstep;
	USoundCue* S_SFX_DefaultFootstep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_Dust;
	USoundCue* S_SFX_Dust;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_Dirt;
	USoundCue* S_SFX_Dirt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_Mud;
	USoundCue* S_SFX_Mud;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_Grass;
	USoundCue* S_SFX_Grass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_LightGrass;
	USoundCue* S_SFX_LightGrass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_SnowLight;
	USoundCue* S_SFX_SnowLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_SnowHeavy;
	USoundCue* S_SFX_SnowHeavy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_Embers;
	USoundCue* S_SFX_Embers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_Fire;
	USoundCue* S_SFX_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_Leaves;
	USoundCue* S_SFX_Leaves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_Sparks;
	USoundCue* S_SFX_Sparks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_Shock;
	USoundCue* S_SFX_Shock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_WaterSmall;
	USoundCue* S_SFX_WaterSmall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent*SFX_WaterLarge;
	USoundCue* S_SFX_WaterLarge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_Light;
	USoundCue* S_SFX_Light;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_Dark;
	USoundCue* S_SFX_Dark;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_Ring;
	USoundCue* S_SFX_Ring;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_Energy;
	USoundCue* S_SFX_Energy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_Electric;
	USoundCue* S_SFX_Electric;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_Static;
	USoundCue* S_SFX_Static;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_WoodLight;
	USoundCue* S_SFX_WoodLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_WoodHeavy;
	USoundCue* S_SFX_WoodHeavy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_MetalLight;
	USoundCue* S_SFX_MetalLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_MetalHeavy;
	USoundCue* S_SFX_MetalHeavy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_ConcreteLight;
	USoundCue* S_SFX_ConcreteLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FootstepSounds)
	UAudioComponent* SFX_ConcreteHeavy;
	USoundCue* S_SFX_ConcreteHeavy;
};
