// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRockArmour.h"

#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMyRockArmour::UMyRockArmour()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemAsset(TEXT("'/Game/Blueprints/SANDCLONEEFFECT.SANDCLONEEFFECT'"));
	if (NiagaraSystemAsset.Succeeded())
	{
		ArmourParticle = NiagaraSystemAsset.Object;
	}
}


// Called when the game starts
void UMyRockArmour::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UMyRockArmour::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsActive() == true)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Can call niagara maybe from here!"));

		// Get the owning actor (assuming the component is attached to the player actor)
		USceneComponent* ownerComponent = GetOwner()->GetRootComponent();

		if (ownerComponent)
		{
			// Get the player controller
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

			if (PlayerController && active == false)
			{
				// Call Niagara function to spawn the effect at the player's location
				UNiagaraFunctionLibrary::SpawnSystemAttached(ArmourParticle, ownerComponent, NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false, true);
				active = true;
			}
		}
		// setup timer again for x seconds
		timer += DeltaTime;
		if (timer >= 8)
		{
			SetActive(false);
			timer = 0;
			active = false;
		}
	}
}

