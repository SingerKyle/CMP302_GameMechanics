// Fill out your copyright notice in the Description page of Project Settings.

#include "MyRock.h"
#include "Curves/CurveFloat.h"

// Sets default values
AMyRock::AMyRock()
{
	//Random Mesh Generator
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh1(TEXT("'/Game/StylizedProvencal/Meshes/SM_Rock_Small_01.SM_Rock_Small_01'"));
	if (Mesh1.Succeeded())
	{
		RockMeshes.Add(Mesh1.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh2(TEXT("'/Game/StylizedProvencal/Meshes/SM_Rock_Small_03.SM_Rock_Small_03'"));
	if (Mesh2.Succeeded())
	{
		RockMeshes.Add(Mesh2.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh3(TEXT("'/Game/StylizedProvencal/Meshes/SM_Rock_Small_02.SM_Rock_Small_02'"));
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
		//CollisionComponent->OnComponentHit.AddDynamic(this, &AMyRock::OnHit);
		CollisionComponent->SetSimulatePhysics(true);
		CollisionComponent->BodyInstance.SetCollisionProfileName("QueryAndPhysics");
		CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		CollisionComponent->SetNotifyRigidBodyCollision(true);
		CollisionComponent->OnComponentHit.AddDynamic(this, &AMyRock::OnHit);
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

		static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/StylizedProvencal/Materials/MI_Rocks_.MI_Rocks_'"));
		if (Material.Succeeded())
		{
			RockMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, RockMeshComponent);
		}
		RockMeshComponent->SetMaterial(0, RockMaterialInstance);
		RockMeshComponent->SetRelativeScale3D(FVector(FMath::FRandRange(2.0f, 2.5f)));
		FRotator newRotation(FMath::FRandRange(0.0f, 360.0f), FMath::FRandRange(0.0f, 360.0f), FMath::FRandRange(0.0f, 360.0f));
		RockMeshComponent->SetRelativeRotation(newRotation);
		RockMeshComponent->SetSimulatePhysics(true);
		RockMeshComponent->SetCollisionProfileName("QueryAndPhysics");
		RockMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		RockMeshComponent->SetNotifyRigidBodyCollision(true);
		RockMeshComponent->OnComponentHit.AddDynamic(this, &AMyRock::OnHit);
		RockMeshComponent->SetupAttachment(RootComponent);
		RockMeshComponent->SetAllMassScale(1.0);
	}

	// Delete the projectile after 3 seconds.
	InitialLifeSpan = 4.0f;
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
	// Get the current scale of the rock
	FVector RockScale = RockMeshComponent->GetComponentScale();

	// Calculate a scaling factor based on the rock's scale
	float ScaleFactor = FMath::Max3(RockScale.X, RockScale.Y, RockScale.Z);

	// Adjust the impulse based on the scale factor
	float ImpulseStrength = 250000 * ScaleFactor;

	CollisionComponent->SetSimulatePhysics(true);
	RootComponent = CollisionComponent;
	//UE_LOG(LogTemp, Warning, TEXT("Impulse: %f"), ScaleFactor);
	RockMeshComponent->AddImpulse(ShootDirection * ImpulseStrength);
}

void AMyRock::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("test"));

	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		
	}
}
