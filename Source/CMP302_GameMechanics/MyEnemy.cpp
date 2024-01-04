// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "Components/BoxComponent.h"
#include "AIMovementComponent.h"
#include "Engine/DamageEvents.h"

// Sets default values
AMyEnemy::AMyEnemy(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UAIMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set capsule size
	//GetCapsuleComponent()->InitCapsuleSize(34.0f, 95.0f);

	// Initialise skeletal mesh of enemies
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

	// setup fist hitbox
	leftFist = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Fist"));
	if (leftFist)
	{
		FVector fistBoxSize(8.0f, 5.0f, 5.0f);
		leftFist->SetBoxExtent(fistBoxSize, false);
		FVector boxLocation(7.0f, 0.0f, 0.0f);
		leftFist->SetRelativeLocation(FVector(boxLocation));
		leftFist->SetupAttachment(bodyMesh, "hand_l_Socket");
		leftFist->OnComponentBeginOverlap.AddDynamic(this, &AMyEnemy::OnHit);
		leftFist->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	}

	// Setup Behaviour Tree
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprints/AI/Enemy_tree.Enemy_tree'"));
	if (BTObject.Succeeded())
	{
		tree = BTObject.Object;
	}

	// Setup controller
	AIControllerClass = AEnemy_AIController::StaticClass();

	// Setup Animation Blueprint
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimationBlueprintFinder(TEXT("'/Game/ParagonGideon/Characters/Heroes/Gideon/Gideon_AnimBlueprint.Gideon_AnimBlueprint'"));
	if (AnimationBlueprintFinder.Succeeded())
	{
		// Set the animation blueprint on the skeletal mesh component
		bodyMesh->SetAnimInstanceClass(AnimationBlueprintFinder.Object->GeneratedClass);
	}

	setHealth(200);
	setMana(200);
	maxMana = getMana();

	hurt = false;

	GetCharacterMovement()->MaxAcceleration = 500.0f;
}

int AMyEnemy::meleeAttack_Implementation()
{
	if (getAttackMontage() && hurt == false)
	{
		PlayAnimMontage(getAttackMontage());
	}
	return 0;
}

int AMyEnemy::rangedAttack_Implementation()
{
	if (getAttackMontage() && hurt == false)
	{
		PlayAnimMontage(getAttackMontage());
	}
	return 0;
}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();

	FString socketName = "hand_l_Socket";
	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
	leftFist->AttachToComponent(bodyMesh, rules, FName(socketName));
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetMesh()->GetAnimInstance()->Montage_GetIsStopped(getHurtMontage()))
	{
		hurt = false;
		AEnemy_AIController* AIController = Cast<AEnemy_AIController>(GetController());
		AIController->SetIgnoreMoveInput(false);
	}
}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBehaviorTree* AMyEnemy::getBehaviorTree() const
{
	return tree;
}

float AMyEnemy::getManaFromBase()
{
	return getMana();
}

float AMyEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	healthChange(-100);

	AEnemy_AIController* AIController = Cast<AEnemy_AIController>(GetController());
	AIController->SetIgnoreMoveInput(true);

	bodyMesh = GetMesh();

	if (bodyMesh->GetAnimInstance())
	{
		UAnimInstance* animInstance = bodyMesh->GetAnimInstance();

		animInstance->Montage_Play(getHurtMontage());
		hurt = true;

		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Animation should play!"));
	}

	if (getHealth() <= 0)
	{
		AMyEarthbender* player = Cast<AMyEarthbender>(DamageCauser);
		if (player == DamageCauser)
		{
			player->manaChange(100);
		}
		Die();
	}

	return DamageAmount;
}

void AMyEnemy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AMyEarthbender* player = Cast<AMyEarthbender>(OtherActor);

	if(player == OtherActor)
	{
		FDamageEvent damagevent;
		damagevent.DamageTypeClass = UDamageType::StaticClass();

		player->TakeDamage(50, damagevent, this->GetController(), this);
	}
}

void AMyEnemy::Die()
{
	// Disable all collision on capsule 
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	// Ragdoll physics
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->WakeAllRigidBodies();
	GetMesh()->bBlendPhysics = true;

	// Set mass after enabling physics
	GetMesh()->SetMassOverrideInKg(NAME_None, 10.0f, true);

	// Set collision profile after enabling physics
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	SetActorEnableCollision(true);

		

	UCharacterMovementComponent* CharacterComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (CharacterComp)
	{
		CharacterComp->StopMovementImmediately();
		CharacterComp->DisableMovement();
		CharacterComp->SetComponentTickEnabled(false);
	}

	SetLifeSpan(10.0f);


}

