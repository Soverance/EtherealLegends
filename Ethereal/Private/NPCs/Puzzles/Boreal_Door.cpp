// Â© 2014 - 2017 Soverance Studios
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
#include "Boreal_Door.h"

ABoreal_Door::ABoreal_Door(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorLeftMesh(TEXT("StaticMesh'/Game/Environment/Meshes/SM_Cave_Statue_01.SM_Cave_Statue_01'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorRightMesh(TEXT("StaticMesh'/Game/Environment/Meshes/SM_Cave_Statue_01.SM_Cave_Statue_01'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Satellite1Mesh(TEXT("StaticMesh'/Game/Environment/Meshes/SM_Cave_Statue_01.SM_Cave_Statue_01'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Satellite2Mesh(TEXT("StaticMesh'/Game/Environment/Meshes/SM_Cave_Statue_01.SM_Cave_Statue_01'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AuraLeftDoorParticle(TEXT("ParticleSystem'/Game/ExampleContent/Effects/ParticleSystems/P_Sov_StatueAura.P_Sov_StatueAura'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AuraRightDoorParticle(TEXT("ParticleSystem'/Game/ExampleContent/Effects/ParticleSystems/P_Sov_StatueAura.P_Sov_StatueAura'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AuraSatellite1Particle(TEXT("ParticleSystem'/Game/ExampleContent/Effects/ParticleSystems/P_Sov_StatueAura.P_Sov_StatueAura'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AuraSatellite2Particle(TEXT("ParticleSystem'/Game/ExampleContent/Effects/ParticleSystems/P_Sov_StatueAura.P_Sov_StatueAura'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> FlareLeftDoorParticle(TEXT("ParticleSystem'/Game/Effects/Particles/Eth_DemonStatuePower.Eth_DemonStatuePower'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> FlareRightDoorParticle(TEXT("ParticleSystem'/Game/Effects/Particles/Eth_DemonStatuePower.Eth_DemonStatuePower'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> FlareSatellite1Particle(TEXT("ParticleSystem'/Game/Effects/Particles/Eth_DemonStatuePower.Eth_DemonStatuePower'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> FlareSatellite2Particle(TEXT("ParticleSystem'/Game/Effects/Particles/Eth_DemonStatuePower.Eth_DemonStatuePower'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> LeftDoorAudioObject(TEXT("SoundCue'/Game/Audio/Cave/Statue_Burst_Cue.Statue_Burst_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> RightDoorAudioObject(TEXT("SoundCue'/Game/Audio/Cave/Statue_Burst_Cue.Statue_Burst_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> Satellite1AudioObject(TEXT("SoundCue'/Game/Audio/Cave/Statue_Burst_Cue.Statue_Burst_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> Satellite2AudioObject(TEXT("SoundCue'/Game/Audio/Cave/Statue_Burst_Cue.Statue_Burst_Cue'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DoorsMesh(TEXT("SkeletalMesh'/Game/Elemental/Animation/Skeletal_Meshes/lava_knight_proxy/Throne_Doors.Throne_Doors'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorsArchMesh(TEXT("StaticMesh'/Game/Elemental/Environment/Throne_Exterior/Mesh/SM_Throne_Exterior_DoorArch.SM_Throne_Exterior_DoorArch'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> DoorOpenAudioObject(TEXT("SoundCue'/Game/Elemental/Sound/Cinematic/DoorOpening.DoorOpening'"));
	static ConstructorHelpers::FObjectFinder<UAnimationAsset> DoorOpenAnimObject(TEXT("AnimSequence'/Game/Elemental/Animation/LavaKnight_Animations/Anims/Anim_Shot_0003_Throne_Doors.Anim_Shot_0003_Throne_Doors'"));
	static ConstructorHelpers::FObjectFinder<UClass> DropBlueprintObject(TEXT("Blueprint'/Game/Blueprints/NPCs/Puzzles/BorealDoor_Drop.BorealDoor_Drop_C'"));
	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/Blueprints/NPCs/Puzzles/Curve_ShiitakeGate.Curve_ShiitakeGate'"));

	// Set Default Objects
	SM_Statue_LeftDoor = DoorLeftMesh.Object;
	SM_Statue_RightDoor = DoorRightMesh.Object;
	SM_Statue_Satellite1 = Satellite1Mesh.Object;
	SM_Statue_Satellite2 = Satellite2Mesh.Object;
	P_AuraFX_LeftDoor = AuraLeftDoorParticle.Object;
	P_AuraFX_RightDoor = AuraRightDoorParticle.Object;
	P_AuraFX_Satellite1 = AuraSatellite1Particle.Object;
	P_AuraFX_Satellite2 = AuraSatellite2Particle.Object;
	P_FlareFX_LeftDoor = FlareLeftDoorParticle.Object;
	P_FlareFX_RightDoor = FlareRightDoorParticle.Object;
	P_FlareFX_Satellite1 = FlareSatellite1Particle.Object;
	P_FlareFX_Satellite2 = FlareSatellite2Particle.Object;
	S_FlareAudio_LeftDoor = LeftDoorAudioObject.Object;
	S_FlareAudio_RightDoor = RightDoorAudioObject.Object;
	S_FlareAudio_Satellite1 = Satellite1AudioObject.Object;
	S_FlareAudio_Satellite2 = Satellite2AudioObject.Object;
	SK_Doors = DoorsMesh.Object;
	SM_DoorsArch = DoorsArchMesh.Object;
	S_DoorOpenAudio = DoorOpenAudioObject.Object;
	DoorOpenAnim = DoorOpenAnimObject.Object;
	ColorCurve = Curve.Object;

	DoorDropBP = DropBlueprintObject.Object;

	// DEFAULTS

	IsUsable = true;
	InteractAnimType = EInteractAnims::IA_Open;

	Color_Active = FColor::Orange;  // orange
	Color_Inactive = FColor::Blue;  // blue
	Solved = false;

	InteractBox->SetRelativeLocation(FVector(0, 0, -200));  // Move the default Interact box out of the way


	// STATUE LEFT DOOR

	Active_LeftDoor = false;

	LeftDoorTimeline = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("LeftDoorTimeline"));
	InterpFunctionLeftDoor.BindUFunction(this, FName{ TEXT("LeftDoorTimelineFloatReturn") });

	Statue_LeftDoor = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Statue_LeftDoor"));
	Statue_LeftDoor->SetStaticMesh(SM_Statue_LeftDoor);
	Statue_LeftDoor->SetupAttachment(Root);
	Statue_LeftDoor->SetRelativeLocation(FVector(327, -214, -14));
	Statue_LeftDoor->SetRelativeRotation(FRotator(0, 177, 0));

	InteractBox_LeftDoor = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("InteractBox_LeftDoor"));
	InteractBox_LeftDoor->SetupAttachment(Statue_LeftDoor);
	InteractBox_LeftDoor->SetBoxExtent(FVector(100, 150, 60));
	InteractBox_LeftDoor->SetRelativeLocation(FVector(0, 130, 75));

	PointLight_LeftDoor = ObjectInitializer.CreateDefaultSubobject<UPointLightComponent>(this, TEXT("PointLight_LeftDoor"));
	PointLight_LeftDoor->SetupAttachment(Statue_LeftDoor);
	PointLight_LeftDoor->SetRelativeLocation(FVector(0, 70, 175));
	PointLight_LeftDoor->LightColor = Color_Inactive;

	AuraFX_LeftDoor = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("AuraFX_LeftDoor"));
	AuraFX_LeftDoor->Template = P_AuraFX_LeftDoor;
	AuraFX_LeftDoor->bAutoActivate = false;
	AuraFX_LeftDoor->SetupAttachment(Statue_LeftDoor, "StatueAura");

	FlareFX_LeftDoor = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("FlareFX_LeftDoor"));
	FlareFX_LeftDoor->Template = P_FlareFX_LeftDoor;
	FlareFX_LeftDoor->bAutoActivate = false;
	FlareFX_LeftDoor->SetupAttachment(Statue_LeftDoor, "StatueAura");
	//FlareFX_LeftDoor->SetRelativeLocation(FVector(0, 0, 0));
	FlareFX_LeftDoor->SetRelativeRotation(FRotator(90, 0, 0));

	FlareAudio_LeftDoor = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("FlareAudio_LeftDoor"));
	FlareAudio_LeftDoor->Sound = S_FlareAudio_LeftDoor;
	FlareAudio_LeftDoor->bAutoActivate = false;
	FlareAudio_LeftDoor->SetupAttachment(Statue_LeftDoor);
	
	// STATUE RIGHT DOOR

	Active_RightDoor = false;

	RightDoorTimeline = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("RightDoorTimeline"));
	InterpFunctionRightDoor.BindUFunction(this, FName{ TEXT("RightDoorTimelineFloatReturn") });

	Statue_RightDoor = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Statue_RightDoor"));
	Statue_RightDoor->SetStaticMesh(SM_Statue_RightDoor);
	Statue_RightDoor->SetupAttachment(Root);
	Statue_RightDoor->SetRelativeLocation(FVector(-327, -177, -12));
	Statue_RightDoor->SetRelativeRotation(FRotator(0, 177, 0));

	InteractBox_RightDoor = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("InteractBox_RightDoor"));
	InteractBox_RightDoor->SetupAttachment(Statue_RightDoor);
	InteractBox_RightDoor->SetBoxExtent(FVector(100, 150, 60));
	InteractBox_RightDoor->SetRelativeLocation(FVector(0, 130, 75));

	PointLight_RightDoor = ObjectInitializer.CreateDefaultSubobject<UPointLightComponent>(this, TEXT("PointLight_RightDoor"));
	PointLight_RightDoor->SetupAttachment(Statue_RightDoor);
	PointLight_RightDoor->SetRelativeLocation(FVector(0, 70, 175));
	PointLight_RightDoor->LightColor = Color_Inactive;

	AuraFX_RightDoor = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("AuraFX_RightDoor"));
	AuraFX_RightDoor->Template = P_AuraFX_RightDoor;
	AuraFX_RightDoor->bAutoActivate = false;
	AuraFX_RightDoor->SetupAttachment(Statue_RightDoor, "StatueAura");

	FlareFX_RightDoor = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("FlareFX_RightDoor"));
	FlareFX_RightDoor->Template = P_FlareFX_RightDoor;
	FlareFX_RightDoor->bAutoActivate = false;
	FlareFX_RightDoor->SetupAttachment(Statue_RightDoor, "StatueAura");

	FlareAudio_RightDoor = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("FlareAudio_RightDoor"));
	FlareAudio_RightDoor->Sound = S_FlareAudio_RightDoor;
	FlareAudio_RightDoor->bAutoActivate = false;
	FlareAudio_RightDoor->SetupAttachment(Statue_RightDoor);
	
	// SATELLITE STATUE 1

	Active_Satellite1 = true;

	Satellite1Timeline = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("Satellite1Timeline"));
	InterpFunctionSatellite1.BindUFunction(this, FName{ TEXT("Satellite1TimelineFloatReturn") });

	Statue_Satellite1 = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Statue_Satellite1"));
	Statue_Satellite1->SetStaticMesh(SM_Statue_Satellite1);
	Statue_Satellite1->SetupAttachment(Root);
	Statue_Satellite1->SetRelativeLocation(FVector(-221, -2033, -19));
	Statue_Satellite1->SetRelativeRotation(FRotator(0, 14.3f, 0));

	InteractBox_Satellite1 = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("InteractBox_Satellite1"));
	InteractBox_Satellite1->SetupAttachment(Statue_Satellite1);
	InteractBox_Satellite1->SetBoxExtent(FVector(100, 150, 60));
	InteractBox_Satellite1->SetRelativeLocation(FVector(0, 130, 75));

	PointLight_Satellite1 = ObjectInitializer.CreateDefaultSubobject<UPointLightComponent>(this, TEXT("PointLight_Satellite1"));
	PointLight_Satellite1->SetupAttachment(Statue_Satellite1);
	PointLight_Satellite1->SetRelativeLocation(FVector(0, 70, 175));
	PointLight_Satellite1->LightColor = Color_Active;

	AuraFX_Satellite1 = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("AuraFX_Satellite1"));
	AuraFX_Satellite1->Template = P_AuraFX_Satellite1;
	AuraFX_Satellite1->bAutoActivate = true;
	AuraFX_Satellite1->SetupAttachment(Statue_Satellite1, "StatueAura");

	FlareFX_Satellite1 = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("FlareFX_Satellite1"));
	FlareFX_Satellite1->Template = P_FlareFX_Satellite1;
	FlareFX_Satellite1->bAutoActivate = false;
	FlareFX_Satellite1->SetupAttachment(Statue_Satellite1, "StatueAura");

	FlareAudio_Satellite1 = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("FlareAudio_Satellite1"));
	FlareAudio_Satellite1->Sound = S_FlareAudio_Satellite1;
	FlareAudio_Satellite1->bAutoActivate = false;
	FlareAudio_Satellite1->SetupAttachment(Statue_Satellite1);
	
	// SATELLITE STATUE 2

	Active_Satellite2 = true;

	Satellite2Timeline = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("Satellite2Timeline"));
	InterpFunctionSatellite2.BindUFunction(this, FName{ TEXT("Satellite2TimelineFloatReturn") });

	Statue_Satellite2 = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Statue_Satellite2"));
	Statue_Satellite2->SetStaticMesh(SM_Statue_Satellite2);
	Statue_Satellite2->SetupAttachment(Root);
	Statue_Satellite2->SetRelativeLocation(FVector(1940, -3809, -9.6f));
	Statue_Satellite2->SetRelativeRotation(FRotator(0, -8.1f, 0));

	InteractBox_Satellite2 = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("InteractBox_Satellite2"));
	InteractBox_Satellite2->SetupAttachment(Statue_Satellite2);
	InteractBox_Satellite2->SetBoxExtent(FVector(100, 150, 60));
	InteractBox_Satellite2->SetRelativeLocation(FVector(0, 130, 75));
	
	PointLight_Satellite2 = ObjectInitializer.CreateDefaultSubobject<UPointLightComponent>(this, TEXT("PointLight_Satellite2"));
	PointLight_Satellite2->SetupAttachment(Statue_Satellite2);
	PointLight_Satellite2->SetRelativeLocation(FVector(0, 70, 175));
	PointLight_Satellite2->LightColor = Color_Active;

	AuraFX_Satellite2 = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("AuraFX_Satellite2"));
	AuraFX_Satellite2->Template = P_AuraFX_Satellite2;
	AuraFX_Satellite2->bAutoActivate = true;
	AuraFX_Satellite2->SetupAttachment(Statue_Satellite2, "StatueAura");

	FlareFX_Satellite2 = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("FlareFX_Satellite2"));
	FlareFX_Satellite2->Template = P_FlareFX_Satellite2;
	FlareFX_Satellite2->bAutoActivate = false;
	FlareFX_Satellite2->SetupAttachment(Statue_Satellite2, "StatueAura");

	FlareAudio_Satellite2 = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("FlareAudio_Satellite2"));
	FlareAudio_Satellite2->Sound = S_FlareAudio_Satellite2;
	FlareAudio_Satellite2->bAutoActivate = false;
	FlareAudio_Satellite2->SetupAttachment(Statue_Satellite2);
	
	// DOORS

	DoorsArch = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("DoorsArch"));
	DoorsArch->SetStaticMesh(SM_DoorsArch);
	DoorsArch->SetupAttachment(Root);
	DoorsArch->SetRelativeScale3D(FVector(1.3f, 1.0f, 1.1f));

	Doors = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Doors"));
	Doors->SetSkeletalMesh(SK_Doors);
	Doors->SetupAttachment(DoorsArch);
	Doors->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	Doors->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.45f));
	Doors->SetRelativeLocation(FVector(-0, -30, 0));

	DoorOpenAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DoorOpenAudio"));
	DoorOpenAudio->Sound = S_DoorOpenAudio;
	DoorOpenAudio->bAutoActivate = false;
	DoorOpenAudio->SetupAttachment(DoorsArch);

	Doors->SetupAttachment(DoorsArch);
	DoorOpenAudio->SetupAttachment(DoorsArch);

}

