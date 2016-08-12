// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
//#include "EtherealGameInstance.h"
#include "EtherealPlayerController.h"
#include "EtherealPlayerState.h"
#include "EtherealGameState.h"
#include "EtherealGameMode.generated.h"

UCLASS()
class AEtherealGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AEtherealGameMode(const FObjectInitializer& ObjectInitializer);

	/** Called immediately after the game begins. */
	UFUNCTION(BlueprintCallable, Category = Default)
	void PlayerLogin(AEtherealPlayerController* NewPlayer);

	
};



