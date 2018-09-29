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
	Mesh->SetSkeletalMesh(SM_Mesh);
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
	DoInteraction.AddDynamic(this, &AGatekeeper::CustomInteract);

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
void AGatekeeper::CustomInteract()
{
	IsUsable = false;

	if (InteractingPlayer)
	{
		// IF the player HAS started the tutorial
		if (StartedTutorial)
		{
			if (Tutorial)
			{
				DoHuh = true;  // animate

				if (Tutorial->TutorialIndex >= 1 && Tutorial->TutorialIndex < 4)
				{
					Tutorial->SkipTo_Conversation03();  // skip to Convo 03
				}

				// The tutorial index will only be 4 if you've defeated the Skeleton King
				if (Tutorial->TutorialIndex == 4)
				{
					CompletedTutorial = true;  // Complete the Tutorial
					ShowConversation();  // Show Conversation Widget
				}
			}
		}
		// IF the player HAS NOT started the tutorial
		if (!StartedTutorial)
		{
			// Check if this is a New Game or not
			if (InteractingPlayer->EtherealGameInstance->IsNewGame)
			{
				// redundancy check, should always return false since you haven't started the tutorial
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
			else // If this IS NOT a New Game...
			{
				// If the player hasn't actually started the tutorial
				if (!InteractingPlayer->EtherealPlayerState->HasCompletedTutorial)
				{
					// if this block runs, this means the player died after starting the tutorial (probably death by Skeleton King), and then GAVE UP LIKE A BITCH, quitting the application.
					// Luckily, they restarted, which loaded their save file, but not their tutorial progress.
					// Since we don't actually save tutorial progress, this is a crappy way to force the player to start a bit further into the process
					// otherwise, they'd have to go speak with Prodigy again, who would give them items they already owned, which looks weird because nothing actually happens.
					// In this case, the player has restarted the game and decided to speak with Prodigy again, so we'll remind them to go beat up the Skeleton King

					// Check to be sure an InteractWidget exists
					if (!InteractWidget)
					{
						SpawnTutorialWidget();  // Spawn tutorial widget				
					}

					if (Tutorial)  // error checking
					{
						Tutorial->TutorialIndex = 1;  // hard set the tutorial index, bypassing the need to speak with Prodigy
						StartedTutorial = true;  // Player has started the Tutorial
						Tutorial->SkipTo_Conversation03();  // skip to Convo 03
					}					
				}
				// If the player has completed the tutorial...
				if (InteractingPlayer->EtherealPlayerState->HasCompletedTutorial)
				{
					// if this block runs, this means the player has finished the tutorial and come back to Prod for a simple conversation later in the game

					// Check to be sure an InteractWidget exists
					if (!InteractWidget)
					{
						SpawnTutorialWidget();  // Spawn tutorial widget				
					}

					if (Tutorial)  // error checking
					{
						DoExplain = true;
						Tutorial->SkipTo_Conversation07();  // Show the Congratulatory conversation, but skip the rewards
					}
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
			// If this is a new game...
			if (InteractingPlayer->EtherealGameInstance->IsNewGame)
			{
				// Check to see if the player has completed the tutorial
				if (!InteractingPlayer->EtherealPlayerState->HasCompletedTutorial)
				{
					// Check to be sure an InteractWidget exists
					if (!InteractWidget)
					{
						SpawnTutorialWidget();  // Spawn tutorial widget				
					}
					// This conversation tells the player to go speak with Prodigy before entering the graveyard
					ShowConversation();  // Show Conversation Widget
				}
			}
			else  // if this is not a new game
			{
				// if this block runs, this means the player died after starting the tutorial (probably death by Skeleton King), and then GAVE UP, quitting the application.
				// Then they restarted, which loaded their save file, but not their tutorial progress.
				// Since we don't actually save tutorial progress, this is a crappy way to force the player to start a bit further into the process
				// otherwise, they'd have to go speak with Prodigy again, who would give them items they already owned.
				// In this case, the player has restarted the game and decided to head straight to the graveyard, so we'll start them directly on the Basic Combat tutorial

				// if the player has not completed the tutorial
				if (!InteractingPlayer->EtherealPlayerState->HasCompletedTutorial)
				{
					// Check to be sure an InteractWidget exists
					if (!InteractWidget)
					{
						SpawnTutorialWidget();  // Spawn tutorial widget				
					}

					if (Tutorial)  // error checking
					{
						// If the tutorial index is less than 1 (should only be possible if this widget was just created during the above process)
						// if the tutorial index is equal to 1, it means the player spoke with Prodigy before heading for the Graveyard
						// If the index is greater than 1, it means the player has already made progress on the tutorial during this play session
						if (Tutorial->TutorialIndex <= 1)
						{
							StartedTutorial = true;  // start the tutorial
							Tutorial->TutorialIndex = 1;  // hard set the tutorial index back to 1, so that the tutorial progresses in the correct manner
							Tutorial->ShowConversation_04();  // Show the Combat Tutorial
							IsUsable = true;
						}
					}									
				}
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