// Called when the game starts or when spawned
void ABoreal_Door::BeginPlay()
{
	Super::BeginPlay();

	DoInteract.AddDynamic(this, &ABoreal_Door::Interact);

	InteractBox_LeftDoor->OnComponentBeginOverlap.AddDynamic(this, &ABoreal_Door::Entered_LeftDoor);
	InteractBox_LeftDoor->OnComponentEndOverlap.AddDynamic(this, &AEtherealNPCMaster::EndInteract);
	InteractBox_RightDoor->OnComponentBeginOverlap.AddDynamic(this, &ABoreal_Door::Entered_RightDoor);
	InteractBox_RightDoor->OnComponentEndOverlap.AddDynamic(this, &AEtherealNPCMaster::EndInteract);
	InteractBox_Satellite1->OnComponentBeginOverlap.AddDynamic(this, &ABoreal_Door::Entered_Satellite1);
	InteractBox_Satellite1->OnComponentEndOverlap.AddDynamic(this, &AEtherealNPCMaster::EndInteract);
	InteractBox_Satellite2->OnComponentBeginOverlap.AddDynamic(this, &ABoreal_Door::Entered_Satellite2);
	InteractBox_Satellite2->OnComponentEndOverlap.AddDynamic(this, &AEtherealNPCMaster::EndInteract);
}

