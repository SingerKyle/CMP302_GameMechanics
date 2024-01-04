// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.h"
#include "Enemy_AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "MyCombatInterface.h"
#include "MyEarthbender.h"
#include "MyEnemy.generated.h"

UCLASS()
class CMP302_GAMEMECHANICS_API AMyEnemy : public ABaseCharacter, public IMyCombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyEnemy(const FObjectInitializer& ObjectInitializer);

	int meleeAttack_Implementation() override;
	int rangedAttack_Implementation() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UBehaviorTree* getBehaviorTree() const;

	float getManaFromBase();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	UFUNCTION() void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision") class UBoxComponent* leftFist;

	// called when health < 0
	void Die();

protected:
	// behaviour tree
	UPROPERTY(EditAnywhere, Category = "Enemy AI") UBehaviorTree* tree;
	// maximum mana value for ranged attack
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float maxMana;
	// hurt variable to stop other animations playing
	UPROPERTY() bool hurt = false;
};
