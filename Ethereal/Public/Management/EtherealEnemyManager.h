// © 2014 - 2017 Soverance Studios
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

#include "GameFramework/Actor.h"
#include "Management/EnemyNode.h"
#include "EtherealEnemyManager.generated.h"

class AEtherealPlayerMaster;

UCLASS()
class ETHEREAL_API AEtherealEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEtherealEnemyManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Player Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	AEtherealPlayerMaster* Player;

	// Enemy Node Array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TArray<AEnemyNode*> EnemyNodes;

	// By default, enemies are spawned at the level specified on their Node.  Calling this function will adjust their level based on the player's level.
	// This function is generally used for New Game +, but it's also useful for enemies in Arcadia, since you return to that map often.
	UFUNCTION(BlueprintCallable, Category = Default)
	int32 GetAdjustedLevel();

	// Searches the world for EnemyNode instances, and spawns the enemies associated with them.
	UFUNCTION(BlueprintCallable, Category = Default)
	void SpawnAllNodes();	

	// Spawns the enemy at a specific node.
	UFUNCTION(BlueprintCallable, Category = Default)
	void SpawnNode(AEnemyNode* Node);

	// Destroys all enemies found in scene - used during loading screens when unloading a Realm.
	// I tried to get enemies to spawn inside their sublevels, so that this function would not be necessary  (see SpawnActorIntoLevel() inside CommonLibrary.cpp), however that does not seem to work correctly
	// so instead, this function is now called during loading to destroy all remaining enemies
	UFUNCTION(BlueprintCallable, Category = Default)
	void DestroyAllEnemies();
};
