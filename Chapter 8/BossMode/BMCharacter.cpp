// Fill out your copyright notice in the Description page of Project Settings.

#include "BossMode.h"
#include "BMCharacter.h"


// Sets default values
ABMCharacter::ABMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// Set the character turn rates
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	// Create a CameraComponent	
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPCameraComponent->AttachParent = GetCapsuleComponent();

	// Position the camera
	FPCameraComponent->RelativeLocation = FVector(0, 0, 64.f);
	FPCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will only be viewed by the controlling pawn
	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));

	FPMesh->SetOnlyOwnerSee(true);
	FPMesh->AttachParent = FPCameraComponent;
	FPMesh->bCastDynamicShadow = false;
	FPMesh->CastShadow = false;

	FPGunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FPGunMesh->SetOnlyOwnerSee(true);// only the owning player will see mesh

	FPGunMesh->bCastDynamicShadow = false;
	FPGunMesh->CastShadow = false;

	FPGunMesh->AttachTo(FPMesh, TEXT("GripPoint"), EAttachLocation::SnapToTargetIncludingScale, true);

	ProjSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));
	ProjSpawn->AttachTo(FPGunMesh);


}

// Called when the game starts or when spawned
void ABMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABMCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ABMCharacter::OnTrack()
{
	FVector MousePos;
	FVector MouseDir;
	FHitResult Hit;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel2);

	APlayerController* playerController = Cast<APlayerController>(GetController());

	if (GEngine->GameViewport != nullptr && playerController != nullptr)
	{
		FVector2D ScreenPos = GEngine->GameViewport->Viewport->GetSizeXY();

		playerController->DeprojectScreenPositionToWorld(ScreenPos.X / 2.0f, ScreenPos.Y / 2.0f, MousePos, MouseDir);
		MouseDir *= 100000.0f;

		GetWorld()->LineTraceSingleByObjectType(Hit, MousePos, MouseDir, ObjectQueryParams);

		if (Hit.bBlockingHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("TRACE HIT WITH %s"), *(Hit.GetActor()->GetName()));

			TrackingSceneComponent = Cast<USceneComponent>(Hit.GetActor()->GetComponentByClass(USceneComponent::StaticClass()));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Trace"));
			TrackingSceneComponent = nullptr;
		}
	}
}


void ABMCharacter::MoveForward(float Val)
{
	if (Val != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void ABMCharacter::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Val);
	}
}

void ABMCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABMCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABMCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	check(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ABMCharacter::OnFire);
	InputComponent->BindAction("Track", IE_Pressed, this, &ABMCharacter::OnTrack);

	InputComponent->BindAxis("MoveForward", this, &ABMCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABMCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ABMCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ABMCharacter::LookUpAtRate);

}

void ABMCharacter::OnFire()
{
	// attempt to fire Projectile
	if (ProjectileClass != nullptr)
	{
		if (GetWorld() != nullptr)
		{
			ABMProjectile* ThisProjectile = GetWorld()->SpawnActor<ABMProjectile>(ProjectileClass, ProjSpawn->GetComponentLocation(), GetControlRotation());

			ThisProjectile->GetProjectileMovement()->HomingTargetComponent = TrackingSceneComponent;

		}
	}
}




