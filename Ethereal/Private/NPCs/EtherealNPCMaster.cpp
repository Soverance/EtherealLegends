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
#include "Characters/Player/EtherealPlayerMaster.h"
#include "EtherealNPCMaster.h"

// Sets default values
AEtherealNPCMaster::AEtherealNPCMaster(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> MapMarkerParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Mobile/ICE/P_MapMarker.P_MapMarker'"));
	
	P_MapMarkerFX = MapMarkerParticleObject.Object;

	Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	InteractBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("InteractBox"));

	RootComponent = Root;
	InteractBox->SetupAttachment(Root);

	// Map Marker Component
	MapMarkerFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("MapMarkerFX"));
	MapMarkerFX->SetupAttachment(RootComponent);
	MapMarkerFX->Template = P_MapMarkerFX;
	MapMarkerFX->bAutoActivate = false;
	MapMarkerFX->SetRelativeRotation(FRotator(90, 0, 0));

	InteractBox->OnComponentBeginOverlap.AddDynamic(this, &AEtherealNPCMaster::OnInteract);
	InteractBox->OnComponentEndOverlap.AddDynamic(this, &AEtherealNPCMaster::EndInteract);
}

// Called when the game starts or when spawned
void AEtherealNPCMaster::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AEtherealPlayerMaster> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		InteractingPlayer = *ActorItr; // get the instance of the Player Master

		if (InteractingPlayer)
		{
			// Bind the Map Marker functions
			InteractingPlayer->MapOpened.AddDynamic(this, &AEtherealNPCMaster::ShowMapMarker);
			InteractingPlayer->MapClosed.AddDynamic(this, &AEtherealNPCMaster::HideMapMarker);
		}
	}
}

// Activates the Map Marker effect
void AEtherealNPCMaster::ShowMapMarker()
{
	MapMarkerFX->Activate();
}

// Deactivates the Map Marker
void AEtherealNPCMaster::HideMapMarker()
{
	MapMarkerFX->Deactivate();
}

// Function called when the player enters the InteractBox
void AEtherealNPCMaster::OnInteract(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AEtherealPlayerMaster>(OtherActor))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, "Player has entered an NPC interaction zone.");
		InteractingPlayer = Cast<AEtherealPlayerMaster>(OtherActor);
		CheckIfUsable();
	}
}

// Function called when the player can no longer interact with this NPC
void AEtherealNPCMaster::EndInteract(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AEtherealPlayerMaster>(OtherActor))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, "Player has stopped interacting with a NPC.");
		StopInteraction();
	}
}

// Checks whether or not this NPC is usable
void AEtherealNPCMaster::CheckIfUsable()
{
	if (InteractingPlayer->AggroList.Num() == 0)
	{
		if (IsUsable == true)
		{
			InteractingPlayer->InteractAnimType = InteractAnimType;
			StartInteraction();
		}
	}
}

// Begin Interacting with this NPC
void AEtherealNPCMaster::StartInteraction()
{
	if (InteractingPlayer)
	{
		if (IsUsable)
		{
			InteractingPlayer->IsInteracting = true;
			InteractingPlayer->InteractTarget = this;
			InteractingPlayer->InteractAnimType = InteractAnimType;
			InteractingPlayer->Exclamation->SetVisibility(true);
			InteractingPlayer->AudioManager->Play_NPC_Notify();
		}
	}
}

// End Interacting with this NPC
void AEtherealNPCMaster::StopInteraction()
{
	if (InteractingPlayer)
	{
		//IsUsable = true;
		InteractingPlayer->IsInteracting = false;
		InteractingPlayer->Exclamation->SetVisibility(false);
		//InteractingPlayer->PlayerController->BattleHUD->SetVisibility(true);
		if (ActionWidget)
		{
			ActionWidget->RemoveFromParent();
		}
	}
}

// Interact with this NPC. This function can only be called by the player pressing the "A" button while inside the InteractBox
void AEtherealNPCMaster::Interact()
{
	DoInteract.Broadcast();
	InteractingPlayer->IsInteracting = false;
}
