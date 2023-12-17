// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/StaticMeshActor.h"
#include "AIController.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "AIModule/Classes/Tasks/AITask_MoveTo.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "AbilityClone.generated.h"

UCLASS()
class CMP302_GAMEMECHANICS_API AAbilityClone : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAbilityClone();

	// First-Person Arms
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) USkeletalMeshComponent* CloneBody;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) UCapsuleComponent* CollisionCapsule;
	UPROPERTY(VisibleDefaultsOnly, Category = Animation) UAnimBlueprint* animation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY() UAITask_MoveTo* CloneMove;
	UPROPERTY() class AAIController* AIController;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// handles backward and forward movement
	UFUNCTION() void MoveForward(float val);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