// Interact with this NPC
void ABoreal_Door::Interact()
{
	switch (CurrentStatue) // switch on CurrentStatue
	{
	case ECurrentStatue::CS_None: // if None, do nothing
		break;

	////////////////////////////////////////////////
	//// LEFT DOOR

	case ECurrentStatue::CS_LeftDoor: // LEFT DOOR
		if (Active_LeftDoor) // if Left Door is active
		{
			if (!IsCarryingDrop) // if player is not carrying a drop
			{
				OnLeftDoor.Broadcast();  // Broadcast Left Door event  (this plays the Matinee in the level BP)
				Active_LeftDoor = false; // left door inactive
				FlareFX_LeftDoor->Activate(); // activate flare fx
				FlareAudio_LeftDoor->Play(); // play flare audio				
				AuraFX_LeftDoor->Deactivate(); // deactivate aura

				// Spawn Door Drop, attach it to player
				DoorDrop = UCommonLibrary::SpawnBP(GetWorld(), DoorDropBP, InteractingPlayer->GetActorLocation(), InteractingPlayer->GetActorRotation());
				DoorDrop->AttachToComponent(InteractingPlayer->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,"PowerSocket");
				IsCarryingDrop = true;

				// Run timeline that lerps color of light at this door from ACTIVE to INACTIVE, reset interaction for statues when finished
				LeftDoorTimeline->AddInterpFloat(ColorCurve, InterpFunctionLeftDoor, FName{ TEXT("Float") });
				LeftDoorTimeline->PlayFromStart();
			}
			else
			{
				InteractingPlayer->AudioManager->Play_SFX_Error();  // ERROR - the statue cannot be used because status is active and player is carrying a drop				
			}
		}
		else // if the Left Door statue is inactive
		{
			if (IsCarryingDrop) // if player is carring a statue drop
			{
				OnLeftDoor.Broadcast();  // Broadcast Left Door event  (this plays the Matinee in the level BP)
				Active_LeftDoor = true; // activate this statue
				FlareFX_LeftDoor->Activate();  // activate flare fx
				FlareAudio_LeftDoor->Play();  // play flare audio				
				AuraFX_LeftDoor->Activate();  // activate aura fx				
				DoorDrop->Destroy();  // Remove door drop
				IsCarryingDrop = false;

				// Run timeline that lerps color of light at this door from INACTIVE to ACTIVE, reset interaction for statues when finished.
				LeftDoorTimeline->AddInterpFloat(ColorCurve, InterpFunctionLeftDoor, FName{ TEXT("Float") });
				LeftDoorTimeline->ReverseFromEnd();

				CheckForSuccess();  // Check for puzzle success
			}
			else
			{
				InteractingPlayer->AudioManager->Play_SFX_Error(); // ERROR statue cannot be used because player is not carrying drop to activate the statue with
			}
		}
		break;

	///////////////////////////////////////////////////////
	////// RIGHT DOOR

	case ECurrentStatue::CS_RightDoor:
		if (Active_RightDoor) // if statue is active
		{
			if (!IsCarryingDrop) // if player is not carrying a drop
			{
				OnRightDoor.Broadcast();  // Broadcast Right Door event  (this plays the Matinee in the level BP)
				Active_RightDoor = false; // left door inactive
				FlareFX_RightDoor->Activate(); // activate flare fx
				FlareAudio_RightDoor->Play(); // play flare audio				
				AuraFX_RightDoor->Deactivate(); // deactivate aura

				// Spawn Door Drop, attach it to player
				DoorDrop = UCommonLibrary::SpawnBP(GetWorld(), DoorDropBP, InteractingPlayer->GetActorLocation(), InteractingPlayer->GetActorRotation());
				DoorDrop->AttachToComponent(InteractingPlayer->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "PowerSocket");
				IsCarryingDrop = true;

				// Run timeline that lerps color of light at this door from ACTIVE to INACTIVE, reset interaction for statues when finished
				RightDoorTimeline->AddInterpFloat(ColorCurve, InterpFunctionRightDoor, FName{ TEXT("Float") });
				RightDoorTimeline->PlayFromStart();
			}
			else
			{
				InteractingPlayer->AudioManager->Play_SFX_Error(); // ERROR - the statue cannot be used because status is active and player is carrying a drop
			}
		}
		else // if the Left Door statue is inactive
		{
			if (IsCarryingDrop) // if player is carring a statue drop
			{
				OnRightDoor.Broadcast();  // Broadcast Right Door event  (this plays the Matinee in the level BP)
				Active_RightDoor = true; // activate this statue
				FlareFX_RightDoor->Activate();  // activate flare fx
				FlareAudio_RightDoor->Play();  // play flare audio				
				AuraFX_RightDoor->Activate();  // activate aura fx				
				DoorDrop->Destroy();  // Remove door drop from player
				IsCarryingDrop = false;

				// Run timeline that lerps color of light at this door from INACTIVE to ACTIVE, reset interaction for statues when finished.
				RightDoorTimeline->AddInterpFloat(ColorCurve, InterpFunctionRightDoor, FName{ TEXT("Float") });
				RightDoorTimeline->ReverseFromEnd();

				CheckForSuccess();  // Check for puzzle success
			}
			else
			{
				InteractingPlayer->AudioManager->Play_SFX_Error(); // ERROR statue cannot be used because player is not carrying drop to activate the statue with
			}
		}
		break;

	///////////////////////////////////////////////////////////
	////// SATELLITE 1

	case ECurrentStatue::CS_Satellite1:
		if (Active_Satellite1) // if statue is active
		{
			if (!IsCarryingDrop) // if player is not carrying a drop
			{
				OnSat1.Broadcast();  // Broadcast Satellite 1 event  (this plays the Matinee in the level BP)
				Active_Satellite1 = false; // left door inactive
				FlareFX_Satellite1->Activate(); // activate flare fx
				FlareAudio_Satellite1->Play(); // play flare audio				
				AuraFX_Satellite1->Deactivate(); // deactivate aura

				// Spawn Door Drop, attach it to player
				DoorDrop = UCommonLibrary::SpawnBP(GetWorld(), DoorDropBP, InteractingPlayer->GetActorLocation(), InteractingPlayer->GetActorRotation());
				DoorDrop->AttachToComponent(InteractingPlayer->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "PowerSocket");
				IsCarryingDrop = true;

				// Run timeline that lerps color of light at this door from ACTIVE to INACTIVE, reset interaction for statues when finished
				Satellite1Timeline->AddInterpFloat(ColorCurve, InterpFunctionSatellite1, FName{ TEXT("Float") });
				Satellite1Timeline->PlayFromStart();
			}
			else
			{
				InteractingPlayer->AudioManager->Play_SFX_Error(); // ERROR - the statue cannot be used because status is active and player is carrying a drop
			}
		}
		else // if the Left Door statue is inactive
		{
			if (IsCarryingDrop) // if player is carring a statue drop
			{
				OnSat1.Broadcast();  // Broadcast Satellite 1 event  (this plays the Matinee in the level BP)
				Active_Satellite1 = true; // activate this statue
				FlareFX_Satellite1->Activate();  // activate flare fx
				FlareAudio_Satellite1->Play();  // play flare audio				
				AuraFX_Satellite1->Activate();  // activate aura fx				
				DoorDrop->Destroy();  // Remove door drop
				IsCarryingDrop = false;

				// Run timeline that lerps color of light at this door from INACTIVE to ACTIVE, reset interaction for statues when finished.
				Satellite1Timeline->AddInterpFloat(ColorCurve, InterpFunctionSatellite1, FName{ TEXT("Float") });
				Satellite1Timeline->ReverseFromEnd();

				CheckForSuccess();  // Check for puzzle success
			}
			else
			{
				InteractingPlayer->AudioManager->Play_SFX_Error(); // ERROR statue cannot be used because player is not carrying drop to activate the statue with
			}
		}
		break;

	//////////////////////////////////////////////////////
	//// SATELLITE 2

	case ECurrentStatue::CS_Satellite2:
		if (Active_Satellite2) // if statue is active
		{
			if (!IsCarryingDrop) // if player is not carrying a drop
			{
				OnSat2.Broadcast();  // Broadcast Satellite 2 event  (this plays the Matinee in the level BP)
				Active_Satellite2 = false; // left door inactive
				FlareFX_Satellite2->Activate(); // activate flare fx
				FlareAudio_Satellite2->Play(); // play flare audio				
				AuraFX_Satellite2->Deactivate(); // deactivate aura

				// Spawn Door Drop, attach it to player
				DoorDrop = UCommonLibrary::SpawnBP(GetWorld(), DoorDropBP, InteractingPlayer->GetActorLocation(), InteractingPlayer->GetActorRotation());
				DoorDrop->AttachToComponent(InteractingPlayer->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "PowerSocket");
				IsCarryingDrop = true;

				// Run timeline that lerps color of light at this door from ACTIVE to INACTIVE, reset interaction for statues when finished
				Satellite2Timeline->AddInterpFloat(ColorCurve, InterpFunctionSatellite2, FName{ TEXT("Float") });
				Satellite2Timeline->PlayFromStart();
			}
			else
			{
				InteractingPlayer->AudioManager->Play_SFX_Error(); // ERROR - the statue cannot be used because status is active and player is carrying a drop
			}
		}
		else // if the Left Door statue is inactive
		{
			if (IsCarryingDrop) // if player is carring a statue drop
			{
				OnSat2.Broadcast();  // Broadcast Satellite 2 event  (this plays the Matinee in the level BP)
				Active_Satellite2 = true; // activate this statue
				FlareFX_Satellite2->Activate();  // activate flare fx
				FlareAudio_Satellite2->Play();  // play flare audio				
				AuraFX_Satellite2->Activate();  // activate aura fx				
				DoorDrop->Destroy();  // Remove door drop
				IsCarryingDrop = false;

				// Run timeline that lerps color of light at this door from INACTIVE to ACTIVE, reset interaction for statues when finished.
				Satellite2Timeline->AddInterpFloat(ColorCurve, InterpFunctionSatellite2, FName{ TEXT("Float") });
				Satellite2Timeline->ReverseFromEnd();

				CheckForSuccess();  // Check for puzzle success
			}
			else
			{
				InteractingPlayer->AudioManager->Play_SFX_Error(); // ERROR statue cannot be used because player is not carrying drop to activate the statue with
			}
		}
		break;
	}

	// Do the stomp blast after the timeline completes
	FTimerHandle StopTimer;
	GetWorldTimerManager().SetTimer(StopTimer, this, &AEtherealNPCMaster::StopInteraction, 3.0f, false);
}

