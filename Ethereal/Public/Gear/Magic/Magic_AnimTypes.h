// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#pragma once
#include "Magic_AnimTypes.generated.h"
/**
*
*/

UENUM(BlueprintType)
enum class EMagic_AnimTypes : uint8
{
	AT_None UMETA(DisplayName = "NONE"),
	AT_Dash UMETA(DisplayName = "Dash"),
	AT_Standard UMETA(DisplayName = "Standard"),
	AT_GroundUp UMETA(DisplayName = "Ground Up"),
	AT_TopDown UMETA(DisplayName = "Top Down"),
	AT_ForwardBlast UMETA(DisplayName = "Forward Blast"),
};