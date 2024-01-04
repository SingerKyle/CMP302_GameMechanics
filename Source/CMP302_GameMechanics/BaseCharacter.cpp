// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> montageFinder(TEXT("'/Game/ParagonGideon/Characters/Heroes/Gideon/Animations/Primary_Attack_B_Medium_Montage.Primary_Attack_B_Medium_Montage'"));
	if (montageFinder.Succeeded())
	{
		// Set the animation blueprint on the skeletal mesh component
		attackMontage = montageFinder.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> stunnedMontageFinder(TEXT("'/Game/Blueprints/Anim/StunAnimation.StunAnimation'"));
	if (stunnedMontageFinder.Succeeded())
	{
		stunMontage = stunnedMontageFinder.Object;
	}

	mana = 200;
	damage = 50;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::regenerateMana(float dt, float maxMana)
{
	// Variable to set how much mana regenerates a second
	float manaRegenRate = 5.0f;

	timer += dt;
	if (timer > 1.0f)
	{
		mana += manaRegenRate;
		mana = FMath::Clamp(mana, 0, maxMana);
		

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, FString::Printf(TEXT("Current Mana (regen function): %.2f"), mana));
		timer = 0;
	}
}

void ABaseCharacter::setHealth(float amount)
{
	health = amount;
	maxHealth = amount;
}

void ABaseCharacter::healthChange(float amount)
{
	if (amount < 0) // if less than 0 = taking damage
	{
		health += amount;
	}
	else // restoring health
	{
		health += amount;
	}
}

void ABaseCharacter::setMana(float amount)
{
	mana = amount;
}

void ABaseCharacter::manaChange(float amount)
{
	if (amount < 0) // if less than 0 = losing mana
	{
		mana += amount;
	}
	else // restoring mana
	{
		mana += amount;
	}
}

