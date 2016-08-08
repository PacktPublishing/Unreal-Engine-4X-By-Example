// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ObstacleSpawner.generated.h"

UCLASS()
class BOUNTYDASH_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObstacleSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;


protected:

	void SpawnObstacle();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class AObstacle>> ObstaclesToSpawn;

	UPROPERTY()
	TArray<class ATargetPoint*>SpawnTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTimer;

	UPROPERTY()
	USceneComponent* Scene;

private:
	float KillPoint;
	float SpawnPoint;
	float TimeSinceLastSpawn;
};
