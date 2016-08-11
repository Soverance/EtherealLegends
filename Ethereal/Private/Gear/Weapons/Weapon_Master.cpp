// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#include "Ethereal.h"
#include "Weapon_Master.h"

// SetVisible
void AWeapon_Master::SetVisible()
{
	if (IsVisible == true)
	{
		switch (Type)
		{
			case EMasterGearTypes::GT_None:
				break;
			case EMasterGearTypes::GT_OneHanded:
				break;
			case EMasterGearTypes::GT_TwoHanded:
				break;
			case EMasterGearTypes::GT_Ranged:
				break;
			case EMasterGearTypes::GT_CastingOrb:
				break;
			case EMasterGearTypes::GT_Theurgy:
				break;
			case EMasterGearTypes::GT_Necromancy:
				break;
			case EMasterGearTypes::GT_Support:
				break;
			case EMasterGearTypes::GT_Ancient:
				break;
			case EMasterGearTypes::GT_Shield:
				break;
			case EMasterGearTypes::GT_Ammo:
				break;
			case EMasterGearTypes::GT_Head:
				break;
			case EMasterGearTypes::GT_Cape:
				break;
			case EMasterGearTypes::GT_Body:
				break;
			case EMasterGearTypes::GT_Hands:
				break;
			case EMasterGearTypes::GT_Legs:
				break;
			case EMasterGearTypes::GT_Feet:
				break;
			case EMasterGearTypes::GT_Consumable:
				break;
			case EMasterGearTypes::GT_KeyItem:
				break;
			default:
				break;
		}
	}

	
}

AWeapon_Master::AWeapon_Master(const FObjectInitializer& ObjectInitializer)
{
	// Asset, Reference Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObject(TEXT("StaticMesh'/Game/Elemental/Environment/Throne_Warspoils/Mesh/IronSword.IronSword'"));

	SM_WeaponStaticMesh = StaticMeshObject.Object;

	// Create
	WeaponStaticMesh = ObjectInitializer.CreateDefaultSubobject < UStaticMeshComponent >(this, TEXT("Weapon Static Mesh"));

	// Set Mesh
	WeaponStaticMesh->SetStaticMesh(SM_WeaponStaticMesh);

	// Configure Mesh
	SetupSMComponentsWithCollision(WeaponStaticMesh);

	// Attachment
	WeaponStaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
}



