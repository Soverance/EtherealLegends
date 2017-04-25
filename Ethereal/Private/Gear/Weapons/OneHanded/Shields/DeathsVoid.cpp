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
#include "DeathsVoid.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
ADeathsVoid::ADeathsVoid(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshObject(TEXT("SkeletalMesh'/Game/Weapons/Shields/DeathsVoid/DeathsVoid.DeathsVoid'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObject(TEXT("StaticMesh'/Game/VFX/sphere.sphere'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> OffhandMeshObject(TEXT("StaticMesh'/Game/VFX/sphere.sphere'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_DeathsHead.WeaponIcon_DeathsHead'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_DeathsHead-small.WeaponIcon_DeathsHead-small'"));


	// Set Default Objects

	Name = EMasterGearList::GL_DeathsVoid;
	NameText = LOCTEXT("DeathsVoidName", "Death's Void");
	Type = EMasterGearTypes::GT_Shield;
	TypeText = LOCTEXT("DeathsVoidType", "Shield");
	Description = "A shield forged from pure darkness, signed by Death himself.";
	Price = 40000;
	MPCost = 0.0f;
	ATK = 30.0f;
	DEF = 30.0f;
	SPD = 30.0f;
	HP = 500.0f;
	MP = 250.0f;
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_WeaponSkeletalMesh = SkeletalMeshObject.Object;
	SM_WeaponStaticMesh = StaticMeshObject.Object;
	SM_WeaponOffhandMesh = StaticMeshObject.Object;

	// Set Mesh
	WeaponSkeletalMesh->SetSkeletalMesh(SK_WeaponSkeletalMesh);
	WeaponSkeletalMesh->SetRelativeLocation(FVector(0, 75, -42));  // location correction
	WeaponSkeletalMesh->SetWorldScale3D(FVector(28, 40, 20)); // Scale correction
	WeaponStaticMesh->SetStaticMesh(SM_WeaponStaticMesh);
	WeaponStaticMesh->SetHiddenInGame(true);
	WeaponOffhandMesh->SetStaticMesh(SM_WeaponOffhandMesh);
	WeaponOffhandMesh->SetHiddenInGame(true);

	//WeaponStaticMesh->SetVisibility(true);
	//SwordCollider->SetBoxExtent(FVector(5.0f, 5.0f, 25.0f));
	//SwordCollider->SetRelativeLocation(FVector(0.0f, 0.0f, 5.0f));
}

// Called when the game starts or when spawned
void ADeathsVoid::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &ADeathsVoid::BindWeapon);
}

// Custom code when binding
void ADeathsVoid::BindWeapon()
{
	// If this weapon was bound while IsShown is true, set the weapon visible
	if (IsShown)
	{
		ShowWeapon(true, false, false);
	}
}

#undef LOCTEXT_NAMESPACE
