// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#pragma once
#include "Magic_TargetTypes.generated.h"
/**
*
*/

UENUM(BlueprintType)
enum class EMagic_TargetTypes : uint8
{
	AT_None UMETA(DisplayName = "Player"),
	AT_Dash UMETA(DisplayName = "Enemy"),
};
