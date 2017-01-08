// © 2014 - 2016 Soverance Studios
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

#include "EnemyNames.h"
#include "Perception/PawnSensingComponent.h"
#include "Characters/EtherealCharacterMaster.h"
#include "Characters/Player/EtherealPlayerMaster.h"
#include "Management/BattleTypes.h"
#include "Management/Realms.h"
#include "EtherealEnemyMaster.generated.h"

// Event Dispatchers
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReachedTarget);

UCLASS()
class ETHEREAL_API AEtherealEnemyMaster : public AEtherealCharacterMaster
{
	GENERATED_BODY()
	
public:

	AEtherealEnemyMaster(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// DEFAULTS

	// The name of this enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	EEnemyNames Name;

	// The name of this enemy as text, for display use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText NameText;

	// The Realm associated with this enemy (i.e. what map does he spawn in).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	ERealms Realm;

	// What type of battle this enemy initiates (standard, boss, or zhan)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	EBattleTypes BattleType;

	// Common Drop
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Drops)
	EMasterGearList CommonDrop;

	// Uncommon Drop
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Drops)
	EMasterGearList UncommonDrop;

	// Rare Drop
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Drops)
	EMasterGearList RareDrop;

	// Enemy's current target. will always be the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	AEtherealPlayerMaster* Target;

	// CONTROL STATES

	// Do an attack animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool IsAttacking;
	
	// Whether or not the enemy is in range of the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool InRange;

	// Whether or not the enemy is currently moving
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool IsMoving;

	// Whether or not the enemy has been aggroed by the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool IsAggroed;

	// BASE STATS

	// Enemy Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Level;

	// Enemy ATK value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float ATK;

	// Enemy DEF value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float DEF;

	// Enemy SPD value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float SPD;

	// Enemy Current HP value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float HP_Current;

	// Enemy Max HP value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float HP_Max;

	// The time this enemy will wait between taking turns
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float AttackDelay;

	// The damage output of this enemy. Used to calculate final damage taken by the player.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float DamageOutput;

	// COMPONENTS

	/** This emitter is active when the enemy is hit. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* HitFX;
	UParticleSystem* P_HitFX;

	/** This emitter is active when this enemy dies. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* DeathFX;
	UParticleSystem* P_DeathFX;

	/** Effect played when enemy vanishes after dying. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* DisappearFX;
	UParticleSystem* P_DisappearFX;

	// Disappear Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* DisappearAudio;
	USoundCue* S_DisappearAudio;

	// STANDARD FUNCTIONS

	// Sets the initial stats of the player, based on his level
	UFUNCTION(BlueprintCallable, Category = Stats)
	void SetBaseStats();

	// Sets the initial stats of the player, based on his level
	UFUNCTION(BlueprintCallable, Category = Stats)
	bool ForceHPCaps();

	// Sets the initial stats of the player, based on his level
	UFUNCTION(BlueprintCallable, Category = Combat)
	void EnemyTakeDamage(float DamageTaken);

	// Sets the initial stats of the player, based on his level
	UFUNCTION(BlueprintCallable, Category = Combat)
	float EnemyDealDamage(float BaseATK);

	// Sets the hit animation bool to false.  Without this, an enemy could wind up locked in the Hit anim state if a player lands successive hits too quickly.
	UFUNCTION(BlueprintCallable, Category = Stats)
	void StopHit();

	// Aggro the player. This function is called in Blueprint by the AI OnSeePawn event
	UFUNCTION(BlueprintCallable, Category = Combat)
	void Aggro(APawn* Pawn);

	// Deaggro the player. 
	UFUNCTION(BlueprintCallable, Category = Combat)
	void Deaggro();

	// Ends All Attack Rounds, allowing the enemy A.I. to once again begin searching for the player
	UFUNCTION(BlueprintCallable, Category = Default)
	void EndAttackRound();

	// DEATH FUNCTIONS

	// Event Dispatcher OnDeath
	UPROPERTY(BlueprintAssignable, Category = "Dispatcher")
	FDeath OnDeath;

	// Activate the Death sequence of this enemy
	UFUNCTION(BlueprintCallable, Category = Combat)
	void Death();

	// Activate the Final Death sequence of this enemy, destroying it. Boss enemies will spawn Zhan after this cycle.
	// This function is called at the end of an enemy's Death animation, and must be bound to an AnimNotify in editor
	UFUNCTION(BlueprintCallable, Category = Combat)
	void FinalDeath(bool ShouldDestroy, bool SpawnZhan);

	// Activate the Disappear sequence of this enemy
	UFUNCTION(BlueprintCallable, Category = Combat)
	void Disappear();

	// Spawns Zhan after a Boss dies. Should not be called by regular enemies.
	UFUNCTION(BlueprintCallable, Category = Combat)
	void SpawnZhan();

	// Destroys this enemy
	UFUNCTION(BlueprintCallable, Category = Combat)
	void DestroyEnemy();

	// A.I.

	// Pawn Sensing Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	UPawnSensingComponent* PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));

	// Behavior Tree
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	class UBehaviorTree* EnemyBehavior;

	// Allows the AI MoveToPlayer task to run. Setting this to true will cause the AI to move this Enemy towards the player, following the shortest route possible.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
	bool RunAI;

	// Run to Target
	UFUNCTION(BlueprintCallable, Category = Default)
	void RunToTarget();

	// Event Dispatcher ReachedTarget
	UPROPERTY(BlueprintAssignable, Category = "Dispatcher")
	FReachedTarget OnReachedTarget;

	// Event Dispatcher ReachedTarget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	float AcceptanceRadius;
};
