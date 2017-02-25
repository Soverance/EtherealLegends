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
#include "Cat.h"

ACat::ACat(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> NPCMesh(TEXT("SkeletalMesh'/Game/EtherealParty/Cat/cat_mesh.cat_mesh'"));
	static ConstructorHelpers::FObjectFinder<UClass> AnimBP(TEXT("AnimBlueprint'/Game/EtherealParty/Cat/Anim_Cat.Anim_Cat_C'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> CatAudioObject(TEXT("SoundCue'/Game/EtherealParty/Cat/audio/Cat_1_Cue.Cat_1_Cue'"));

	// Set Default Objects
	SM_Mesh = NPCMesh.Object;
	S_CatAudio = CatAudioObject.Object;

	// Create objects
	Mesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetAnimInstanceClass(AnimBP.Object);
	Mesh->SkeletalMesh = SM_Mesh;
	Mesh->SetRelativeScale3D(FVector(15.0f, 15.0f, 15.0f));
	Mesh->bCastCapsuleIndirectShadow = true;

	MapMarkerFX->SetupAttachment(RootComponent);
	MapMarkerFX->SetColorParameter(FName(TEXT("BeamColor")), FColor::Purple);

	IsUsable = true;
	InteractAnimType = EInteractAnims::IA_Pet;

	InteractBox->SetBoxExtent(FVector(10, 10, 10));

	DoInteract.AddDynamic(this, &ACat::Interact);

	// Cat audio
	CatAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("CatAudio"));
	CatAudio->SetupAttachment(RootComponent);
	CatAudio->Sound = S_CatAudio;
	CatAudio->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ACat::BeginPlay()
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
void ACat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Interact with this NPC
void ACat::Interact()
{	
	if (IsUsable)
	{
		IsUsable = false;

		// Blow Up after a split second... better feedback by waiting.
		FTimerHandle BlowUpTimer;
		GetWorldTimerManager().SetTimer(BlowUpTimer, this, &ACat::BlowUp, 0.5f, false);
	}	
}

// Blow up the chicken, because you kicked it. 
void ACat::BlowUp()
{
	CatAudio->Play();
	DoRoar = true;

	// determine whether or not to drop an item
	FTimerHandle BlowUpTimer;
	GetWorldTimerManager().SetTimer(BlowUpTimer, this, &ACat::DropItem, 0.75f, false);
}

// Occasionally the cat will drop a rare item
void ACat::DropItem()
{
	IsUsable = true;
	InteractingPlayer->EtherealPlayerState->EnemyKillReward(0, EMasterGearList::GL_None, EMasterGearList::GL_FeralBand, EMasterGearList::GL_FeralBand);
}