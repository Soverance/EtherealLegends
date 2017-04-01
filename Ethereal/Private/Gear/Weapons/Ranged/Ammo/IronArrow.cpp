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
#include "IronArrow.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AIronArrow::AIronArrow(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshObject(TEXT("SkeletalMesh'/Game/VFX/sphere_skeletal.sphere_skeletal'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObject(TEXT("StaticMesh'/Game/Weapons/Ranged/Ammo/IronArrow.IronArrow'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> OffhandMeshObject(TEXT("StaticMesh'/Game/VFX/sphere.sphere'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_IronArrows.WeaponIcon_IronArrows'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_IronArrows_small.WeaponIcon_IronArrows_small'"));

	Name = EMasterGearList::GL_IronArrow;
	NameText = LOCTEXT("IronArrowName", "Iron Arrow");
	Type = EMasterGearTypes::GT_Ammo;
	TypeText = LOCTEXT("IronArrowType", "Ammunition");
	Description = "Arrows forged by Vulcan blacksmiths.";
	Price = 15000;
	MPCost = 0.0f;
	ATK = 10.0f;
	DEF = 0.0f;
	SPD = 0.0f;
	HP = 0.0f;
	MP = 0.0f;
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_WeaponSkeletalMesh = SkeletalMeshObject.Object;
	SM_WeaponStaticMesh = StaticMeshObject.Object;
	SM_WeaponOffhandMesh = StaticMeshObject.Object;

	// Set Mesh
	WeaponSkeletalMesh->SetSkeletalMesh(SK_WeaponSkeletalMesh);
	WeaponSkeletalMesh->SetHiddenInGame(true);
	WeaponStaticMesh->SetStaticMesh(SM_WeaponStaticMesh);
	//WeaponStaticMesh->SetWorldScale3D(FVector(30, 30, 30));  // scale correction
	//WeaponStaticMesh->SetRelativeLocation(FVector(20, -2, -2));  // location correction
	//WeaponStaticMesh->SetRelativeRotation(FRotator(-80, 180, 0));  // location correction
	WeaponOffhandMesh->SetStaticMesh(SM_WeaponOffhandMesh);
	WeaponOffhandMesh->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void AIronArrow::BeginPlay()
{
	Super::BeginPlay();
}

#undef LOCTEXT_NAMESPACE
