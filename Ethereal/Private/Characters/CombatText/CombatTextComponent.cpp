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

#include "Ethereal.h"
#include "CombatTextComponent.h"

#define LOCTEXT_NAMESPACE "EtherealText"

// Sets default values for this component's properties
UCombatTextComponent::UCombatTextComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> Widget(TEXT("/Game/CombatText/UI/Blueprints/CombatText"));

	W_CombatTextWidget = Widget.Class;
}


// Called when the game starts
void UCombatTextComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UCombatTextComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	for (AVisualEffect* Effect : CurrentEffects)  // scan the current effects...
	{
		// Remove Effects after their duration completes
		FCombatEffectStruct CurrentEffect = RemoveEffectDurationTick(Effect->CombatEffect, 0.1f);

		if (CurrentEffect.Duration < 0)
		{

		}
		else
		{
			Effect->CombatEffect = CurrentEffect; // set the new current effect
		}
	}

	// Only tick if we have effects
	if (CurrentEffects.Num() <= 0)
	{
		SetComponentTickEnabled(false);  // disable tick
	}
}

// Removes the effect duration during tick
FCombatEffectStruct UCombatTextComponent::RemoveEffectDurationTick(FCombatEffectStruct CombatEffect, float TickAmount)
{
	float DurationModifier = CombatEffect.Duration - TickAmount;

	FCombatEffectStruct NewEffect;

	NewEffect.Name = CombatEffect.Name;
	NewEffect.Text = CombatEffect.Text;
	NewEffect.Icon = CombatEffect.Icon;
	NewEffect.Effect = CombatEffect.Effect;
	NewEffect.Duration = DurationModifier;

	return NewEffect;
}

// Updates the effect duration
FCombatEffectStruct UCombatTextComponent::UpdateEffectDuration(FCombatEffectStruct CombatEffect, float Duration)
{
	FCombatEffectStruct NewEffect;

	NewEffect.Name = CombatEffect.Name;
	NewEffect.Text = CombatEffect.Text;
	NewEffect.Icon = CombatEffect.Icon;
	NewEffect.Effect = CombatEffect.Effect;
	NewEffect.Duration = Duration;

	return NewEffect;
}

// removes the current effect
void UCombatTextComponent::RemoveCurrentEffect(AVisualEffect* Effect)
{
	FFormatNamedArguments Arguments;
	Arguments.Add(TEXT("DisplayText"), Effect->CombatEffect.Text);
	FText NewText = FText::Format(LOCTEXT("RemoveStatusText", "- {DisplayText}"), Arguments);
	ShowCombatText(ECombatTextTypes::TT_Text, NewText);

	CurrentEffects.Remove(Effect);
	Effect->Destroy();
}

// displays the combat effect text
void UCombatTextComponent::ShowCombatText(ECombatTextTypes Type, FText Text)
{
	CombatTextWidget = CreateWidget<UCombatTextWidget>(GetWorld(), W_CombatTextWidget);
	CombatTextWidget->ActorLocation = GetOwner()->GetActorLocation() + FVector(0, 0, 10);
	CombatTextWidget->CombatTextType = Type;
	CombatTextWidget->CombatText = Text;
	CombatTextWidget->AddToViewport();
}

// Apply status effects
void UCombatTextComponent::ApplyStatusEffect(FCombatEffectStruct CombatEffect)
{
	bool HasEffect = false;
	AVisualEffect* VisualEffect = nullptr;

	VisualEffect = CheckCurrentEffects(CombatEffect.Name, HasEffect, VisualEffect); // check if the effect is already applied and if it should have an effect on the player

	if (HasEffect)
	{
		UpdateCurrentEffect(VisualEffect, CombatEffect.Duration); // effect already exists, so update it with a new duration
	}
	else
	{
		AddCurrentEffect(CombatEffect);  // add effect
		SetComponentTickEnabled(true);  // enable tick
	}

	FFormatNamedArguments Arguments;
	Arguments.Add(TEXT("DisplayText"), CombatEffect.Text);
	FText NewText = FText::Format(LOCTEXT("ApplyStatusText", "+ {DisplayText}"), Arguments);
	ShowCombatText(ECombatTextTypes::TT_Text, NewText);  // show text on screen
}

// Remove status effects
void UCombatTextComponent::RemoveStatusEffect(FCombatEffectStruct CombatEffect)
{
	if (CurrentEffects.Num() > 0)
	{
		for (AVisualEffect* Effect : CurrentEffects)  // scan the current effects...
		{
			if (CombatEffect.Name == Effect->CombatEffect.Name)  // If the name matches
			{
				RemoveCurrentEffect(Effect);  // remove effect

				break;  // stop iterating if an effect was successfully removed.
			}
		}
	}	
}

// Add the Effect
void UCombatTextComponent::AddCurrentEffect(FCombatEffectStruct CombatEffect)
{
	AVisualEffect* NewVisualEffect = GetWorld()->SpawnActor<AVisualEffect>();
	NewVisualEffect->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetIncludingScale, "PowerSocket");
	CurrentEffects.AddUnique(NewVisualEffect);
	NewVisualEffect->StartFX(CombatEffect);
}

AVisualEffect* UCombatTextComponent::CheckCurrentEffects(FName Name, bool& HasEffect, AVisualEffect* VisualEffect)
{
	int Index = 0;  // this is a hack for finding the index of a range based for loop...

	for (AVisualEffect* Effect : CurrentEffects)  // scan the current effects...
	{
		Index++;

		if (Name == Effect->CombatEffect.Name)
		{
			HasEffect = true;
			VisualEffect = Effect;
		}
	}

	return VisualEffect;
}

// Update the duration of the current effect
void UCombatTextComponent::UpdateCurrentEffect(AVisualEffect* Effect, float Duration)
{
	FCombatEffectStruct CombatEffect = Effect->CombatEffect;
	UpdateEffectDuration(CombatEffect, Duration);
}

#undef LOCTEXT_NAMESPACE
