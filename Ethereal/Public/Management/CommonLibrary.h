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

#include "Gear/MasterGearList.h"
#include "CommonLibrary.generated.h"

UCLASS()
class ETHEREAL_API UCommonLibrary : public UObject
{
	GENERATED_BODY()

public:

	UCommonLibrary();

	// Spawn an Actor into a specified level
	UFUNCTION(BlueprintCallable, Category = Default, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static AActor* SpawnActorIntoLevel(UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, FName Level = NAME_None, FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator, bool SpawnEvenIfColliding = true);
	
	// Spawns a new Gear item, based on the Name
	UFUNCTION(BlueprintCallable, Category = Inventory)
	static AEtherealGearMaster* CreateGear(UObject* GearOwner, EMasterGearList ItemToCreate, FName MapName, FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator);

	// Spawn a Blueprint actor
	static FORCEINLINE AActor* SpawnBP(
		UWorld*         TheWorld,
		UClass*         TheBP,
		const FVector&  Loc,
		const FRotator& Rot,
		const bool      bNoCollisionFail = true,
		AActor*         Owner = NULL,
		APawn*          Instigator = NULL
		) {
		if (!TheWorld) return NULL;
		if (!TheBP) return NULL;

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.Owner = Owner;
		SpawnInfo.Instigator = Instigator;
		SpawnInfo.bDeferConstruction = false;

		return TheWorld->SpawnActor<AActor>(TheBP, Loc, Rot, SpawnInfo);
	}

	// Configure Skeletal Meshes
	static FORCEINLINE void SetupSKComponentsWithCollision(USkeletalMeshComponent* Comp)
	{
		if (!Comp) return;

		Comp->bOwnerNoSee = false;
		Comp->bCastDynamicShadow = true;
		Comp->CastShadow = true;
		Comp->BodyInstance.SetObjectType(ECC_WorldDynamic);
		Comp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Comp->BodyInstance.SetResponseToAllChannels(ECR_Ignore);
		Comp->SetVisibility(false);
		Comp->SetHiddenInGame(false);
		Comp->bReceivesDecals = false;
	}

	// Configure Static Meshes
	static FORCEINLINE void SetupSMComponentsWithCollision(UStaticMeshComponent* Comp)
	{
		if (!Comp) return;

		Comp->bOwnerNoSee = false;
		Comp->bCastDynamicShadow = true;
		Comp->CastShadow = true;
		Comp->BodyInstance.SetObjectType(ECC_WorldDynamic);
		Comp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Comp->BodyInstance.SetResponseToAllChannels(ECR_Ignore);
		Comp->SetHiddenInGame(false);
		Comp->bReceivesDecals = false;
	}

	// Get Float as Text with Precision
	static FORCEINLINE FText GetFloatAsTextWithPrecision(float TheFloat, int32 Precision, bool IncludeLeadingZero = true)
	{
		FNumberFormattingOptions NumberFormat;
		NumberFormat.MinimumIntegralDigits = (IncludeLeadingZero) ? 1 : 0;
		NumberFormat.MaximumIntegralDigits = 10000;
		NumberFormat.MinimumFractionalDigits = Precision;
		NumberFormat.MaximumFractionalDigits = Precision;
		return FText::AsNumber(TheFloat, &NumberFormat);
	}

	// Get Float As String With Precision
	static FORCEINLINE FString GetFloatAsStringWithPrecision(float TheFloat, int32 Precision, bool IncludeLeadingZero = true)
	{
		FNumberFormattingOptions NumberFormat;					//Text.h
		NumberFormat.MinimumIntegralDigits = (IncludeLeadingZero) ? 1 : 0;
		NumberFormat.MaximumIntegralDigits = 10000;
		NumberFormat.MinimumFractionalDigits = Precision;
		NumberFormat.MaximumFractionalDigits = Precision;
		return FText::AsNumber(TheFloat, &NumberFormat).ToString();
	}
};
