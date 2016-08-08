// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BountyDashObject.h"
#include "Coin.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYDASH_API ACoin : public ABountyDashObject
{
	GENERATED_BODY()

	ACoin();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	virtual void MyOnActorOverlap(AActor* otherActor) override;

public:

	bool BeingPulled;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

};
