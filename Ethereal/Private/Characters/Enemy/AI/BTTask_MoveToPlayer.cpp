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

#include "Ethereal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Characters/Enemy/EtherealEnemyMaster.h"
#include "Characters/Player/EtherealPlayerMaster.h"
#include "EnemyAI.h"
#include "BTTask_MoveToPlayer.h"

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAI* EnemyPC = Cast<AEnemyAI>(OwnerComp.GetAIOwner());  // get enemy AI instance

	AEtherealEnemyMaster* Enemy = Cast<AEtherealEnemyMaster>(EnemyPC->GetPawn()); // get the enemy pawn instance

	AEtherealPlayerMaster* Player = Cast<AEtherealPlayerMaster>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyPC->PlayerKeyID)); // Get target from blackboard
	
	if (Player)  // make sure player reference is valid
	{
		if (Enemy)  // make sure enemy reference is valid
		{
			if (Enemy->RunAI)  // Make sure enemy has been aggroed by the player
			{
				EPathFollowingRequestResult::Type MoveEnum = EnemyPC->MoveToActor(Player, Enemy->AcceptanceRadius, true, true, true, 0, true);  // move towards the player

				if (MoveEnum == EPathFollowingRequestResult::AlreadyAtGoal)
				{
					Enemy->OnReachedTarget.Broadcast();
				}

				return EBTNodeResult::Succeeded;
			}
			else
			{
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Enemy is not aggroed"));
				return EBTNodeResult::Failed;
			}
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("FAILED FINDING ENEMY REFERENCE"));
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("FAILED FINDING PLAYER REFERENCE"));
		return EBTNodeResult::Failed;
	}
	// This used to be fine, but I guess it's unused.
	// It got called out while compiling for PS4!
	//EBTNodeResult::Failed;
}

