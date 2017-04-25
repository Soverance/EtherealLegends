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

#include "NPCs/EtherealNPCMaster.h"
#include "SignetGate.generated.h"

UCLASS(Blueprintable)
class ETHEREAL_API ASignetGate : public AEtherealNPCMaster
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ASignetGate(const FObjectInitializer& ObjectInitializer);

	// BeginPlay Override
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Interact with this NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void Interact();

	// Interact Widget.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TSubclassOf<UUserWidget> W_InteractWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UUserWidget* InteractWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	bool GateIsOpen;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Signet)
	void DropGate();

	// Hide the Interact Widget for this NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void DisableInteractWidget();

	// What type of Signet Ring will open this gate
	// this value must be set in the editor, inside the corresponding blueprint instance for each gate.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	EMasterGearList SignetRingType;

	// The name of the Signet Ring.
	// this value must be set in the editor, inside the corresponding blueprint instance for each gate.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText SignetRingName;

	// Show the specified widget panel
	UFUNCTION(BlueprintCallable, Category = Default)
	void ShowPanel(int32 PanelIndex);

	// Opens the Gate
	UFUNCTION(BlueprintCallable, Category = Default)
	void OpenGate();
};
