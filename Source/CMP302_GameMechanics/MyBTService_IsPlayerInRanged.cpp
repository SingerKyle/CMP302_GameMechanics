// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_IsPlayerInRanged.h"
#include "Enemy_AIController.h"
#include "MyEnemy.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseCharacter.h"

UMyBTService_IsPlayerInRanged::UMyBTService_IsPlayerInRanged()
{
	rangedRange = 2000.0f;
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("is player in ranged range?");
}

void UMyBTService_IsPlayerInRanged::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get enemy and controller
	auto const* const controller = Cast<AEnemy_AIController>(OwnerComp.GetAIOwner());
	auto enemy = Cast<AMyEnemy>(controller->GetPawn());

	// get player character
	auto const* const earthbender = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// write true of false to blackboard variable based on player position and enemy position
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), enemy->GetDistanceTo(earthbender) <= rangedRange && enemy->getManaFromBase());
}
