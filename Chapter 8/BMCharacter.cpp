// Fill out your copyright notice in the Description page of Project Settings.

#include "BossModeRemake.h"
#include "BMProjectile.h"
#include "BMCharacter.h"


// Sets default values
ABMCharacter::ABMCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPCameraComponent->AttachParent = GetCapsuleComponent();
	FPCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FPCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	FPMesh->SetOnlyOwnerSee(true);
	FPMesh->AttachParent = FPCameraComponent;
	FPMesh->bCastDynamicShadow = false;
	FPMesh->CastShadow = false;

	// Create a gun mesh component
	FPGunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FPGunMesh->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FPGunMesh->bCastDynamicShadow = false;
	FPGunMesh->CastShadow = false;
	FPGunMesh->AttachTo(FPMesh, TEXT("GripPoint"), EAttachLocation::SnapToTargetIncludingScale, true);

	ProjSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));
	ProjSpawn->AttachTo(FPGunMesh);
}

// Called every frame
void ABMCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
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
	// Attemp to fire Projectile
	if (ProjectileClass != nullptr)
	{
		if (GetWorld() != nullptr)
		{
			ABMProjectile* ThisProjectile = GetWorld()->SpawnActor<ABMProjectile>(ProjectileClass, ProjSpawn->GetComponentLocation(), GetControlRotation());
			ThisProjectile->GetProjectileMovement()->HomingTargetComponent = TrackingSceneComponent;
		}
	}
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

		DrawDebugLine(GetWorld(), MousePos, MouseDir, FColor::Red, true, 3.0f, 1, 1.0f);
		GetWorld()->LineTraceSingleByObjectType(Hit, MousePos, MouseDir, ObjectQueryParams);

		if (Hit.bBlockingHit)
		{
			int itest = 0;
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

void ABMCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ABMCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
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

