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
#include "Gear/EtherealGearMaster.h"
#include "Widgets/Tutorial.h"
#include "Gatekeeper.h"

AGatekeeper::AGatekeeper(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> NPCMesh(TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/Mixamo/prodigy.prodigy'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/InfinityBladeWarriors/Character/Mixamo/AnimBP_Prodigy.AnimBP_Prodigy_C'"));
	static ConstructorHelpers::FClassFinder<UUserWidget> Widget(TEXT("/Game/Blueprints/Widgets/BP_Tutorial"));

	// Set Default Objects
	SM_Mesh = NPCMesh.Object;
	W_InteractWidget = Widget.Class;
	
	// Create objects
	Mesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetAnimInstanceClass(AnimBP.Object);
	Mesh->SkeletalMesh = SM_Mesh;
	Mesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	Mesh->bCastCapsuleIndirectShadow = true;

	CombatBox_Right = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CombatBox_Right"));
	CombatBox_Right->SetupAttachment(Root);
	CombatBox_Right->SetBoxExtent(FVector(1400, 50, 200));
	CombatBox_Right->SetRelativeLocation(FVector(1640, 1086, 0));
	CombatBox_Right->SetRelativeRotation(FRotator(0, -8, 0));

	CombatBox_Left = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CombatBox_Left"));
	CombatBox_Left->SetupAttachment(Root);
	CombatBox_Left->SetBoxExtent(FVector(1000, 50, 200));
	CombatBox_Left->SetRelativeLocation(FVector(-1172, 47, 0));
	CombatBox_Right->SetRelativeRotation(FRotator(0, 54, 0));

	CombatBox_Right->OnComponentBeginOverlap.AddDynamic(this, &AGatekeeper::EnterCombatTutorialZone);
	CombatBox_Right->OnComponentEndOverlap.AddDynamic(this, &AGatekeeper::ExitCombatTutorialZone);
	CombatBox_Left->OnComponentBeginOverlap.AddDynamic(this, &AGatekeeper::EnterCombatTutorialZone);
	CombatBox_Left->OnComponentEndOverlap.AddDynamic(this, &AGatekeeper::ExitCombatTutorialZone);

	IsUsable = true;
	InteractAnimType = EInteractAnims::IA_Talk;
	DoInteract.AddDynamic(this, &AGatekeeper::Interact);

	DoExplain = false;
	DoHuh = false;
	DoWarning = false;

	StartedTutorial = false;
	CompletedTutorial = false;

	MapMarkerFX->SetColorParameter(FName(TEXT("BeamColor")), FColor::Purple);
}

// Called when the game starts or when spawned
void AGatekeeper::BeginPlay()
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
void AGatekeeper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Interact with this NPC
void AGatekeeper::Interact()
{
	IsUsable = false;

	if (InteractingPlayer)
	{
		// IF the player HAS NOT started the tutorial
		if (!StartedTutorial)
		{
			// redundancy check, should always return false
			if (!InteractingPlayer->EtherealPlayerState->HasCompletedTutorial)
			{
				// Check to be sure an InteractWidget exists
				if (!InteractWidget)
				{
					SpawnTutorialWidget();  // Spawn tutorial widget				
				}

				StartedTutorial = true;  // Player has started the Tutorial
				DoWarning = true;  // animate
				ShowConversation();  // Show Conversation Widget
			}
		}
		// IF the player HAS started the tutorial
		if (StartedTutorial)
		{
			if (Tutorial)
			{
				DoHuh = true;  // animate

				// The tutorial index will only be 4 if you've defeated the Skeleton King
				if (Tutorial->TutorialIndex == 4)
				{
					CompletedTutorial = true;  // Complete the Tutorial
					ShowConversation();  // Show Conversation Widget
				}
			}
		}
	}
}

// Spawn Tutorial Widget
void AGatekeeper::SpawnTutorialWidget()
{
	InteractWidget = CreateWidget<UUserWidget>(GetWorld(), W_InteractWidget);  // creates the widget
	Tutorial = Cast<UTutorial>(InteractWidget);	
	Tutorial->Gatekeeper = this;  // sets the Gatekeeper reference inside the Tutorial widget for later use.
	Tutorial->AddToViewport();  // add the Tutorial widget to the viewport
	Tutorial->FirstContact();  // Initiate the tutorial
}

// Disabled the Interact Widget associated with this NPC
void AGatekeeper::ShowConversation()
{
	// Check if the player HAS NOT started the tutorial
	if (!StartedTutorial)
	{
		// Check if the player HAS NOT completed the tutorial
		if (!InteractingPlayer->EtherealPlayerState->HasCompletedTutorial)
		{
			// Check to be sure the Tutorial widget exists (it always should by this point)
			if (Tutorial)
			{
				// Check what TutorialIndex the player is on, since the player may pass through this zone at unknown times
				if (Tutorial->TutorialIndex == 0)
				{
					Tutorial->ShowConversation_00();  // show the Tutorial error message
				}
			}
		}		
	}
	// if the player HAS started the tutorial
	if (StartedTutorial)
	{
		// Check to be sure the Tutorial widget exists (it always should by this point)
		if (Tutorial)
		{
			// Show different conversations based on TutorialIndex
			if (Tutorial->TutorialIndex == 0)
			{				
				Tutorial->ShowConversation_01();  // Initiate the first tutorial conversation
			}
			if (Tutorial->TutorialIndex == 1)
			{
				Tutorial->ShowConversation_04();  // Show the Combat Tutorial
				IsUsable = true;
			}
			if (Tutorial->TutorialIndex == 4 && CompletedTutorial == true)
			{
				Tutorial->ShowConversation_07();  // Show the Congratulatory conversation
			}
		}
	}		
}

// Function called when the player enters the InteractBox
void AGatekeeper::EnterCombatTutorialZone(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AEtherealPlayerMaster>(OtherActor))
	{
		if (!InteractingPlayer)
		{
			// Sometimes the player might pass through this zone without having first interacting with Prodigy.
			// Set the InteractingPlayer reference if it is null
			InteractingPlayer = Cast<AEtherealPlayerMaster>(OtherActor);
		}

		if (InteractingPlayer)
		{
			// Check to see if the player has completed the tutorial
			if (!InteractingPlayer->EtherealPlayerState->HasCompletedTutorial)
			{
				// Check to be sure an InteractWidget exists
				if (!InteractWidget)
				{
					SpawnTutorialWidget();  // Spawn tutorial widget				
				}

				ShowConversation();  // Show Conversation Widget
			}
		}			
	}
}

// Function called when the player can no longer interact with this NPC
void AGatekeeper::ExitCombatTutorialZone(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AEtherealPlayerMaster>(OtherActor))
	{		

	}
}
