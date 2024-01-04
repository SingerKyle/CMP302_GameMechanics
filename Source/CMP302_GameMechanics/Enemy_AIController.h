// Fill out your copyright notice in the Description page of Project Settings.

// counteract circular dependency - forward declare
class AMyEnemy;

#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Enemy_AIController.generated.h"

UCLASS()
class CMP302_GAMEMECHANICS_API AEnemy_AIController : public AAIController
{
	GENERATED_BODY()
public:
	explicit AEnemy_AIController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* inPawn) override;

private:
	class UAISenseConfig_Sight* sightSetup;

	void initPerception();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTargetPerceptionInfoUpdated, AActor*, Actor, FAIStimulus, Stimulus);

	UPROPERTY()
	FOnTargetPerceptionInfoUpdated OnTargetPerceptionInfoUpdated;

	UFUNCTION() void onTargetInSight(AActor* actor, FAIStimulus const Stimulus);
};
