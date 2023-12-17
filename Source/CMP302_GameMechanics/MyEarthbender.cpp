// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEarthbender.h"
#include "Animation/AnimInstance.h"

// Sets default values
AMyEarthbender::AMyEarthbender()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

<<<<<<< HEAD
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 95.0f);

	bodyMesh = GetMesh();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("'/Game/ParagonGideon/Characters/Heroes/Gideon/Meshes/Gideon.Gideon'"));
	if (MeshAsset.Succeeded())
	{
		bodyMesh->SetSkeletalMesh(MeshAsset.Object);
		//Moves model into capsule
		bodyMesh->SetRelativeLocation(FVector(bodyMesh->GetRelativeLocation().X, bodyMesh->GetRelativeLocation().Y, -95.0f));
		bodyMesh->SetRelativeRotation(FRotator(bodyMesh->GetRelativeRotation().Pitch, -90.0f, bodyMesh->GetRelativeRotation().Yaw));
		bodyMesh->SetCastHiddenShadow(true);
		bodyMesh->SetupAttachment(RootComponent);
	}
=======
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 88.0f);
>>>>>>> parent of 1feb2f0 (Added effects to my rock throw and started next ability - sand clones)

	// Create First Person Camera
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);
	// Create Third Person Camera
	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	check(TPSCameraComponent != nullptr);

	// Attach the camera component to our capsule component.
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	TPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	// Set camera just above the eye level of the model (hopefully)
<<<<<<< HEAD
	FPSCameraComponent->SetRelativeLocation(FVector(60.0f, 0.0f, BaseEyeHeight + 10.0f));
=======
	FPSCameraComponent->SetRelativeLocation(FVector(20.0f, 0.0f, 30.0f + BaseEyeHeight));
>>>>>>> parent of 1feb2f0 (Added effects to my rock throw and started next ability - sand clones)
	// Allow the user to control camera rotation
	FPSCameraComponent->bUsePawnControlRotation = true;

	// Set third person camera to behind the model and at eye level
	TPSCameraComponent->SetRelativeLocation(FVector(-150.0f, 10.0f, 65.0f));
	// Allow the user to control camera rotation
	TPSCameraComponent->bUsePawnControlRotation = true;


	//First Person Arm Mesh
	FPSArms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonArms"));
	check(FPSArms != nullptr);

	// Make only the owning actor see the arms
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAssetArms(TEXT("'/Game/ParagonGideon/Characters/Heroes/Gideon/Meshes/Gideon.Gideon'"));
	if (MeshAssetArms.Succeeded())
	{


		FPSArms->SetOnlyOwnerSee(true);
		// Attach Arms to camera
		FPSArms->SetupAttachment(FPSCameraComponent);
		FPSArms->SetRelativeLocation(FVector(165, 0, -85));
		FPSArms->SetRelativeRotation(FRotator(-55.0f, -20.0f, -110.0f));
		FPSArms->bCastDynamicShadow = false;
		FPSArms->CastShadow = false;
	}
	

	zOffset = BaseEyeHeight + 50.0f;
	health = 100.0f;
}

void AMyEarthbender::updateRock(float value)
{
	FVector newLocation = FMath::Lerp(startLocation, endLocation, value);
	HeldRock->SetActorLocation(newLocation);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Timeline Works!"));
}

// Called when the game starts or when spawned
void AMyEarthbender::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	APlayerCameraManager* const camMan = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;

	camMan->ViewPitchMin = -50.f;
	camMan->ViewPitchMax = 50.f;

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("EarthBender Working!!"));
}

// Called every frame
void AMyEarthbender::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	rockTimeline.TickTimeline(DeltaTime);
}

// Called to bind functionality to input
void AMyEarthbender::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Create Player movement bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyEarthbender::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyEarthbender::MoveRight);
	// Create player mouse movement 
	PlayerInputComponent->BindAxis("LookX", this, &AMyEarthbender::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookY", this, &AMyEarthbender::AddControllerPitchInput);
	// Create Action Bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyEarthbender::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyEarthbender::StopJump);
	// Camera Toggle
	PlayerInputComponent->BindAction("ChangePerspective", IE_Pressed, this, &AMyEarthbender::ChangePerspective);
	// Fire command
	PlayerInputComponent->BindAction("CreateRock", IE_Pressed, this, &AMyEarthbender::powerPick);
	PlayerInputComponent->BindAction("ThrowRock", IE_Pressed, this, &AMyEarthbender::ThrowRock);

	// selecting ability
	DECLARE_DELEGATE_OneParam(InputDelegate, const int);
	PlayerInputComponent->BindAction<InputDelegate>("Power1", IE_Pressed, this, &AMyEarthbender::setPower, 1);
	PlayerInputComponent->BindAction<InputDelegate>("Power2", IE_Pressed, this, &AMyEarthbender::setPower, 2);
	PlayerInputComponent->BindAction<InputDelegate>("Power2", IE_Pressed, this, &AMyEarthbender::setPower, 3);

}

void AMyEarthbender::ChangePerspective()
{
	isFirstPerson = !isFirstPerson; // Toggle the camera state

	if (isFirstPerson)
	{
		FPSCameraComponent->SetActive(true);
		TPSCameraComponent->SetActive(false);
		// Hide model in first person
		GetMesh()->SetOwnerNoSee(true);
		FPSArms->SetOwnerNoSee(false);
	}
	else
	{
		FPSCameraComponent->SetActive(false);
		TPSCameraComponent->SetActive(true);
		// show model in third person
		GetMesh()->SetOwnerNoSee(false);
		FPSArms->SetOwnerNoSee(true);
	}
}

