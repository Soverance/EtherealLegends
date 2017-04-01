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

#include "Animation/AnimInstance.h"
#include "EtherealPlayerAnim.generated.h"

UCLASS()
class ETHEREAL_API UEtherealPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:


	/////////////////////////
	// FLOATS

	// Movement Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floats)
	float Speed;

	// Move Forward
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floats)
	float MoveForward;

	// Move Right
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floats)
	float MoveRight;

	// Charge Rate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Floats)
	float ChargeRate;

	/////////////////////////
	// BOOLS
	
	// Death
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
	bool Death;

	// Hit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
	bool Hit;

	// Is In Air
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
	bool IsInAir;

	// Charge
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
	bool Charge;

	// Can Cast
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
	bool CanCast;

	// Cast
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
	bool Cast;

	// Blocking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
	bool Blocking;

	// Strafing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
	bool Strafing;

	// Can Fire Ranged Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
	bool CanFire;

	// Do Interact Anim
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
	bool DoInteractAnim;

	// Get Up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
	bool GetUp;

	// Attacking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
	bool Attacking;

	// Use Item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
	bool UseItem;

	// Do Flight
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
	bool DoFlight;

	// Take Fall Damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
	bool TakeFallDamage;

	// Reaction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
	bool React;
};
