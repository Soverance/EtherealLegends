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
#include "Widgets/Shop.h"
#include "Chicken.h"

AChicken::AChicken(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> NPCMesh(TEXT("SkeletalMesh'/Game/InfinityBladeAdversaries/Enemy/Enemy_Chicken/Chicken.Chicken'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/InfinityBladeAdversaries/Enemy/Enemy_Chicken/Anims/Anim_Chicken.Anim_Chicken_C'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> BurstParticleObject(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Chicken/P_Chicken_Death_01.P_Chicken_Death_01'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> KickAudioObject(TEXT("SoundCue'/Game/InfinityBladeAdversaries/Enemy/Enemy_Chicken/Chicken_Kick_Cue.Chicken_Kick_Cue'"));

	// Set Default Objects
	SM_Mesh = NPCMesh.Object;
	P_BurstFX = BurstParticleObject.Object;
	S_KickAudio = KickAudioObject.Object;

	Node0 = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Node0"));
	Node0->SetupAttachment(Root);
	Node1 = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Node1"));
	Node1->SetupAttachment(Root);
	Node2 = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Node2"));
	Node2->SetupAttachment(Root);
	Node3 = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Node3"));
	Node3->SetupAttachment(Root);
	Node4 = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Node4"));
	Node4->SetupAttachment(Root);

	// Create objects
	Mesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Mesh"));
	Mesh->SetupAttachment(InteractBox);
	Mesh->SetAnimInstanceClass(AnimBP.Object);
	Mesh->SkeletalMesh = SM_Mesh;
	Mesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	Mesh->bCastCapsuleIndirectShadow = true;

	IsUsable = true;
	InteractAnimType = EInteractAnims::IA_Kick;

	InteractBox->SetBoxExtent(FVector(10, 10, 10));

	DoInteract.AddDynamic(this, &AChicken::Interact);
	
	// Burst Effect
	BurstFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("BurstFX"));
	BurstFX->SetupAttachment(Mesh);
	BurstFX->SetRelativeLocation(FVector(0, 0, 0.1f));
	BurstFX->Template = P_BurstFX;
	BurstFX->bAutoActivate = false;

	// Kick audio
	KickAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("KickAudio"));
	KickAudio->SetupAttachment(RootComponent);
	KickAudio->Sound = S_KickAudio;
	KickAudio->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AChicken::BeginPlay()
{
	Super::BeginPlay();

	// This usually wouldn't be necessary, since we collect this reference when the player enters the NPC's collider.
	// However, we require the reference to draw debug lines for the map, and the player may access the map before having interacting with this actor
	for (TActorIterator<AEtherealPlayerMaster> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		InteractingPlayer = *ActorItr; // get the instance of the Player
	}

	// Configure Node Location Array
	FVector Loc0 = Node0->GetComponentLocation();
	NodeLocations.AddUnique(Loc0);
	FVector Loc1 = Node1->GetComponentLocation();
	NodeLocations.AddUnique(Loc1);
	FVector Loc2 = Node2->GetComponentLocation();
	NodeLocations.AddUnique(Loc2);
	FVector Loc3 = Node3->GetComponentLocation();
	NodeLocations.AddUnique(Loc3);
	FVector Loc4 = Node4->GetComponentLocation();
	NodeLocations.AddUnique(Loc4);

	Patrol();  // start patrolling
}

// Called every frame
void AChicken::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// I see no need to draw the map markers for the chickens... so that code has been removed below
	
	//// Draw Debug Cylinder on Map
	//if (InteractingPlayer->MapControl)
	//{
	//	FVector DebugStart = GetActorLocation();
	//	FVector DebugEnd = FVector(DebugStart.X, DebugStart.Y, (DebugStart.Z + 1500));

	//	DrawDebugCylinder(GetWorld(), DebugStart, DebugEnd, 10, 12, FColor::Orange, false, 0, 0);
	//}
}

// Interact with this NPC
void AChicken::Interact()
{	
	if (IsUsable)
	{
		Wait();  // Stop Patrolling
		IsUsable = false;

		// Blow Up after a split second... better feedback by waiting.
		FTimerHandle BlowUpTimer;
		GetWorldTimerManager().SetTimer(BlowUpTimer, this, &AChicken::BlowUp, 0.5f, false);
	}	
}

// Blow up the chicken, because you kicked it. 
void AChicken::BlowUp()
{
	KickAudio->Play();
	UGameplayStatics::PlayWorldCameraShake(GetWorld(), InteractingPlayer->LevelUpCamShake, InteractingPlayer->GetActorLocation(), 0, 10000, 1, false);  // level up cam shake 
	BurstFX->Activate();
	IsDead = true;
	InteractingPlayer->EtherealPlayerController->Achievement_Chickenlover();

	// determine whether or not to drop an item
	FTimerHandle BlowUpTimer;
	GetWorldTimerManager().SetTimer(BlowUpTimer, this, &AChicken::DropItem, 0.75f, false);
}

// Occasionally the chicken will drop a rare item
void AChicken::DropItem()
{
	InteractingPlayer->EtherealPlayerState->EnemyKillReward(1, EMasterGearList::GL_None, EMasterGearList::GL_None, EMasterGearList::GL_RubberChicken);
}

void AChicken::Patrol_Implementation()
{
}

void AChicken::Wait_Implementation()
{
}