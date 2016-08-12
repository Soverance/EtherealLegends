// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Ethereal.h"
#include "EtherealGameMode.h"

AEtherealGameMode::AEtherealGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set Default Classes

	//GameInstanceClass = AEtherealGameInstance::StaticClass();

	//ADefaultPawn = AEtherealGameMode::StaticClass();

	PlayerControllerClass = AEtherealPlayerController::StaticClass();

	PlayerStateClass = AEtherealPlayerState::StaticClass();

	GameStateClass = AEtherealGameState::StaticClass();

}

void AEtherealGameMode::PlayerLogin(AEtherealPlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	NewPlayer->ClientPostLogin();
}
