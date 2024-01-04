// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_RangedAttack.h"

UMyBTTask_RangedAttack::UMyBTTask_RangedAttack()
{
    NodeName = TEXT("Ranged Attack");
}

EBTNodeResult::Type UMyBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // if the enemy isn't in melee range, can't attack so return
    auto const outOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
    if (outOfRange)
    {
        // finish task
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }
    // if enemy is in range, attack
    auto const* const controller = OwnerComp.GetAIOwner();
    auto* const enemy = Cast<AMyEnemy>(controller->GetPawn());

    // if NPC supports combat interface call function for melee:
    if (auto* const icombat = Cast<IMyCombatInterface>(enemy))
    {
        if (montageFinished(enemy))
        {
            icombat->Execute_rangedAttack(enemy);
        }
    }

    // Finish task and return
    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Type();
}

bool UMyBTTask_RangedAttack::montageFinished(AMyEnemy* const enemy)
{
    return enemy->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(enemy->getAttackMontage());
}
