// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class CMP302_GAMEMECHANICS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// BodyMesh
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) USkeletalMeshComponent* bodyMesh;
	// Animation Blueprint
	UPROPERTY(VisibleDefaultsOnly, Category = Animation) UAnimBlueprint* animation;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Function to regenerate mana
	void regenerateMana(float dt, float maxMana);

	// Getters and Setters
	void setHealth(float health);
	void healthChange(float amount);
	float getHealth() { return health; }
	float getMaxHealth() { return maxHealth; }

	void setMana(float mana);
	void manaChange(float amount);
	float getMana() { return mana; }

	float getDamage() { return damage; }
	UFUNCTION() 

	UAnimMontage* getAttackMontage() { return attackMontage; }
	UAnimMontage* getHurtMontage() { return stunMontage; }

private:
	// Health
	UPROPERTY(EditAnywhere) float health;
	UPROPERTY(EditAnywhere) float maxHealth;
	// Mana
	UPROPERTY(EditAnywhere) float mana;
	// damage value
	UPROPERTY(EditAnywhere) float damage;
	// montages for animations
	UPROPERTY() UAnimMontage* attackMontage;
	UPROPERTY() UAnimMontage* stunMontage;

	float timer = 0;
};
