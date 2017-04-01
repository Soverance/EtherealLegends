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

#include "Blueprint/UserWidget.h"
#include "Management/RealmStruct.h"
#include "RealmSelect.generated.h"

UCLASS()
class ETHEREAL_API URealmSelect : public UUserWidget
{
	GENERATED_BODY()	
	
public:

	URealmSelect(const FObjectInitializer& ObjectInitializer);

	// Realm Info Array
	// All Realms are locked until you progress through the game.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Realms)
	TArray<FRealmStruct> Realms;
	
	// Realm - Shiitake Temple
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Realms)
	FRealmStruct Shiitake;

	// Realm - Vulcan Shrine
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Realms)
	FRealmStruct Vulcan;

	// Realm - Boreal Core
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Realms)
	FRealmStruct Boreal;

	// Realm - Yggdrasil
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Realms)
	FRealmStruct Yggdrasil;

	// Realm - Empyrean Gardens
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Realms)
	FRealmStruct Empyrean;

	// Realm - Celestial Nexus
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Realms)
	FRealmStruct Celestial;
};
