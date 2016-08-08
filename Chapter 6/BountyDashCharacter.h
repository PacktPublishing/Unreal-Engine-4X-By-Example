// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PowerUpObject.h"
#include "BountyDashCharacter.generated.h"

UCLASS()
class BOUNTYDASH_API ABountyDashCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Array of movement locations
	UPROPERTY(EditAnywhere, Category = Logic)
	TArray<class ATargetPoint*> TargetArray;

	// Character lane swap speed
	UPROPERTY(EditAnywhere, Category = Logic)
	float CharSpeed;

	// Audio component for obstacle hit sound
	UPROPERTY(EditAnywhere, Category = Sound)
	UAudioComponent* HitObstacleSound;

	// Audio component for coin pickup sound
	UPROPERTY(EditAnywhere, Category = Sound)
	UAudioComponent* DingSound;

protected:
	// Camera Boom for maintaining camera distance to the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	// Camera we will use as the target view
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	// Player Score
	UPROPERTY(BlueprintReadOnly)
	int32 Score;

	// Smash Time
	UPROPERTY(EditAnywhere, Category = PowerUps)
	float SmashTime;

	// Magnet Time
	UPROPERTY(EditAnywhere, Category = PowerUps)
	float MagnetTime;

	UPROPERTY(EditAnywhere, Category = PowerUps)
	float MagnetReach;

	// Kill Point
	float Killpoint;

private:

	// Data for character lane positioning
	short CurrentLocation;
	FVector DesiredLocation;
	bool bBeingPushed;

	// Power up property
	bool CanSmash;
	bool CanMagnet;

public:
	// Sets default values for this character's properties
	ABountyDashCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void ScoreUp();

	void PowerUp(EPowerUp Type);

	int GetScore();

protected:
	// Will handle moving the target location of the player left and right
	void MoveRight();
	void MoveLeft();

	// Power up functions
	void CoinMagnet();

	// Overlap functions to be used upon capsule component collision
	UFUNCTION()
	void MyOnComponentOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void MyOnComponentEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void StopSmash();

	UFUNCTION()
	void StopMagnet();

	UFUNCTION()
	void Reset();

};
