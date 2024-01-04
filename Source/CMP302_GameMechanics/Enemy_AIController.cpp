// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_AIController.h"
#include "MyEarthbender.h"
#include "MyEnemy.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AEnemy_AIController::AEnemy_AIController(const FObjectInitializer& ObjectInitializer)
{
    initPerception();
}

void AEnemy_AIController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

    if (AMyEnemy* const enemy = Cast<AMyEnemy>(inPawn))
    {
        if (UBehaviorTree* const tree = enemy->getBehaviorTree())
        {
            UBlackboardComponent* b;
            UseBlackboard(tree->BlackboardAsset, b);
            Blackboard = b;
            RunBehaviorTree(tree);
        }
    }
}

void AEnemy_AIController::initPerception()
{
    sightSetup = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight setup"));
    if (sightSetup)
    {
        SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Setup")));
        sightSetup->SightRadius = 1500.0f;
        sightSetup->LoseSightRadius = sightSetup->SightRadius + 150.0f;
        sightSetup->PeripheralVisionAngleDegrees = 90.0f;
        sightSetup->SetMaxAge(5.0f);
        sightSetup->AutoSuccessRangeFromLastSeenLocation = 600.0f;
        sightSetup->DetectionByAffiliation.bDetectEnemies = true;
        sightSetup->DetectionByAffiliation.bDetectFriendlies = true;
        sightSetup->DetectionByAffiliation.bDetectNeutrals = true;

        GetPerceptionComponent()->SetDominantSense(*sightSetup->GetSenseImplementation());
        GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemy_AIController::onTargetInSight);
        GetPerceptionComponent()->ConfigureSense(*sightSetup);
    }
} 

void AEnemy_AIController::onTargetInSight(AActor* actor, FAIStimulus const Stimulus)
{
    if (auto* const player = Cast<AMyEarthbender>(actor))
    {
        GetBlackboardComponent()->SetValueAsBool("Player in Vision", Stimulus.WasSuccessfullySensed());
    }
    else if (auto* const clone = Cast<AAbilityClone>(actor))
    {
        GetBlackboardComponent()->SetValueAsBool("isClone", Stimulus.WasSuccessfullySensed());
    }
}
