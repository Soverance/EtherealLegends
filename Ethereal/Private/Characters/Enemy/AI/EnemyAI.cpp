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
#include "EnemyAI.h"

AEnemyAI::AEnemyAI()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComponent"));
}

void AEnemyAI::Possess(APawn *InPawn)
{
	Super::Possess(InPawn);

	AEtherealEnemyMaster* Enemy = Cast<AEtherealEnemyMaster>(InPawn);
	
	if (Enemy && Enemy->EnemyBehavior)
	{
		BlackboardComp->InitializeBlackboard(*Enemy->EnemyBehavior->BlackboardAsset);  // Init Blackboard, dereference the Blackboard asset
		PlayerKeyID = BlackboardComp->GetKeyID("Target");  // Set KeyID

		BehaviorComp->StartTree(*Enemy->EnemyBehavior); // start tree and dereference the behavior
	}
}
