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
#include "SpartanShield.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
ASpartanShield::ASpartanShield(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshObject(TEXT("SkeletalMesh'/Game/VFX/sphere_skeletal.sphere_skeletal'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObject(TEXT("StaticMesh'/Game/Elemental/Environment/Throne_Warspoils/Mesh/SpartanShield.SpartanShield'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> OffhandMeshObject(TEXT("StaticMesh'/Game/VFX/sphere.sphere'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_SpartanShield.WeaponIcon_SpartanShield'"));
	ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_SpartanShield-small.WeaponIcon_SpartanShield-small'"));


	// Set Default Objects

	Name = EMasterGearList::GL_SpartanShield;
	NameText = LOCTEXT("SpartanShieldName", "Spartan Shield");
	Type = EMasterGearTypes::GT_Shield;
	TypeText = LOCTEXT("SpartanShieldType", "Shield");
	Description = "An inscription on the back reads: 'Return with it, or carried on it'.";
	Price = 15000;
	MPCost = 0.0f;
	ATK = 25.0f;
	DEF = 25.0f;
	SPD = 10.0f;
	HP = 250.0f;
	MP = 50.0f;
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_WeaponSkeletalMesh = SkeletalMeshObject.Object;
	SM_WeaponStaticMesh = StaticMeshObject.Object;
	SM_WeaponOffhandMesh = StaticMeshObject.Object;

	// Set Mesh
	WeaponSkeletalMesh->SetSkeletalMesh(SK_WeaponSkeletalMesh);
	WeaponStaticMesh->SetStaticMesh(SM_WeaponStaticMesh);
	WeaponStaticMesh->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f)); // Scale correction
	WeaponOffhandMesh->SetStaticMesh(SM_WeaponOffhandMesh);

	//WeaponStaticMesh->SetVisibility(true);
	//SwordCollider->SetBoxExtent(FVector(5.0f, 5.0f, 25.0f));
	//SwordCollider->SetRelativeLocation(FVector(0.0f, 0.0f, 5.0f));
}

// Called when the game starts or when spawned
void ASpartanShield::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &ASpartanShield::BindWeapon);
}

// Custom code when binding
void ASpartanShield::BindWeapon()
{
	// If this weapon was bound while IsShown is true, set the weapon visible
	if (IsShown)
	{
		ShowWeapon(false, true, false);
	}
}

#undef LOCTEXT_NAMESPACE
