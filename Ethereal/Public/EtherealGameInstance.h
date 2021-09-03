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

#include "Engine/GameInstance.h"
#include "Management/CommonLibrary.h"
#include "Management/GameStates.h"
#include "Management/Realms.h"
#include "Management/BlackBox.h"
#include "Management/EtherealAudioManager.h"
#include "Management/EtherealEnemyManager.h"
//#include "Management/EtherealTrueSKYManager.h"  // THE TRUESKY PLUGIN HAS BEEN DEPRECATED FROM ETHEREAL LEGENDS AS OF VERSION 1.2.1
#include "EtherealGameInstance.generated.h"

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)

//static void ConsoleLoadEtherealRealm()
//{
//	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Do some bullshit here!");
//
//	//UEtherealGameInstance::LoadNewRealm(Realm)
//}
//
//FAutoConsoleCommand ConsoleLoadRealm(
//	TEXT("EtherealConsole.LoadEtherealRealm"),
//	TEXT("Load the specified Ethereal Realm."),
//	FConsoleCommandDelegate::CreateStatic(ConsoleLoadEtherealRealm)
//);
#endif

// Event Dispatchers
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLoadingCleanup);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFadeOutEndGame);

UCLASS()
class ETHEREAL_API UEtherealGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	//UEtherealGameInstance();
	UEtherealGameInstance(const FObjectInitializer& ObjectInitializer);

	// Event Dispatcher for LoadingCleanup
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Dispatchers)
	FLoadingCleanup LoadingCleanup;

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

	// this function configures some default values necessary for the game's operation in both single and multiplayer modes
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Action)
	void ConfigureSharedResources();

	// this function loads a new streaming realm
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Action)
	void LoadNewRealm(ERealms RealmToLoad);

	// this function updates the game state
	UFUNCTION(BlueprintCallable, Category = Action)
	bool ChangeState(EGameStates DesiredState);

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
	// THE TRUESKY PLUGIN HAS BEEN DEPRECATED FROM ETHEREAL LEGENDS AS OF VERSION 1.2.1
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Managers)
	//AEtherealTrueSKYManager* TrueSKYManager;

	// Loads the management actors and sets their references.
	UFUNCTION(BlueprintCallable, Category = Managers)
	void LoadManagement();

	// This is a hacky solution to set the audio volume in settings, since I didn't want to re-write the entire settings BP in code right now... LAZY!
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Action)
	void SetAudioVolume(UAudioComponent* AudioComponent, EAudioTypes AudioType);

	//////////////////////////////////////////////
	//
	// NETWORK SESSION CONFIGURATION
	//
	//////////////////////////////////////////////

	// Creates a network host session server
	//	@Param	UserID			User that started the request
	//	@Param	SessionName		Name of the Session
	//	@Param	bIsLAN			Whether or not this session is played on LAN networks
	//	@Param	bIsPresence		Allows the session to use friend list functionality : "my friend is currently playing this game"
	//	@Param	MaxNumPlayers	Maximum allowed players in this session	
	bool HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);

	// Delegate called when session created 
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;

	// Delegate called when session started 
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	// Handles to registered delegates for creating/starting a session
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	// Container for session settings
	TSharedPtr<class FOnlineSessionSettings> SessionSettings;

	//	Function fired when a session create request has completed
	//	@param SessionName		the name of the session this callback is for
	//	@param bWasSuccessful	true if the async action completed without error, false if there was an error	
	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	
	//	Function fired when a session start request has completed
	//	@param SessionName		the name of the session this callback is for
	//	@param bWasSuccessful	true if the async action completed without error, false if there was an error	
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable, Category = Network)
	void StartOnlineGame();

	//////////////////////////////////////////////
	//
	// SESSION SEARCH CONFIGURATION
	//
	//////////////////////////////////////////////

	//	Find an online session
	//	@param UserId		user that initiated the request
	//	@param bIsLAN		are we searching LAN matches
	//	@param bIsPresence	are we searching presence sessions	
	void FindSessions(TSharedPtr<const FUniqueNetId> UserId, bool bIsLAN, bool bIsPresence);

	// Delegate for searching for sessions
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;

	// Handle to registered delegate for searching a session
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;

	// Container for search results
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	// Delegate fired when a session search query has completed	
	// @param bWasSuccessful	true if the async action completed without error, false if there was an error
	void OnFindSessionsComplete(bool bWasSuccessful);

	UFUNCTION(BlueprintCallable, Category = Network)
	void FindOnlineGames();

	//////////////////////////////////////////////
	//
	// SESSION JOIN CONFIGURATION
	//
	//////////////////////////////////////////////

	//	Joins a session via a search result
	//	@param SessionName name of session
	//	@param SearchResult Session to join
	//	@return bool true if successful, false otherwise
	bool JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);

	// Delegate for joining a session 
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	// Handle to registered delegate for joining a session
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
	
	//	Delegate fired when a session join request has completed	
	//	@param SessionName the name of the session this callback is for
	//	@param bWasSuccessful true if the async action completed without error, false if there was an error	
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION(BlueprintCallable, Category = Network)
	void JoinOnlineGame();

	//////////////////////////////////////////////
	//
	// DESTROY SESSION CONFIGURATION
	//
	//////////////////////////////////////////////

	/** Delegate for destroying a session */
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;

	/** Handle to registered delegate for destroying a session */
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;
		
	//	Delegate fired when a destroying an online session has completed
	//	@param SessionName the name of the session this callback is for
	//	@param bWasSuccessful true if the async action completed without error, false if there was an error	
	virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable, Category = Network)
	void DestroySessionAndLeaveGame();
};
