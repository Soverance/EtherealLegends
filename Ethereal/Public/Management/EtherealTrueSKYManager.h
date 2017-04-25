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

#include "GameFramework/Actor.h"
#include "Realms.h"
#include "EtherealTrueSKYManager.generated.h"

//////////////////
// THE TRUESKY PLUGIN HAS BEEN DEPRECATED FROM ETHEREAL LEGENDS AS OF VERSION 1.2.1
//////////////////

UCLASS()
class ETHEREAL_API AEtherealTrueSKYManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEtherealTrueSKYManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Time of Day
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	float TimeOfDay;
	
	// How fast time passes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	float ClockSpeed;

	// Whether or not time should pass
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	bool PassTime;

	// trueSKY sequence actor
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	//ATrueSkySequenceActor SequenceActor;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Sequence)
	void SetSequence(ERealms Realm);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Sequence)
	void ConfigureSequence(float Brightness, float StartTime, bool RunClock, bool Visible);
};
