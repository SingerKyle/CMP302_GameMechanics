// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHUD.generated.h"

/**
 * Based on class from Lively Geek - https://www.youtube.com/watch?v=T7v3UnL6PNU&t=406s
 */
UCLASS()
class CMP302_GAMEMECHANICS_API UMyHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void setHealth(float health, float maxHealth);

	void setMana(float mana, float maxMana);

	void setText(FText& text);

	void setImage(UTexture2D* image);

	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UProgressBar* healthBar;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UProgressBar* manaBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UTextBlock* abilityText;

	UPROPERTY(EditAnywhere, meta = (BindWidget)) class UImage* iconImage;

};
