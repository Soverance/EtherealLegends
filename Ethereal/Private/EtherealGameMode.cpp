// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Ethereal.h"
#include "EtherealGameMode.h"

AEtherealGameMode::AEtherealGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set Default Classes

	PlayerControllerClass = AEtherealPlayerController::StaticClass();

	PlayerStateClass = AEtherealPlayerState::StaticClass();

	GameStateClass = AEtherealGameState::StaticClass();

}

