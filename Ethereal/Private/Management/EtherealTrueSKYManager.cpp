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
#include "EtherealTrueSKYManager.h"

//////////////////
// THE TRUESKY PLUGIN HAS BEEN DEPRECATED FROM ETHEREAL LEGENDS AS OF VERSION 1.2.1
//////////////////

// Sets default values
AEtherealTrueSKYManager::AEtherealTrueSKYManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEtherealTrueSKYManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEtherealTrueSKYManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Set Sequence
void AEtherealTrueSKYManager::SetSequence_Implementation(ERealms Realm)
{

}

// Configure Sequence
void AEtherealTrueSKYManager::ConfigureSequence_Implementation(float Brightness, float StartTime, bool RunClock, bool Visible)
{

}
