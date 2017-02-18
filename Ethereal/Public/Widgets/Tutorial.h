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

#include "Blueprint/UserWidget.h"
#include "NPCs/Characters/Gatekeeper.h"
#include "Tutorial.generated.h"

UCLASS()
class ETHEREAL_API UTutorial : public UUserWidget
{
	GENERATED_BODY()
	
public:

	// Gatekeeper Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	AGatekeeper* Gatekeeper;

	// Initiates the tutorial, giving the player default items. Called when you first interact with the Gatekeeper NPC
	UFUNCTION(BlueprintCallable, Category = Default)
	void FirstContact();

	// Bind the Action Inputs of the PlayerController to functions in this widget
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Widgets)
	void BindActions();

	// Tutorial Index :  0 - Convo00,  1 - Convo01 to Convo02,   2 - Convo03 to Convo 04,  3 - Convo05,  4 - Convo06
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	int32 TutorialIndex;

	// Whether this widget is usable or not
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	bool IsActive;

	///////////////////////////
	// TUTORIAL SECTION 0
	// 
	// Section 0 is basically an error message, telling you to speak with the Gatekeeper NPC before venturing into the desert.

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Widgets)
	void ShowConversation_00();

	///////////////////////////
	// TUTORIAL SECTION 1
	// 
	// Section 1 contains a small conversation with Prodigy, the Gatekeeper, where he'll give you basic weapons.

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Widgets)
	void ShowConversation_01();

	// Gives the Tutorial items to the player
	UFUNCTION(BlueprintCallable, Category = Tutorial)
	void GiveDefaultItems();

	// Gives the player the first item
	UFUNCTION(BlueprintCallable, Category = Tutorial)
	void GiveItem1();

	// Gives the player the second item
	UFUNCTION(BlueprintCallable, Category = Tutorial)
	void GiveItem2();

	// Skips to Prodigy's "Call to Action"... which tells the player to defeat the skeleton king before Prod will open the gate.
	// this only gets called if the player quit the application without completing the tutorial
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Tutorial)
	void SkipTo_Conversation03();

	// Skips to Prodigy's "Congratulations" speech, but skips the part where he awards you anything.
	// this only happens if the player has already completed the tutorial when speaking with prodigy
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Tutorial)
	void SkipTo_Conversation07();

	///////////////////////////
	// TUTORIAL SECTION 2
	// 
	// Section 2 reviews the process of binding equipment and magic spells.

	// Tutorial Panel Conversation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Widgets)
	void ShowConversation_02();

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph1;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph2;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph3;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph4;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph5;

	///////////////////////////
	// TUTORIAL SECTION 4
	// 
	// Section 4 reviews the basics of combat.

	// Tutorial Panel Conversation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Widgets)
	void ShowConversation_04();

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph6;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph7;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph8;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph9;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph10;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph11;

	///////////////////////////
	// TUTORIAL SECTION 5
	// 
	// Section 5 reviews the usage of consumable items.

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph12;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph13;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph14;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph15;

	// Tutorial Panel Conversation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Widgets)
	void ShowConversation_05();

	///////////////////////////
	// TUTORIAL SECTION 6
	// 
	// Section 6 reviews the usage of Magic.

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph16;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph17;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph18;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph19;

	// Tutorial Panel Conversation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Widgets)
	void ShowConversation_06();

	///////////////////////////
	// TUTORIAL SECTION 7
	// 
	// Section 7 congratulates the player for completing the tutorial, gives an achievement, and permanently unlocks the gate.

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph20;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph21;

	// Tutorial Panel Conversation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Widgets)
	void ShowConversation_07();

	///////////////////////////
	// TUTORIAL SECTION 8
	// 
	// Section 8 gives you an overview of weapon modes, since you were just rewarded a weapon.
	// This is the first opportunity you have to equip a second weapon.

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph22;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph23;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph24;

	// Informational tutorial text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	FText Paragraph25;

	// Tutorial Panel Conversation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Widgets)
	void ShowConversation_08();
};