void AMyEarthbender::powerPick()
{
	switch (currentPower)
	{
	case 1:
		CreateRock();
		break;
	case 2:

		break;
	case 3:
		createClone();
		break;
	default:
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Switch Error"));
		break;
	}
}

void AMyEarthbender::CreateRock()
{
	// Attempt to fire a projectile.
	if (ProjectileClass)
	{
		// Get the camera transform.
		const FRotator SpawnRotation = GetControlRotation();
		const FVector ActorForward = FVector(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorForwardVector() * FMath::RandRange(200.f, 400.f));
		const FVector ActorLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		FVector SpawnLocation = ((ActorLocation + ActorForward));
		SpawnLocation.Z = 100;

		//const FVector SpawnLocation = (FVector(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation().X, GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation().Y, GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation().Z) + SpawnRotation.RotateVector(FVector(200.0f, 0.0f, 0.0f)));
		// Log the camera location and rotation.
		//UE_LOG(LogTemp, Warning, TEXT("CameraLocation: %s"), *CameraLocation.ToString());

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Spawn the projectile at the muzzle.
			HeldRock = World->SpawnActor<AMyRock>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
			//HeldRock->SetActorScale3D(FVector(2, 2, 2));
			if (rockCurveFloat)
			{
				FOnTimelineFloat timelineProgress;
				timelineProgress.BindUFunction(this, FName("updateRock"));
				rockTimeline.AddInterpFloat(rockCurveFloat, timelineProgress);
				//rockTimeline.SetLooping(true);

				startLocation = endLocation = HeldRock->GetActorLocation();
				endLocation.Z += zOffset;

			}

			if (HeldRock)
			{
				rockTimeline.PlayFromStart();
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Projectile Working!"));
				UStaticMeshComponent* RockMeshComponent = HeldRock->RockMeshComponent;
				if (RockMeshComponent)
				{
					FBoxSphereBounds Bounds = RockMeshComponent->CalcBounds(RockMeshComponent->GetComponentTransform());

					// Access the extent in each dimension
					BoxExtentZ = Bounds.BoxExtent.Z * 2;
				}
				//HeldRock->SetActorLocation(FVector(Projectile->GetActorLocation().X, Projectile->GetActorLocation().Y, -BoxExtentZ));
				//HeldRock = Projectile;
			}
		}
	}
}

void AMyEarthbender::createClone()
{

<<<<<<< HEAD
			// Get the camera transform.
			const FRotator SpawnRotation(GetActorForwardVector().X, RandomSpawnAngle, GetActorForwardVector().Z);
			FVector Offset(FMath::Cos(FMath::DegreesToRadians(RandomSpawnAngle)), FMath::Sin(FMath::DegreesToRadians(RandomSpawnAngle)), 0.0f);
			const FVector ActorLocation = World->GetFirstPlayerController()->GetPawn()->GetActorLocation();
			FVector SpawnLocation = ActorLocation + Offset * FMath::RandRange(200.f, 500.f);
			SpawnLocation.Z = 100;

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Spawn the projectile at the muzzle.
			clone = World->SpawnActor<AAbilityClone>(CloneClass, SpawnLocation, SpawnRotation, SpawnParams);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("SHOULD BE SPAWNED!"));

			if (clone)
			{
				AbilityClones.Push(clone);
			}
			
		}
	}

=======
>>>>>>> parent of 1feb2f0 (Added effects to my rock throw and started next ability - sand clones)
}

/*void AMyEarthbender::UpdateRock()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("updateRock!"));
	if (HeldRock)
	{
		FVector NewLocation = HeldRock->GetActorLocation();
		NewLocation.Z = FMath::Lerp(-BoxExtentZ, 120.0f, RockRiseTimeline.GetPlaybackPosition()); // Interpolate the Z position
		HeldRock->SetActorLocation(NewLocation, true);
	}
}*/

void AMyEarthbender::ThrowRock()
{
	if (HeldRock)
	{
		rockTimeline.Stop();

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("shoot!"));
		// Calculate the throw direction based on the player's view direction.
		const FRotator SpawnRotation = GetControlRotation();
		const FVector ThrowDirection = SpawnRotation.Vector();

		// Call the FireInDirection function on the held rock to set its initial velocity.
		HeldRock->FireInDirection(ThrowDirection);
		//HeldRock = nullptr;
		//bIsHoldingRock = false;
	}
}

float AMyEarthbender::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	health -= 50;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), health);

	if (health <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Dead!"));
	}

	return 50.0f;
}

void AMyEarthbender::setPower(int num)
{
	currentPower = num;
}

bool AMyEarthbender::LineTraceMethod(FHitResult& OutHit)
{
	if (FPSCameraComponent)
	{
		FVector CameraLocation = FPSCameraComponent->GetComponentLocation();
		FVector CameraForward = FPSCameraComponent->GetForwardVector();

		FVector StartPoint = CameraLocation;
		FVector EndPoint = StartPoint + CameraForward + (CameraForward * GrabRange);

		FCollisionQueryParams Parameters;
		return GetWorld()->LineTraceSingleByChannel(OutHit, StartPoint, EndPoint, ECC_Visibility, Parameters);
	}
	else
	{
		return false;
	}
}

UFUNCTION() void AMyEarthbender::MoveForward(float val)
{
	// Find forward and record
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(GetActorForwardVector() * val);
}

UFUNCTION() void AMyEarthbender::MoveRight(float val)
{
	// Find forward and record
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, val);
}

UFUNCTION() void AMyEarthbender::StartJump()
{
	bPressedJump = true;
}

UFUNCTION() void AMyEarthbender::StopJump()
{
	bPressedJump = false;
}

