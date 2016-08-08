// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HelloSphere.generated.h"

UCLASS()
class HELLOWORLD_API AHelloSphere : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHelloSphere();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:

	// On Overlap implementation
	UFUNCTION()
	void MyOnBeginOverlap(AActor* OtherActor);

	// On End Overlap implementation
	UFUNCTION()
	void MyOnEndOverlap(AActor* OtherActor);

	class UTextRenderComponent* TextRenderComponent;
};
