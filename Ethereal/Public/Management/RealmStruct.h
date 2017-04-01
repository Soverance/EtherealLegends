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

#include "Realms.h"
#include "RealmStruct.generated.h"

USTRUCT(BlueprintType)
struct FRealmStruct
{
	GENERATED_USTRUCT_BODY()

	// Realm Enum
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RealmData)
	ERealms Realm;

	// Realm Name used for legible display
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RealmData)
	FText NameText;

	// Actual Map Name used for Streaming
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RealmData)
	FName MapName;

	// Whether or not this level is currently LOCKED
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RealmData)
	bool Locked;

	// Recommended Player Level for this Realm
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RealmData)
	int32 RecLevel;

	// Realm Description
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RealmData)
	FText Description;

	// List Icon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RealmData)
	UTexture2D* ListIcon;

	// Realm Preview Art
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RealmData)
	UTexture2D* RealmPreview;
};
