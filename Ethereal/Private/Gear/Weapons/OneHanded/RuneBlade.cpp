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
#include "RuneBlade.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
ARuneBlade::ARuneBlade(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshObject(TEXT("SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Dual_Blade/Dual_Blade_Fang/SK_RuneBlade.SK_RuneBlade'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObject(TEXT("StaticMesh'/Game/VFX/sphere.sphere'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> OffhandMeshObject(TEXT("StaticMesh'/Game/VFX/sphere.sphere'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_RuneBlade.WeaponIcon_RuneBlade'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_RuneBlade-small.WeaponIcon_RuneBlade-small'"));
	
	// Set Default Objects

	Name = EMasterGearList::GL_RuneBlade;
	NameText = LOCTEXT("RuneBladeName", "Rune Blade");
	Type = EMasterGearTypes::GT_OneHanded;
	TypeText = LOCTEXT("RuneBladeType", "One-Handed");
	Description = "A blade inscribed with ancient runes.";
	Price = 15000;
	MPCost = 0.0f;
	ATK = 10.0f;
	DEF = 10.0f;
	SPD = 5.0f;
	HP = 100.0f;
	MP = 50.0f;
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_WeaponSkeletalMesh = SkeletalMeshObject.Object;
	SM_WeaponStaticMesh = StaticMeshObject.Object;
	SM_WeaponOffhandMesh = StaticMeshObject.Object;

	// Set Mesh
	WeaponSkeletalMesh->SetSkeletalMesh(SK_WeaponSkeletalMesh);
	WeaponSkeletalMesh->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	WeaponSkeletalMesh->SetRelativeRotation(FRotator(0, 180, 0));
	WeaponStaticMesh->SetStaticMesh(SM_WeaponStaticMesh);
	WeaponOffhandMesh->SetStaticMesh(SM_WeaponOffhandMesh);

	SwordCollider->SetupAttachment(WeaponSkeletalMesh);
	SwordCollider->SetBoxExtent(FVector(10.0f, 10.0f, 50.0f));
	SwordCollider->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));
}

// Called when the game starts or when spawned
void ARuneBlade::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &ARuneBlade::BindWeapon);
}

// Custom code when binding
void ARuneBlade::BindWeapon()
{
	// If this weapon was bound while IsShown is true, set the weapon visible
	if (IsShown)
	{
		ShowWeapon(true, false, false);
	}
}

#undef LOCTEXT_NAMESPACE
