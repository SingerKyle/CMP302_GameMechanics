// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityClone.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AAbilityClone::AAbilityClone()
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
		AIController->MoveToLocation(FVector(100, 100, 0), -1.0f, true, true, true);
		CloneMove = UAITask_MoveTo::AIMoveTo(AIController, FVector(100, 100, 0), this);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Running"));
	}
}

// Called every frame
void AAbilityClone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//MoveForward(200);
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

