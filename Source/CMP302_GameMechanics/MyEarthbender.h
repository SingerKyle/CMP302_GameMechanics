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
#include "AbilityClone.h"
#include "MyRock.h"
#include "MyRockArmour.h"
#include "BaseCharacter.h"
#include "MyHUD.h"
#include "MyEarthbender.generated.h"

class UCurveFloat;

UCLASS()
class CMP302_GAMEMECHANICS_API AMyEarthbender : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyEarthbender();

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
	// Power switch case
	UFUNCTION() void powerPick();
	// Function that handles spawning and holding projectiles.
	UFUNCTION() void CreateRock();
	//Function to give sand armour.
	UFUNCTION() void CreateArmour();
	//UFUNCTION() void UpdateRock();
	UFUNCTION() void createClone();
	// Function that handles shooting projectiles.
	UFUNCTION() void ThrowRock();
	// TAKE DAMAGE
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	// called when player dies
	void onDeath();
	// sets which ability to use
	UFUNCTION() void setPower(int num);
	UFUNCTION() void updateRock(float value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Projectile class to spawn.
	UPROPERTY(EditAnywhere, Category = Projectile)
		TSubclassOf<class AMyRock> ProjectileClass;
	// clone
	UPROPERTY(EditAnywhere, Category = clone)
		TSubclassOf<class AAbilityClone> CloneClass;

	// HUD
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMyHUD> HUDClass;

	FTimeline rockTimeline;
	UPROPERTY(EditAnywhere, Category = "TimeLine")
		UCurveFloat* rockCurveFloat;

	UPROPERTY()
		FVector startLocation;
	UPROPERTY()
		FVector endLocation;
	UPROPERTY(EditAnywhere, Category = "TimeLine")
		float zOffset;
	// FPS camera.
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UCameraComponent* FPSCameraComponent;
	// TPS Camera
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UCameraComponent* TPSCameraComponent;
	// Perspective Change boolean
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool isFirstPerson = true;
	// First-Person Arms
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) USkeletalMeshComponent* FPSArms;
	// Sets which ability to use
	int currentPower = 1;
	// Pointers of abilities
	UPROPERTY(EditAnywhere, Category = "Projectile") AMyRock* HeldRock;
	UPROPERTY() TArray<AMyRock*> heldRocks;
	UPROPERTY(EditAnywhere, Category = "clone") AAbilityClone* clone;
	UPROPERTY(EditAnywhere, Category = "Armour") UMyRockArmour* armour;
	UPROPERTY() class UMyHUD* myHud;
	// Used to pass in maximum mana amount for each class.
	UPROPERTY(EditAnywhere) float maxMana;

private:
	class UAIPerceptionStimuliSourceComponent* stimulus;

	void setupStimulus();
};