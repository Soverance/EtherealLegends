// © 2014 - 2016 Soverance Studios. All Rights Reserved.

#pragma once

#include "Gear/EtherealGearMaster.h"
#include "Magic_AnimTypes.h"
#include "Magic_TargetTypes.h"
#include "Magic_Master.generated.h"

/**
 * 
 */
UCLASS()
class ETHEREAL_API AMagic_Master : public AEtherealGearMaster
{
	GENERATED_BODY()

public:
		
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	UParticleSystem* ChargeFX;
};
