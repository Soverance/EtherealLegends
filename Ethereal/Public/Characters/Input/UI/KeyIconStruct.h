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
#include "KeyIconStruct.generated.h"

USTRUCT(BlueprintType)
struct FKeyIconStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	// The keys that correspond to these icons for each platform
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KeyData)
	TArray<FKey> Keys;

	// The Key Display Name to display on the Xbox platform
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KeyData)
	FText Text_Xbox;

	// The Icon to display on the Xbox platform for this key
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KeyData)
	UTexture2D* Icon_Xbox;

	// The Key Display Name to display on the PS4 platform
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KeyData)
	FText Text_PS4;

	// The Icon to display on the PS4 platform for this key
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KeyData)
	UTexture2D* Icon_PS4;

	// The Key Display Name to display on the Steam platform, including PC, Mac, and Linux
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KeyData)
	FText Text_Steam;

	// The Icon to display on the Steam platform for this key, including PC, Mac, and Linux
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KeyData)
	UTexture2D* Icon_Steam;
};
