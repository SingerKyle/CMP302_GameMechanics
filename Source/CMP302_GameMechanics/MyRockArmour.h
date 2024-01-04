// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "NiagaraComponent.h"
#include "Components/ActorComponent.h"
#include "MyRockArmour.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CMP302_GAMEMECHANICS_API UMyRockArmour : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyRockArmour();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

	// particles
	UPROPERTY(EditAnywhere, Category = Particles) UNiagaraSystem* ArmourParticle;
	UPROPERTY(VisibleAnywhere) UNiagaraComponent* ArmourComponent;
	// Timer
	float timer = 0;
	bool active = false;
		
};
