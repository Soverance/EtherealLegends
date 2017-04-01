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
#include "MagicOrbs.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AMagicOrbs::AMagicOrbs(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshObject(TEXT("SkeletalMesh'/Game/VFX/sphere_skeletal.sphere_skeletal'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObject(TEXT("StaticMesh'/Game/Weapons/Casting/MagicOrb.MagicOrb'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> OffhandMeshObject(TEXT("StaticMesh'/Game/Weapons/Casting/MagicOrb.MagicOrb'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_MagicOrbs.WeaponIcon_MagicOrbs'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_MagicOrbs-small.WeaponIcon_MagicOrbs-small'"));


	// Set Default Objects

	Name = EMasterGearList::GL_MagicOrbs;
	NameText = LOCTEXT("MagicOrbsName", "Magic Orbs");
	Type = EMasterGearTypes::GT_Casting;
	TypeText = LOCTEXT("MagicOrbsType", "Casting Orbs");
	Description = "Ergonomic and easy to wield, the orbs are standard issue to Cadets of the Ethereal Knights.";
	Price = 2500;
	MPCost = 0.0f;
	ATK = 15.0f;
	DEF = 5.0f;
	SPD = 10.0f;
	HP = 100.0f;
	MP = 100.0f;
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_WeaponSkeletalMesh = SkeletalMeshObject.Object;
	SM_WeaponStaticMesh = StaticMeshObject.Object;
	SM_WeaponOffhandMesh = StaticMeshObject.Object;

	// Set Mesh
	WeaponSkeletalMesh->SetSkeletalMesh(SK_WeaponSkeletalMesh);
	WeaponStaticMesh->SetStaticMesh(SM_WeaponStaticMesh);
	WeaponOffhandMesh->SetStaticMesh(SM_WeaponOffhandMesh);

	//WeaponStaticMesh->SetVisibility(true);
	//WeaponStaticMesh->SetRelativeRotation(FRotator(180.0f, 90.0f, 0.0f));
	//SwordCollider->SetBoxExtent(FVector(10.0f, 15.0f, 60.0f));
	//SwordCollider->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
}

// Called when the game starts or when spawned
void AMagicOrbs::BeginPlay()
{
	Super::BeginPlay();
}

#undef LOCTEXT_NAMESPACE
