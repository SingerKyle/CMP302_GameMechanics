// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/Engine.h"
#include "Components/CapsuleComponent.h"
#include "Components/TimelineComponent.h"
#include "MyRock.h"
#include "MyEarthbender.generated.h"
UCLASS()
class CMP302_GAMEMECHANICS_API AMyEarthbender : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyEarthbender();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Projectile class to spawn.
	UPROPERTY(EditAnywhere, Category = Projectile)
		TSubclassOf<class AMyRock> ProjectileClass;

public:
	// FPS camera.
	UPROPERTY(EditAnywhere) UCameraComponent* FPSCameraComponent;
	// TPS Camera
	UPROPERTY(EditAnywhere) UCameraComponent* TPSCameraComponent;
	// Perspective Change boolean
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool isFirstPerson = true;
	// First-Person Arms
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) USkeletalMeshComponent* FPSArms;
	// Gun muzzle offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) FVector MuzzleOffset;

	//AMyRock* SpawnedRock;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// handles backward and forward movement
	UFUNCTION() void MoveForward(float val);
	// Handles left and right movement
	UFUNCTION() void MoveRight(float val);
	// Sets jump active when key is pressed
	UFUNCTION() void StartJump();
	// deactivates jump when key is released.
	UFUNCTION() void StopJump();
	// Function for toggle perspective
	UFUNCTION() void ChangePerspective();
	// Function that handles spawning projectiles.
	UFUNCTION() void Fire();

};