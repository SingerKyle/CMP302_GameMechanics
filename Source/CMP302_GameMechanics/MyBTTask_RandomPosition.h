// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyBTTask_RandomPosition.generated.h"

/**
 * class is based on a similar class from youtube video: "UE5 C++ AI series" by MrCxx - https://www.youtube.com/watch?v=1g1nhuy-kAI&list=PLWUvrI0mg8VKTJWKqsDn_xyZfD3f7Xye-&index=4
 */
UCLASS()
class CMP302_GAMEMECHANICS_API UMyBTTask_RandomPosition : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UMyBTTask_RandomPosition(const FObjectInitializer& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category = "Enemy AI") float searchRange = 1500.0f;
};
