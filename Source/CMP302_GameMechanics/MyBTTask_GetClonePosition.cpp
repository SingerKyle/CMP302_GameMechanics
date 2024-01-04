// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_GetClonePosition.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "AbilityClone.h"

UMyBTTask_GetClonePosition::UMyBTTask_GetClonePosition(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Get Clone Position";
}

EBTNodeResult::Type UMyBTTask_GetClonePosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get class we're searching for - clone
	AAbilityClone* clone = nullptr;

	// Get all actors of clone class
	TArray<AActor*> clones;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAbilityClone::StaticClass(), clones);

	// check not empty
	if (clones.IsEmpty())
	{
		return EBTNodeResult::Failed;
	}
	else
	{
		clone = Cast<AAbilityClone>(clones[0]);
	}

	if (clone)
	{
		// Use player position as origin point
		auto const PlayerLocation = clone->GetActorLocation();
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
