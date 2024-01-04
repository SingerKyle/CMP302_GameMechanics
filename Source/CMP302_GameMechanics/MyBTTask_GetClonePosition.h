// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_GetClonePosition.generated.h"

/**
 * 
 */
UCLASS()
class CMP302_GAMEMECHANICS_API UMyBTTask_GetClonePosition : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UMyBTTask_GetClonePosition(const FObjectInitializer& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category = "Enemy AI") bool Spotted = false;
	UPROPERTY(EditAnywhere, Category = "Enemy AI") float searchRange = 150.0f;
};
