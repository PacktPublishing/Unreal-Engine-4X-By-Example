// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "NSGameMode.h"
#include "NSSpawnPoint.generated.h"

UCLASS()
class NS_API ANSSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANSSpawnPoint();
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	void ActorBeginOverlaps(AActor* OtherActor);

	UFUNCTION()
	void ActorEndOverlaps(AActor* OtherActor);

	bool GetBlocked()
	{
		return OverlappingActors.Num() != 0;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ETeam Team;

private:
	UCapsuleComponent* SpawnCapsule;

	TArray<class AActor*> OverlappingActors;
};
