// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"

#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMyHUD::setHealth(float health, float maxHealth)
{
	healthBar->SetPercent(health / maxHealth);
}

void UMyHUD::setMana(float mana, float maxMana)
{
	manaBar->SetPercent(mana / maxMana);
}

void UMyHUD::setText(FText& text)
{
	abilityText->SetText(text);
}

void UMyHUD::setImage(UTexture2D* image)
{
	iconImage->SetBrushFromTexture(image);
}

