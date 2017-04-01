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

#include "Gear/EtherealGearMaster.h"
#include "Magic_AnimTypes.h"
#include "Magic_TargetTypes.h"
#include "Magic_Master.generated.h"

 // Event Dispatchers
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FQuitCharging);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoCast);

UCLASS()
class ETHEREAL_API AMagic_Master : public AEtherealGearMaster
{
	GENERATED_BODY()

public:

	AMagic_Master(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	// Event Dispatcher Stop Charging
	UPROPERTY(BlueprintAssignable, Category = "Dispatcher")
	FQuitCharging QuitCharging;

	// Event Dispatcher Stop Charging
	//UPROPERTY(BlueprintAssignable, Category = "Dispatcher")
	//FDoCast DoCast;

	/** Quit Charging. */
	UFUNCTION(BlueprintCallable, Category = Casting)
	void StopCharge();

	/** Charge Spell. */
	UFUNCTION(BlueprintCallable, Category = Casting)
	virtual void Charge();

	/** Cast Spell. */
	UFUNCTION(BlueprintCallable, Category = Casting)
	virtual void CastSpell();

	/** Start Casting. */
	//UFUNCTION(BlueprintCallable, Category = Casting)
	//void StartCast();
		
	/** Critical Multiplier, used for various things, but mostly for randomizing the output of a spell's effect, such as increasing Cure efficiency, or dealing critical damage from Thunder. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Multipliers)
	float CritMultiplier;
	
	/** Same as CritMultiplier, but specifically for affecting the player's SPD stat. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Multipliers)
	float HasteMultiplier;

	/** The duration, in seconds, that this spell will stay in effect. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Multipliers)
	float DefenseMultiplier;
	
	/** The duration, in seconds, that this spell will stay in effect. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timing)
	float Duration;

	/** How long this spell takes to cast. This variable takes some effort to adjust properly, as it's ultimate effectiveness is the result many different variables, generally based around the player's SPD stat. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timing)
	float CastTime;

	/** Whether or not this spell is charging. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool IsCharging;

	/** Whether or not this spell is casting. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool IsCasting;

	/** What type of animation to play when casting this spell. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	EMagic_AnimTypes AnimType;

	/** What kind of target must be active before this spell will cast. To ensure you can't cure/buff enemies, or cast damage spells on yourself. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	EMagic_TargetTypes TargetType;

	/** This emitter is active when this spell is in a charging state. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* ChargeFX;
	UParticleSystem* P_ChargeFX;

	// This emitter is active when this spell is cast.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* CastFX;
	UParticleSystem* P_CastFX;

	// Cast Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* CastAudio;
	USoundCue* S_CastAudio;
};
