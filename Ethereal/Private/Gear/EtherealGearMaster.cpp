// © 2014 - 2016 Soverance Studios
// www.soverance.com

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
#include "Characters/Player/EtherealPlayerMaster.h"
#include "EtherealGearMaster.h"

// Sets default values
AEtherealGearMaster::AEtherealGearMaster()
{
	// Creates a scene component and sets it as the root
	Root = NewObject<USceneComponent>(this, TEXT("Root"));
	RootComponent = Root;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsBound = false;
}

// Called when the game starts or when spawned
void AEtherealGearMaster::BeginPlay()
{
	Super::BeginPlay();

	// Gets the Ethereal Player Master reference
	AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	OwnerReference = Cast<AEtherealPlayerMaster>(Player);

	if (OwnerReference)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Owner Reference in this Gear Item was successfully initialized from code.");
	}
}



