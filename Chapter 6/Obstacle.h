// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BountyDashObject.h"
#include "Obstacle.generated.h"

UCLASS(BlueprintType)
class BOUNTYDASH_API AObstacle : public ABountyDashObject
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AObstacle();

	UDestructibleComponent* GetDestructable();

protected:
	UPROPERTY(EditAnywhere)
	UDestructibleComponent* Mesh;
};


