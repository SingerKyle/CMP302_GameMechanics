// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "MyBTTask_MeleeAttack.generated.h"

/**
 * Class based on Based on class from Youtube video "UE5 C++ AI Series" by MrCxx: https://www.youtube.com/watch?v=Wrtk2k-l0xw&list=PLWUvrI0mg8VKTJWKqsDn_xyZfD3f7Xye-&index=18
 */
UCLASS()
class CMP302_GAMEMECHANICS_API UMyBTTask_MeleeAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTTask_MeleeAttack();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	bool montageFinished(AMyEnemy* const enemy);
};
