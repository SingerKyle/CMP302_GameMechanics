// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyBTTask_GetPlayerPosition.generated.h"

/**
 * Based on class from Youtube video "UE5 C++ AI Series" by MrCxx: https://www.youtube.com/watch?v=3Ic1-XyoGiU&list=PLWUvrI0mg8VKTJWKqsDn_xyZfD3f7Xye-&index=6
 * Changed by me for this project 
*/
UCLASS()
class CMP302_GAMEMECHANICS_API UMyBTTask_GetPlayerPosition : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	explicit UMyBTTask_GetPlayerPosition(const FObjectInitializer& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category = "Enemy AI") bool Spotted = false;
	UPROPERTY(EditAnywhere, Category = "Enemy AI") float searchRange = 150.0f;
};
