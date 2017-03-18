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
#include "Apocalypse.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AApocalypse::AApocalypse(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshObject(TEXT("SkeletalMesh'/Game/VFX/sphere_skeletal.sphere_skeletal'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObject(TEXT("StaticMesh'/Game/Weapons/TwoHanded/Apocalypse/Apocalypse.Apocalypse'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> OffhandMeshObject(TEXT("StaticMesh'/Game/VFX/sphere.sphere'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_Apocalypse.WeaponIcon_Apocalypse'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_Apocalypse-small.WeaponIcon_Apocalypse-small'"));


	// Set Default Objects

	Name = EMasterGearList::GL_Apocalypse;
	NameText = LOCTEXT("ApocalypseName", "Apocalypse");
	Type = EMasterGearTypes::GT_TwoHanded;
	TypeText = LOCTEXT("ApocalypseType", "Two-Handed");
	Description = "An embodiment of the Ethereal Virtue: Apocalypse.";
	Price = 40000;
	MPCost = 0.0f;
	ATK = 50.0f;
	DEF = 50.0f;
	SPD = 15.0f;
	HP = 500.0f;
	MP = 250.0f;
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_WeaponSkeletalMesh = SkeletalMeshObject.Object;
	SM_WeaponStaticMesh = StaticMeshObject.Object;
	SM_WeaponOffhandMesh = StaticMeshObject.Object;

	// Set Mesh
	WeaponSkeletalMesh->SetSkeletalMesh(SK_WeaponSkeletalMesh);
	WeaponStaticMesh->SetStaticMesh(SM_WeaponStaticMesh);
	WeaponStaticMesh->SetWorldScale3D(FVector(1.5f, 1.5f, 1.8f));  // scale correction
	WeaponStaticMesh->SetRelativeLocation(FVector(-15, 0, -40));  // location correction
	WeaponStaticMesh->SetRelativeRotation(FRotator(0, -70, 0));  // rotation correction
	WeaponOffhandMesh->SetStaticMesh(SM_WeaponOffhandMesh);

	SwordCollider->SetupAttachment(WeaponStaticMesh);
	SwordCollider->SetBoxExtent(FVector(10.0f, 10.0f, 50.0f));
	SwordCollider->SetRelativeLocation(FVector(0.0f, 10.0f, 60.0f));
}

// Called when the game starts or when spawned
void AApocalypse::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &AApocalypse::BindWeapon);
}

// Custom code when binding
void AApocalypse::BindWeapon()
{
	// If this weapon was bound while IsShown is true, set the weapon visible
	if (IsShown)
	{
		ShowWeapon(false, true, false);
	}
}

#undef LOCTEXT_NAMESPACE
