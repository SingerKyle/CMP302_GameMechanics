// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_ChasePlayer.generated.h"

/**
 * Class based on Based on class from Youtube video "UE5 C++ AI Series" by MrCxx: https://www.youtube.com/watch?v=Wrtk2k-l0xw&list=PLWUvrI0mg8VKTJWKqsDn_xyZfD3f7Xye-&index=18
 */
UCLASS()
class CMP302_GAMEMECHANICS_API UMyBTTask_ChasePlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UMyBTTask_ChasePlayer(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
