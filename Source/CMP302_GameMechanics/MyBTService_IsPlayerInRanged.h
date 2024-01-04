// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTService_IsPlayerInRanged.generated.h"

/**
 * 
 */
UCLASS()
class CMP302_GAMEMECHANICS_API UMyBTService_IsPlayerInRanged : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTService_IsPlayerInRanged();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true)) float rangedRange;
};
