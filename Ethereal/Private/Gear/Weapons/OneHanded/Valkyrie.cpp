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
#include "Valkyrie.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AValkyrie::AValkyrie(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshObject(TEXT("SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Dual_Blade/Dual_Blade_Tech/SK_Valkyrie.SK_Valkyrie'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObject(TEXT("StaticMesh'/Game/VFX/sphere.sphere'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> OffhandMeshObject(TEXT("StaticMesh'/Game/VFX/sphere.sphere'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_Valkyrie.WeaponIcon_Valkyrie'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/WeaponIcon_Valkyrie-small.WeaponIcon_Valkyrie-small'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AuraParticleObject(TEXT("ParticleSystem'/Game/ElementalSword/ParticleSystem/PS_ValkyrieAura.PS_ValkyrieAura'"));

	// Set Default Objects
	Name = EMasterGearList::GL_Valkyrie;
	NameText = LOCTEXT("ValkyrieName", "Valkyrie");
	Type = EMasterGearTypes::GT_OneHanded;
	TypeText = LOCTEXT("ValkyrieType", "One-Handed");
	Description = "They say only God can judge them now - but they've never met me.";
	Price = 60000;
	MPCost = 0.0f;
	ATK = 50.0f;
	DEF = 50.0f;
	SPD = 25.0f;
	HP = 500.0f;
	MP = 250.0f;
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_WeaponSkeletalMesh = SkeletalMeshObject.Object;
	SM_WeaponStaticMesh = StaticMeshObject.Object;
	SM_WeaponOffhandMesh = StaticMeshObject.Object;
	P_AuraFX = AuraParticleObject.Object;

	// Set Mesh
	WeaponSkeletalMesh->SetSkeletalMesh(SK_WeaponSkeletalMesh);
	WeaponSkeletalMesh->SetRelativeLocation(FVector(0, 0, 10));
	WeaponSkeletalMesh->SetRelativeRotation(FRotator(0, 180, 0));
	WeaponSkeletalMesh->SetRelativeScale3D(FVector(1, 1, 1.4f));
	WeaponStaticMesh->SetStaticMesh(SM_WeaponStaticMesh);
	WeaponOffhandMesh->SetStaticMesh(SM_WeaponOffhandMesh);

	SwordCollider->SetupAttachment(WeaponSkeletalMesh);
	SwordCollider->SetBoxExtent(FVector(10.0f, 10.0f, 60.0f));
	SwordCollider->SetRelativeLocation(FVector(0.0f, 0.0f, 55.0f));

	// Aura Effect 
	AuraFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("AuraFX"));
	AuraFX->SetupAttachment(WeaponSkeletalMesh);
	AuraFX->Template = P_AuraFX;
	AuraFX->bAutoActivate = false;
	AuraFX->SetRelativeLocation(FVector(0, 0, 0));
	AuraFX->SetRelativeRotation(FRotator(0, 0, 0));
	AuraFX->SetRelativeScale3D(FVector(1, 1, 1));
}

// Called when the game starts or when spawned
void AValkyrie::BeginPlay()
{
	Super::BeginPlay();

	// Bind this function to the event dispatcher for Bind Gear
	OnBindGear.AddDynamic(this, &AValkyrie::BindWeapon);
	//OnRemoveGear.AddDynamic(this, &AValkyrie::RemoveWeapon);
}

// Custom code when binding
void AValkyrie::BindWeapon()
{
	// If this weapon was bound while IsShown is true, set the weapon visible
	if (IsShown)
	{
		ShowWeapon(true, false, false);
		AuraFX->Activate();
	}
}

// Custom code when binding
void AValkyrie::RemoveWeapon()
{
	//Super::RemoveWeapon();
	HideWeapon();
	AuraFX->Deactivate();
}

#undef LOCTEXT_NAMESPACE