void ABoreal_Door::Entered_LeftDoor(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AEtherealPlayerMaster>(OtherActor))
	{
		InteractingPlayer = Cast<AEtherealPlayerMaster>(OtherActor);
		CheckIfUsable();
		CurrentStatue = ECurrentStatue::CS_LeftDoor;
	}
}

void ABoreal_Door::Entered_RightDoor(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AEtherealPlayerMaster>(OtherActor))
	{
		InteractingPlayer = Cast<AEtherealPlayerMaster>(OtherActor);
		CheckIfUsable();
		CurrentStatue = ECurrentStatue::CS_RightDoor;
	}
}

void ABoreal_Door::Entered_Satellite1(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AEtherealPlayerMaster>(OtherActor))
	{
		InteractingPlayer = Cast<AEtherealPlayerMaster>(OtherActor);
		CheckIfUsable();
		CurrentStatue = ECurrentStatue::CS_Satellite1;
	}
}

void ABoreal_Door::Entered_Satellite2(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AEtherealPlayerMaster>(OtherActor))
	{
		InteractingPlayer = Cast<AEtherealPlayerMaster>(OtherActor);
		CheckIfUsable();
		CurrentStatue = ECurrentStatue::CS_Satellite2;
	}
}

// Light To Active Timeline
void ABoreal_Door::LeftDoorTimelineFloatReturn(float val)
{
	PointLight_LeftDoor->SetLightColor(FLinearColor::LerpUsingHSV(Color_Active.ReinterpretAsLinear(), Color_Inactive.ReinterpretAsLinear(), val));
}

