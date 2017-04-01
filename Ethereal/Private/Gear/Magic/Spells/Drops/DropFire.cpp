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
#include "DropFire.h"


// Sets default values
ADropFire::ADropFire(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates a scene component and sets it as the root
	Root = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	RootComponent = Root;
	Root->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
}

// Called when the game starts or when spawned
void ADropFire::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ADropFire::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ADropFire::Start_Fire_Implementation(AEtherealPlayerMaster* Caster)
{

}
