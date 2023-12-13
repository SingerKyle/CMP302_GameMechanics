// Fill out your copyright notice in the Description page of Project Settings.

#include "MyRock.h"
#include "Curves/CurveFloat.h"

// Sets default values
AMyRock::AMyRock()
{
	//Random Mesh Generator
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh1(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Trim_90_In.Shape_Trim_90_In'"));
	if (Mesh1.Succeeded())
	{
		RockMeshes.Add(Mesh1.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh2(TEXT("'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (Mesh2.Succeeded())
	{
		RockMeshes.Add(Mesh2.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh3(TEXT("'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (Mesh3.Succeeded())
	{
		RockMeshes.Add(Mesh3.Object);
	}

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComponent)
	{
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(15.0f);
		// Set the root component to be the collision component.
		RootComponent = CollisionComponent;
	}

	if (!RockMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		RockMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		RockMovementComponent->SetUpdatedComponent(CollisionComponent);
		//RockMovementComponent->InitialSpeed = 0.0f;
		//RockMovementComponent->MaxSpeed = 0.0f;
		RockMovementComponent->bRotationFollowsVelocity = false;
		RockMovementComponent->bShouldBounce = true;
		RockMovementComponent->Bounciness = 0.3f;
		RockMovementComponent->ProjectileGravityScale = 0.0f;
	}

	if (!RockMeshComponent)
	{
		int32 RandomNumber = FMath::RandRange(0, RockMeshes.Num() - 1);
		RockMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		//static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Trim_90_In.Shape_Trim_90_In'"));
		if (RockMeshes.IsValidIndex(RandomNumber))
		{
			FMath::FRand();
			//RockMeshComponent->SetStaticMesh(Mesh.Object);
			RockMeshComponent->SetStaticMesh(RockMeshes[RandomNumber]);
		}

		static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold"));
		if (Material.Succeeded())
		{
			RockMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, RockMeshComponent);
		}
		RockMeshComponent->SetMaterial(0, RockMaterialInstance);
		RockMeshComponent->SetRelativeScale3D(FVector(FMath::FRandRange(0.5f,1.25f)));
		//RockMeshComponent->SetSimulatePhysics(true);
		RockMeshComponent->SetupAttachment(RootComponent);
	}

	// Delete the projectile after 3 seconds.
	//InitialLifeSpan = 4.0f;
}


// Called when the game starts or when spawned
void AMyRock::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyRock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Function that initializes the projectile's velocity in the shoot direction.
void AMyRock::FireInDirection(const FVector& ShootDirection)
{
	RockMeshComponent->SetSimulatePhysics(true);
	RockMeshComponent->AddImpulse(ShootDirection * 500000);
}

