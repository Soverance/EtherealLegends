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
#include "BeamSaber.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
ABeamSaber::ABeamSaber(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshObject(TEXT("SkeletalMesh'/Game/VFX/sphere_skeletal.sphere_skeletal'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObject(TEXT("StaticMesh'/Game/Weapons/Novelty/saber-hilt.saber-hilt'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BeamMeshObject(TEXT("StaticMesh'/Game/Weapons/Novelty/saber-blade.saber-blade'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> OffhandMeshObject(TEXT("StaticMesh'/Game/VFX/sphere.sphere'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_BeamSaber.WeaponIcon_BeamSaber'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_BeamSaber-small.WeaponIcon_BeamSaber-small'"));
	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/Weapons/Novelty/Curve_BeamSaber.Curve_BeamSaber'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> IgnitionAudioObject(TEXT("SoundCue'/Game/Weapons/Novelty/BeamSaber_Ignition_Cue.BeamSaber_Ignition_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> OffAudioObject(TEXT("SoundCue'/Game/Weapons/Novelty/BeamSaber_Off_Cue.BeamSaber_Off_Cue'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> IdleAudioObject(TEXT("SoundCue'/Game/Weapons/Novelty/BeamSaber_Idle_Cue.BeamSaber_Idle_Cue'"));

	// Set Default Objects
	Name = EMasterGearList::GL_BeamSaber;
	NameText = LOCTEXT("BeamSaberName", "Beam Saber");
	Type = EMasterGearTypes::GT_OneHanded;
	TypeText = LOCTEXT("BeamSaberType", "One-Handed");
	Description = "An elegant weapon for a more civilized age.";
	Price = 50000;
	MPCost = 0.0f;
	ATK = 60.0f;
	DEF = 40.0f;
	SPD = 20.0f;
	HP = 500.0f;
	MP = 250.0f;
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_WeaponSkeletalMesh = SkeletalMeshObject.Object;
	SM_WeaponStaticMesh = StaticMeshObject.Object;
	SM_BeamMesh = BeamMeshObject.Object;
	SM_WeaponOffhandMesh = StaticMeshObject.Object;
	BeamCurve = Curve.Object;
	S_IgnitionAudio = IgnitionAudioObject.Object;
	S_OffAudio = OffAudioObject.Object;
	S_IdleAudio = IdleAudioObject.Object;

	// Set Mesh
	WeaponSkeletalMesh->SetSkeletalMesh(SK_WeaponSkeletalMesh);

	WeaponStaticMesh->SetStaticMesh(SM_WeaponStaticMesh);
	WeaponStaticMesh->SetWorldScale3D(FVector(0.15f, 0.15f, 0.15f)); // Scale correction
	WeaponStaticMesh->SetRelativeLocation(FVector(-5, 1, 0));
	WeaponStaticMesh->SetRelativeRotation(FRotator(-76, 160, 168));

	WeaponOffhandMesh->SetStaticMesh(SM_WeaponOffhandMesh);

	BeamMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Beam Mesh"));
	BeamMesh->SetStaticMesh(SM_BeamMesh);
	BeamMesh->SetupAttachment(WeaponStaticMesh, FName(TEXT("BeamSocket")));
	BeamMesh->SetVisibility(false);
	UCommonLibrary::SetupSMComponentsWithCollision(BeamMesh);
	BeamMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.0f)); // Scale correction
	BeamMesh->SetRelativeLocation(FVector(-175, 0, 23));
	BeamMesh->SetRelativeRotation(FRotator(60, -90, -90));

	SwordCollider->SetupAttachment(WeaponSkeletalMesh);
	SwordCollider->SetBoxExtent(FVector(10.0f, 10.0f, 60.0f));
	SwordCollider->SetRelativeLocation(FVector(0.0f, 0.0f, 55.0f));

	BeamTimeline = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("BeamTimeline"));
	InterpFunction.BindUFunction(this, FName{ TEXT("TimelineFloatReturn") });

	IgnitionAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("IgnitionAudio"));
	IgnitionAudio->SetupAttachment(RootComponent);
	IgnitionAudio->Sound = S_IgnitionAudio;
	IgnitionAudio->bAutoActivate = false;

	OffAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("OffAudio"));
	OffAudio->SetupAttachment(RootComponent);
	OffAudio->Sound = S_OffAudio;
	OffAudio->bAutoActivate = false;

	IdleAudio = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("IdleAudio"));
	IdleAudio->SetupAttachment(RootComponent);
	IdleAudio->Sound = S_IdleAudio;
	IdleAudio->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ABeamSaber::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &ABeamSaber::BindWeapon);
	OnRemoveGear.AddDynamic(this, &ABeamSaber::RemoveWeapon);
}

// Custom code when binding
void ABeamSaber::BindWeapon()
{
	// If this weapon was bound while IsShown is true, set the weapon visible
	if (IsShown)
	{
		ShowWeapon(false, true, false);
		BeamMesh->SetVisibility(true);
		IdleAudio->Play(0.0f);

		// Activate the beam
		FTimerHandle BeamTimer;
		GetWorldTimerManager().SetTimer(BeamTimer, this, &ABeamSaber::ActivateBeam, 0.5f, false);
	}	
}

// Activate the Beam!
void ABeamSaber::ActivateBeam()
{
	IgnitionAudio->Play();

	BeamTimeline->AddInterpFloat(BeamCurve, InterpFunction, FName{ TEXT("Float") });
	BeamTimeline->PlayFromStart();
}

// Deactivate the Beam!
void ABeamSaber::DisableBeam()
{
	WeaponSkeletalMesh->SetVisibility(false);
	WeaponStaticMesh->SetVisibility(false);
	WeaponOffhandMesh->SetVisibility(false);
	BeamMesh->SetVisibility(false);
	BeamMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.0f)); // Scale correction
}

// Beam Timeline
void ABeamSaber::TimelineFloatReturn(float val)
{
	BeamMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, FMath::FInterpTo(0, 4, val, 0.3f)));
}

// Custom code when removing binding
void ABeamSaber::RemoveWeapon()
{
	Super::RemoveWeapon();

	if (OwnerReference->EtherealPlayerState->WeaponMode == EWeaponModes::WM_OneHanded)
	{
		IdleAudio->Stop();
		OffAudio->Play();

		BeamTimeline->AddInterpFloat(BeamCurve, InterpFunction, FName{ TEXT("Float") });
		BeamTimeline->ReverseFromEnd();

		// Deactivate the beam
		FTimerHandle BeamTimer;
		GetWorldTimerManager().SetTimer(BeamTimer, this, &ABeamSaber::DisableBeam, 1.0f, false);
	}	
}

#undef LOCTEXT_NAMESPACE
