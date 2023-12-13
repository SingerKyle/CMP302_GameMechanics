// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/TimelineComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Math/UnrealMathUtility.h"
#include "MyRock.generated.h"

class UCurveFloat;

UCLASS()
class CMP302_GAMEMECHANICS_API AMyRock : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyRock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Function that initializes the projectile's velocity in the shoot direction.
	void FireInDirection(const FVector& ShootDirection);

	// Sphere collision component.
	UPROPERTY(VisibleAnywhere, Category = Projectile) USphereComponent* CollisionComponent;
	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement) UProjectileMovementComponent* RockMovementComponent;
	// Projectile mesh
	UPROPERTY(VisibleAnywhere, Category = Projectile) UStaticMeshComponent* RockMeshComponent;
	// Projectile material
	UPROPERTY(VisibleAnywhere, Category = Movement) UMaterialInstanceDynamic* RockMaterialInstance;
	//Array of Static Meshes
	UPROPERTY(EditAnywhere, Category = Rock) TArray<UStaticMesh*> RockMeshes;
	bool atHeight = false;
};