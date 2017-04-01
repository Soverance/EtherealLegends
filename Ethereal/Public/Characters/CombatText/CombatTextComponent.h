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

#include "Components/ActorComponent.h"
#include "CombatEffectStruct.h"
#include "CombatTextTypes.h"
#include "VisualEffect.h"
#include "CombatTextWidget.h"
#include "CombatTextComponent.generated.h"

UCLASS(Blueprintable)
class ETHEREAL_API UCombatTextComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatTextComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Combat Text Widget.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TSubclassOf<UUserWidget> W_CombatTextWidget;
	UCombatTextWidget* CombatTextWidget;
	
	// Current Effects Array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatusEffects)
	TArray<AVisualEffect*> CurrentEffects;

	// Removes the effect duration during tick.
	UFUNCTION(BlueprintCallable, Category = StatusEffects)
	FCombatEffectStruct RemoveEffectDurationTick(FCombatEffectStruct CombatEffect, float TickAmount);

	// Updates the effect duration.
	UFUNCTION(BlueprintCallable, Category = StatusEffects)
	FCombatEffectStruct UpdateEffectDuration(FCombatEffectStruct CombatEffect, float Duration);

	// Removes the current effect
	UFUNCTION(BlueprintCallable, Category = StatusEffects)
	void RemoveCurrentEffect(AVisualEffect* Effect);

	// Displays the combat text on screen
	UFUNCTION(BlueprintCallable, Category = StatusEffects)
	void ShowCombatText(ECombatTextTypes Type, FText Text);

	// Adds the Status Effect
	UFUNCTION(BlueprintCallable, Category = StatusEffects)
	void ApplyStatusEffect(FCombatEffectStruct CombatEffect);

	// Removes the Status Effect
	UFUNCTION(BlueprintCallable, Category = StatusEffects)
	void RemoveStatusEffect(FCombatEffectStruct CombatEffect);

	// Displays the combat text on screen
	UFUNCTION(BlueprintCallable, Category = StatusEffects)
	void AddCurrentEffect(FCombatEffectStruct CombatEffect);

	// Checks CurrentEffects for the specified effect
	UFUNCTION(BlueprintCallable, Category = StatusEffects)
	AVisualEffect* CheckCurrentEffects(FName Name, bool& HasEffect, AVisualEffect* VisualEffect);

	// Displays the combat text on scree
	UFUNCTION(BlueprintCallable, Category = StatusEffects)
	void UpdateCurrentEffect(AVisualEffect* Effect, float Duration);
};
