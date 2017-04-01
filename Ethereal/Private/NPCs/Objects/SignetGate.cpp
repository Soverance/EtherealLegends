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
#include "Management/GameStates.h"
#include "Characters/Player/EtherealPlayerMaster.h"
#include "Gear/EtherealGearMaster.h"
#include "Widgets/SignetSystem.h"
#include "SignetGate.h"

#define LOCTEXT_NAMESPACE "EtherealText"

ASignetGate::ASignetGate(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> Widget(TEXT("/Game/Blueprints/Widgets/BP_SignetSystem"));

	// Set Default Objects
	W_InteractWidget = Widget.Class;

	InteractBox->SetBoxExtent(FVector(30, 30, 30));  // scale up the interact box

	// Create objects
	IsUsable = true;
	GateIsOpen = false;
	InteractAnimType = EInteractAnims::IA_Talk;

	DoInteract.AddDynamic(this, &ASignetGate::Interact); // bind interact

	MapMarkerFX->SetColorParameter(FName(TEXT("BeamColor")), FColor::Purple);
}

// Called when the game starts or when spawned
void ASignetGate::BeginPlay()
{
	Super::BeginPlay();

	// This usually wouldn't be necessary, since we collect this reference when the player enters the NPC's collider.
	// However, we require the reference to draw debug lines for the map, and the player may access the map before having interacting with this actor
	for (TActorIterator<AEtherealPlayerMaster> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		InteractingPlayer = *ActorItr; // get the instance of the Player
	}
}

// Called every frame
void ASignetGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Interact with this NPC
void ASignetGate::Interact()
{
	IsUsable = false;

	if (!GateIsOpen)
	{
		if (!InteractWidget) // only run this code if the widget does not exist
		{
			InteractWidget = CreateWidget<UUserWidget>(GetWorld(), W_InteractWidget);  // creates the widget

			USignetSystem* SignetSystem = Cast<USignetSystem>(InteractWidget);

			if (SignetSystem)
			{
				// Check if the player has the appropriate Signet Ring
				AEtherealGearMaster* SignetRing = InteractingPlayer->EtherealPlayerState->GetInventoryItem(SignetRingType);

				// If so...
				if (SignetRing)
				{
					ShowPanel(1);  // Show USER PROMPT
				}
				else
				{
					ShowPanel(0);  // Show ERROR
				}
			}
		}
		if (InteractWidget)  // run this code if the widget already exists (player has previously interacted with this instance)
		{
			bool InViewport = InteractWidget->IsInViewport();

			if (!InViewport)
			{
				USignetSystem* SignetSystem = Cast<USignetSystem>(InteractWidget);

				if (SignetSystem)
				{
					// Check if the player has the appropriate Signet Ring
					AEtherealGearMaster* SignetRing = InteractingPlayer->EtherealPlayerState->GetInventoryItem(SignetRingType);

					// If so...
					if (SignetRing)
					{
						ShowPanel(1);  // Show USER PROMPT
					}
					else
					{
						ShowPanel(0);  // Show ERROR
					}
				}
			}
		}
	}
	// IF GATE IS OPEN, then the player has already used a ring to unlock the gate during the currently loaded instance
	// Since they've already used a ring, just open the gate.
	if (GateIsOpen)
	{
		DropGate();  // call the BP event to animate the gate dropping
		IsUsable = true;
	}
	
}

// Disabled the Interact Widget associated with this NPC
void ASignetGate::DisableInteractWidget()
{	
	IsUsable = true;
	InteractingPlayer->EtherealGameInstance->CurrentState = EGameStates::GS_Playing;

	if (InteractWidget)
	{
		InteractWidget->RemoveFromViewport();
	}
}

// Show the specified widget panel
void ASignetGate::ShowPanel(int32 PanelIndex)
{
	USignetSystem* SignetSystem = Cast<USignetSystem>(InteractWidget);

	if (SignetSystem)
	{
		SignetSystem->OwningGate = this;  // set a reference to this gate, so that the Signet System widget can call functions on it.
		SignetSystem->SignetName = SignetRingName;  // Set the Signet Ring Name in the widget for easy and instanced access
		SignetSystem->AddToViewport();  // add the Signet System widget to the viewport
		InteractingPlayer->EtherealGameInstance->CurrentState = EGameStates::GS_Menu;  // put the player into the Menu state
		InteractingPlayer->StopActions();  // stop all actions when showing a signet panel

		switch (PanelIndex)
		{
		case 0:  // ERROR
			SignetSystem->ShowErrorPanel();
			break;
		case 1:  // USER PROMPT
			SignetSystem->ShowUserPrompt();
			break;
		case 2:  // SUCCESSFUL USE
			SignetSystem->ShowSuccessPanel();
			break;
		}		
	}	
}

void ASignetGate::DropGate_Implementation()
{
}

// Opens the Gate
void ASignetGate::OpenGate()
{
	// Check if the player has the appropriate Signet Ring
	AEtherealGearMaster* SignetRing = InteractingPlayer->EtherealPlayerState->GetInventoryItem(SignetRingType);

	// If so...
	if (SignetRing)
	{
		SignetRing->Unbind();  // Call Unbind(), which will remove the ring if it is equipped
		InteractingPlayer->EtherealPlayerState->Inventory.Remove(SignetRing);  // remove the ring from inventory
		GateIsOpen = true; // set the gate to open
		InteractingPlayer->DoInteractAnim = true;  // do the interact anim again
		DropGate();  // call the BP event to animate the gate dropping

		// TO DO :  play an audio/visual effect to notify the player that the ring was used and is now broken

		// wait a bit before showing the success panel (delays the UI display, for impact).
		FTimerDelegate DelegatePanel;
		DelegatePanel.BindUFunction(this, FName("ShowPanel"), 2);
		FTimerHandle WidgetTimer;
		GetWorldTimerManager().SetTimer(WidgetTimer, DelegatePanel, 1.5f, false);
	}
}

#undef LOCTEXT_NAMESPACE