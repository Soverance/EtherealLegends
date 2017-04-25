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

#include "Engine/UserDefinedStruct.h"
#include "ActionStruct.generated.h"

USTRUCT(BlueprintType)
struct FActionStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	// The keys pressed to perform this action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActionData)
	TArray<FKey> Keys;

	// Action Name used for legible display
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActionData)
	FString Identifier;

	// Action Name used for legible display
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActionData)
	FText VisualName;
	
	// Whether or not to show this action in the menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActionData)
	bool ShowInMappingSettings;
};
