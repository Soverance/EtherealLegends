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

#pragma once

#include "Engine/GameInstance.h"
#include "Management/GameStates.h"
#include "Management/Realms.h"
#include "Management/BlackBox.h"
#include "Management/EtherealAudioManager.h"
#include "Management/EtherealEnemyManager.h"
#include "Management/EtherealTrueSKYManager.h"
#include "EtherealGameInstance.generated.h"

// Event Dispatchers
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFadeOutEndGame);

UCLASS()
class ETHEREAL_API UEtherealGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UEtherealGameInstance();

	// Event Dispatcher for FadeOutEndGame
	UPROPERTY(BlueprintAssignable, Category = Dispatchers)
	FFadeOutEndGame FadeOutEndGame;

	// The current state of the game
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	EGameStates CurrentState;

	// Wether or not this is a new game. Only becomes true if the game was loaded and no save file was found.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	bool IsNewGame;

	// The current gameplay Realm
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	ERealms CurrentRealm;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Action)
	void LoadNewRealm(ERealms RealmToLoad);

	// Black Box
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Managers)
	ABlackBox* BlackBox;

	// Audio Manager
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Managers)
	AEtherealAudioManager* AudioManager;

	// Enemy Manager
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Managers)
	AEtherealEnemyManager* EnemyManager;

	// TrueSKY Manager
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Managers)
	AEtherealTrueSKYManager* TrueSKYManager;

	// Loads the management actors and sets their references.
	UFUNCTION(BlueprintCallable, Category = Managers)
	void LoadManagement();

	// This is a hacky solution to set the audio volume in settings, since I didn't want to re-write the entire settings BP in code right now... LAZY!
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Action)
	void SetAudioVolume(UAudioComponent* AudioComponent, EAudioTypes AudioType);
};
