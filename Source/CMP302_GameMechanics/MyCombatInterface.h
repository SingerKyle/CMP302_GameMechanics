// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MyCombatInterface.generated.h"

// This class does not need to be modified
// Class is based on MrCxx AI series - ICombat Interface - https://www.youtube.com/watch?v=mqLio5_HwVM&list=PLWUvrI0mg8VKTJWKqsDn_xyZfD3f7Xye-&index=17
UINTERFACE(MinimalAPI)
class UMyCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CMP302_GAMEMECHANICS_API IMyCombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat") int meleeAttack();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat") int rangedAttack();
};
