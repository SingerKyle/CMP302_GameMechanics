// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_GetPlayerPosition.h"

#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UMyBTTask_GetPlayerPosition::UMyBTTask_GetPlayerPosition(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Get Player Position";
}

EBTNodeResult::Type UMyBTTask_GetPlayerPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		// Use player position as origin point
		auto const PlayerLocation = Player->GetActorLocation();
		if (Spotted) // if the enemy can't see the player in their eyeline they go to a random point near the player
		{
			FNavLocation newPos;

			// get navmesh
			if (auto* const navMesh = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				// Generate random position near player
				if (navMesh->GetRandomPointInNavigableRadius(PlayerLocation, searchRange, newPos))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), newPos.Location);
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
		else // if the enemy can see the player in their eyeline
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
			
		}
	}

	return EBTNodeResult::Failed;
}
