// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTService_isPlayerinMeleeRange.generated.h"

/**
 *  Class based on Based on class from Youtube video "UE5 C++ AI Series" by MrCxx: https://www.youtube.com/watch?v=Wrtk2k-l0xw&list=PLWUvrI0mg8VKTJWKqsDn_xyZfD3f7Xye-&index=18
 */
UCLASS()
class CMP302_GAMEMECHANICS_API UMyBTService_isPlayerinMeleeRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTService_isPlayerinMeleeRange();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true)) float meleeRange;
};
