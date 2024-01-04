// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_RandomPosition.h"

#include "Enemy_AIController.h"
#include "NavigationSystem.h"

UMyBTTask_RandomPosition::UMyBTTask_RandomPosition(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Generate Random Position in nav zone";
}

EBTNodeResult::Type UMyBTTask_RandomPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get AI controller owner to variable from tree
	if (AEnemy_AIController* const owner = Cast<AEnemy_AIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const enemy = owner->GetPawn())
		{
			// get NPC location from controller for start point of range
			auto const startPos = enemy->GetActorLocation();

			// generate random location using navmesh
			if (auto* const navMesh = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation newPos;
				// sets a random position in navmesh from the start position in range set.
				if (navMesh->GetRandomPointInNavigableRadius(startPos, searchRange, newPos))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), newPos.Location);
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
