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
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Characters/Enemy/EtherealEnemyMaster.h"
#include "Characters/Player/EtherealPlayerMaster.h"
#include "EnemyAI.h"
#include "BTService_CheckForPlayer.h"

UBTService_CheckForPlayer::UBTService_CheckForPlayer()
{
	bCreateNodeInstance = true; // add ability to create instances of this service
}

void UBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AEnemyAI* EnemyPC = Cast<AEnemyAI>(OwnerComp.GetAIOwner());  // gets this enemy's AI Controller class

	if (EnemyPC)
	{
		AEtherealPlayerMaster* Player = Cast<AEtherealPlayerMaster>(GetWorld()->GetFirstPlayerController()->GetPawn()); // Search for the player

		if (Player)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyPC->PlayerKeyID, Player); // set Key ID to the player
		}
	}
}
