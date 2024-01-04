// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityClone.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "AIMovementComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "NavigationSystem.h"

// Sets default values
AAbilityClone::AAbilityClone(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UAIMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = GetCapsuleComponent();
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 95.0f);
	GetCapsuleComponent()->SetCollisionProfileName("Pawn");

	CloneBody = GetMesh();
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimationBlueprintFinder(TEXT("'/Game/ParagonGideon/Characters/Heroes/Gideon/Gideon_AnimBlueprint.Gideon_AnimBlueprint'"));
	if (AnimationBlueprintFinder.Succeeded())
	{
		// Set the animation blueprint on the skeletal mesh component
		CloneBody->SetAnimInstanceClass(AnimationBlueprintFinder.Object->GeneratedClass);
	}
	// Use ObjectFinder to set the mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("'/Game/ParagonGideon/Characters/Heroes/Gideon/Meshes/Gideon.Gideon'"));
	if (MeshAsset.Succeeded())
	{
		CloneBody->SetSkeletalMesh(MeshAsset.Object);
		//Moves model into capsule
		CloneBody->SetRelativeLocation(FVector(CloneBody->GetRelativeLocation().X, CloneBody->GetRelativeLocation().Y, -95.0f));
		CloneBody->SetRelativeRotation(FRotator(CloneBody->GetRelativeRotation().Pitch, -90.0f, CloneBody->GetRelativeRotation().Yaw));
		CloneBody->SetupAttachment(RootComponent);
	}
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	// set how long the clone is in the level
	InitialLifeSpan = 10.f;
}

// Called when the game starts or when spawned
void AAbilityClone::BeginPlay()
{
	Super::BeginPlay();

	AIController = GetController<AAIController>();
	if (AIController)
	{
		AIController->Possess(this);

		AIController->MoveToLocation(handleMovement(), -1.0f, true, true, true);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Running"));
	}
}

void AAbilityClone::setupStimulus()
{
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Player Stimulus"));
	if (stimulus)
	{
		stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
		stimulus->RegisterWithPerceptionSystem();
	}
}

// Called every frame
void AAbilityClone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector currentPos = GetActorLocation();
	if (FVector::Dist(currentPos, navPos) <= 100.0f)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Distance together"));
		AIController = GetController<AAIController>();
		if (AIController)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Moving!"));
			// generate new position if old position has been reached
			AIController->MoveToLocation(handleMovement(), -1.0f, true, true, true);
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("currentPos: %s, navPos: %s"), *currentPos.ToString(), *navPos.ToString());
}

void AAbilityClone::MoveForward(float val)
{
	// Find forward and record
	FVector Direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(GetActorForwardVector() * val);
}

// Called to bind functionality to input
void AAbilityClone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector AAbilityClone::handleMovement()
{
	FVector startLocation = GetActorLocation();
	// generate random location using navmesh
	if (auto* const navMesh = UNavigationSystemV1::GetCurrent(GetWorld()))
	{
		FNavLocation newPos;
		// sets a random position in navmesh from the start position in range set.
		if (navMesh->GetRandomPointInNavigableRadius(startLocation, searchRange, newPos))
		{
			navPos = newPos.Location;
			navPos.Z = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
			return newPos;
		}
	}
	return FVector(100, 100, 100);
}