// Light To Inactive Timeline
void ABoreal_Door::RightDoorTimelineFloatReturn(float val)
{
	PointLight_RightDoor->SetLightColor(FLinearColor::LerpUsingHSV(Color_Active.ReinterpretAsLinear(), Color_Inactive.ReinterpretAsLinear(), val));
}

// Light To Active Timeline
void ABoreal_Door::Satellite1TimelineFloatReturn(float val)
{
	PointLight_Satellite1->SetLightColor(FLinearColor::LerpUsingHSV(Color_Active.ReinterpretAsLinear(), Color_Inactive.ReinterpretAsLinear(), val));
}

// Light To Inactive Timeline
void ABoreal_Door::Satellite2TimelineFloatReturn(float val)
{
	PointLight_Satellite2->SetLightColor(FLinearColor::LerpUsingHSV(Color_Active.ReinterpretAsLinear(), Color_Inactive.ReinterpretAsLinear(), val));
}

// Checks if this puzzle has been solved
void ABoreal_Door::CheckForSuccess()
{
	if (Active_LeftDoor && Active_RightDoor)
	{
		IsUsable = false;
		OnOpenDoor.Broadcast();  // Broadcast Open Door event  (this plays the Matinee in the level BP)
		DoorOpenAudio->Play();		
		Doors->PlayAnimation(DoorOpenAnim, false); 
		Solved = true;
	}
}
