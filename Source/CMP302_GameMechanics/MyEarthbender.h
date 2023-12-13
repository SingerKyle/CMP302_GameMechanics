// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/Engine.h"
#include "Components/CapsuleComponent.h"
#include "Components/TimelineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UCameraComponent* FPSCameraComponent;
	// TPS Camera
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UCameraComponent* TPSCameraComponent;
	// Perspective Change boolean
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool isFirstPerson = true;
	// First-Person Arms
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) USkeletalMeshComponent* FPSArms;
	// Gun muzzle offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) FVector MuzzleOffset;
	// Grab Range for hold function based off gravity gun lab.
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float GrabRange = 1500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float BoxExtentZ = -50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bIsHoldingRock = false;

	AMyRock* HeldRock;

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
	// Function that handles spawning and holding projectiles.
	UFUNCTION() void CreateRock();
	//UFUNCTION() void UpdateRock();
	UFUNCTION() void StopRock(); // For TimeLine
	// Function that handles shooting projectiles.
	UFUNCTION() void ThrowRock();

	UFUNCTION(BlueprintCallable)
		bool LineTraceMethod(FHitResult& OutHit);

};