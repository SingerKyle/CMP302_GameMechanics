// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_ChasePlayer.h"
#include "Enemy_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UMyBTTask_ChasePlayer::UMyBTTask_ChasePlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Chase Earthbender");
}

EBTNodeResult::Type UMyBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get target location from blackboard via AI controller
	if (auto* const controller = Cast<AEnemy_AIController>(OwnerComp.GetAIOwner()))
	{
		auto const playerPosition = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

		// move to player position
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, playerPosition);

		// Finish with success
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	// else failed
	return EBTNodeResult::Failed;
}
