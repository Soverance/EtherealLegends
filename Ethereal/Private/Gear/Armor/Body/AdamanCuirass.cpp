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
#include "AdamanCuirass.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values
AAdamanCuirass::AAdamanCuirass(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Get Assets, References Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UTexture2D> LargeIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_AdamanCuirass.ArmorIcon_AdamanCuirass'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> SmallIconObject(TEXT("Texture2D'/Game/Blueprints/Widgets/UI-Images/Icons_Gear/ArmorIcon_AdamanCuirass-small.ArmorIcon_AdamanCuirass-small'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmorMeshObject(TEXT("SkeletalMesh'/Game/EtherealParty/Morgan/Clothes/AdamanArmor/AdamanCuirass/AdamanCuirass.AdamanCuirass'"));

	// Set Default Objects
	LargeIcon = LargeIconObject.Object;
	SmallIcon = SmallIconObject.Object;

	SK_ArmorMesh = ArmorMeshObject.Object;
	ArmorMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("ArmorMesh"));
	ArmorMesh->SetSkeletalMesh(SK_ArmorMesh);
	ArmorMesh->SetupAttachment(RootComponent);
	UCommonLibrary::SetupSKComponentsWithCollision(ArmorMesh);
	
	// Set Default Values
	Name = EMasterGearList::GL_AdamanCuirass;
	NameText = LOCTEXT("AdamanCuirassName", "Adaman Cuirass");
	Type = EMasterGearTypes::GT_Body;
	TypeText = LOCTEXT("AdamanCuirassType", "Body");
	Description = "Armor of Ethereal Knights.";
	Price = 9500;
	MPCost = 0;
	ATK = 2;
	DEF = 4;
	SPD = 2;
	HP = 30;
	MP = 10;
}

// Called when the game starts or when spawned
void AAdamanCuirass::BeginPlay()
{
	Super::BeginPlay();
}

#undef LOCTEXT_NAMESPACE
