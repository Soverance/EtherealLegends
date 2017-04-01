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

#include "GameFramework/SaveGame.h"
#include "ActionStruct.h"
#include "AxisStruct.h"
#include "EtherealSaveInput.generated.h"

UCLASS()
class ETHEREAL_API UEtherealSaveInput : public USaveGame
{
	GENERATED_BODY()
	
public:
	
	UEtherealSaveInput();

	// Save Slot Name
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;
	
	// The keys pressed to perform this action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActionData)
	TArray<FActionStruct> ActionInputs;

	// The keys pressed to perform this action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActionData)
	TArray<FAxisStruct> AxisInputs;

	// Current Platform Index - 0 = Xbox, 1 = PS4, 2 = KB+M
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Platform)
	int32 Platform;
};
