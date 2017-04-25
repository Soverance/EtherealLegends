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

#pragma once

#include "Characters/Enemy/EnemyNames.h"
#include "GameFramework/Actor.h"
#include "EnemyNode.generated.h"

UCLASS()
class ETHEREAL_API AEnemyNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyNode(const FObjectInitializer& ObjectInitializer);

	//// Called when the game starts or when spawned
	//virtual void BeginPlay() override;
	//
	//// Called every frame
	//virtual void Tick( float DeltaSeconds ) override;

	// The name of the enemy to spawn at this node.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	EEnemyNames EnemyName;

	// The level of the enemy that spawns at this node.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	int32 EnemyLevel;

	// The root component for this actor.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	USceneComponent* Root;

	// The arrow component for this actor. It's here entirely so that designers can visually see the forward vector of this actor in the editor,
	// and thus determine the direction an enemy will be facing when spawned from this node
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bindings)
	UArrowComponent* Arrow;
	
};
