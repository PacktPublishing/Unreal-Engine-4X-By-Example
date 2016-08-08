// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "NSGameMode.h"
#include "NSCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class ANSCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Mesh;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Gun mesh: 3rd person view (seen only by others) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* TP_Gun;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, Category = Gameplay)
	class USoundBase* FireSound;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, Category = Gameplay)
	class USoundBase* PainSound;

	/** 3rd person anim montage asset for gun shot */
	UPROPERTY(EditAnywhere, Category = Gameplay)
	class UAnimMontage* TP_FireAnimaiton;

	/** 1st person anim montage asset for gun shot */
	UPROPERTY(EditAnywhere, Category = Gameplay)
	class UAnimMontage* FP_FireAnimaiton;

	/** particle system for 1st person gun shot effect */
	UPROPERTY(EditAnywhere, Category = Gameplay)
	class UParticleSystemComponent* FP_GunShotParticle;

	/** particle system for 3rd person gun shot effect */
	UPROPERTY(EditAnywhere, Category = Gameplay)
	class UParticleSystemComponent* TP_GunShotParticle;

	/** particle system that will represent a bullet */
	UPROPERTY(EditAnywhere, Category = Gameplay)
	class UParticleSystemComponent* BulletParticle;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	class UForceFeedbackEffect* HitSuccessFeedback;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

protected:
	class UMaterialInstanceDynamic* DynamicMat;
	class ANSPlayerState* NSPlayerState;

public:
	ANSCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	class ANSPlayerState* GetNSPlayerState();
	void SetNSPlayerState(class ANSPlayerState* newPS);
	void Respawn();

	UPROPERTY(Replicated, BlueprintReadWrite, Category = Team)
	ETeam CurrentTeam;
protected:
	
	/** Fires a projectile. */
	void OnFire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	// will be called by the server to perform raytrace
	void Fire(const FVector pos, const FVector dir);

	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void BeginPlay();
	virtual void PossessedBy(AController* NewController) override;


public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return FP_Mesh; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	/** REMOTE PROCEDURE CALLS */
private:
	// Peform fire action on the server
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire(const FVector pos, const FVector dir);

	// Multicast so all clients run shoot effects
	UFUNCTION(NetMultiCast, unreliable)
	void MultiCastShootEffects();

	// Called on death for all clients for hilarious death
	UFUNCTION(NetMultiCast, unreliable)
	void MultiCastRagdoll();

	// Play pain on owning client when hit
	UFUNCTION(Client, Reliable)
	void PlayPain();

public:
	// Set's team colour
	UFUNCTION(NetMultiCast, Reliable)
	void SetTeam(ETeam NewTeam);

};

