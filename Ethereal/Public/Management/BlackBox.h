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

#pragma once

#include "GameFramework/Actor.h"
#include "Realms.h"
#include "BlackBox.generated.h"

// Event Dispatchers
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFadeOut);

UCLASS()
class ETHEREAL_API ABlackBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackBox();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Event Dispatcher FadeOut
	UPROPERTY(BlueprintAssignable, Category = "Dispatcher")
	FFadeOut FadeOut;

	// True once a boss has been engaged inside a realm.  We don't want the player to have to go all the way back to the start if he dies during the boss fight.
	// Automatically set false during loading.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool HasEngagedBoss;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Position)
	void SetCharacterPosition_RealmStart(ERealms Realm);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Position)
	void SetCharacterPosition_RealmBoss(ERealms Realm);
};
