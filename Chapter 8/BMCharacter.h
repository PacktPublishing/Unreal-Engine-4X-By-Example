// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BMCharacter.generated.h"

UCLASS()
class BOSSMODEREMAKE_API ABMCharacter : public ACharacter
{
	GENERATED_BODY()

	// Pawn Mesh, will only be seen by self
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FPMesh;

	// Gun Mesh, will only be seen by self
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FPGunMesh;

	// First person camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FPCameraComponent;

public:
	// Sets default values for this character's properties
	ABMCharacter();

	// Base Turn Rate in deg/sec
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	// Base Lookup/Down rate in deg/sec
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	// Projectile Spawn
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Projectile)
	class USceneComponent* ProjSpawn;

	// Projectile class to use
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABMProjectile> ProjectileClass;

protected:
	USceneComponent* TrackingSceneComponent;

protected:
	/** fires a projectile */
	void OnFire();
	
	/** Performs Line trace to search for tracking target*/
	void OnTrack();

	/** Handles forwards and backwards movement */
	void MoveForward(float Val);

	/** Handles left and right strafing movement*/
	void MoveRight(float Val);

	/**
	* Will be called via input axis mapping
	* @param Rate this is the normalized rate, 1.0 means full turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate this is the normalized rate, 1.0 means full turn rate
	*/
	void LookUpAtRate(float Rate);
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
};
