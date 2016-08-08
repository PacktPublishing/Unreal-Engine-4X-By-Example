// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DestroyedFloorPiece.generated.h"

UCLASS()
class BOUNTYDASH_API ADestroyedFloorPiece : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADestroyedFloorPiece();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Death();

	UPROPERTY()
	UDestructibleComponent* Destructable;

	UPROPERTY()
	float TimeTillDeath;
};
