// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HybridSphere.generated.h"

UCLASS()
class HELLOWORLD_API AHybridSphere : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHybridSphere();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// On Overlap implementation
	UFUNCTION(BlueprintNativeEvent)
	void MyOnBeginOverlap(AActor* OtherActor);

	void MyOnBeginOverlap_Implementation(AActor* OtherActor);

	// On End Overlap implementation
	UFUNCTION(BlueprintNativeEvent)
	void MyOnEndOverlap(AActor* OtherActor);

	void MyOnEndOverlap_Implementation(AActor* OtherActor);


protected:

	UPROPERTY(Category = "Components", EditAnywhere)
	class USphereComponent* Sphere;

	UPROPERTY(Category = "Components", EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadOnly)
	class UTextRenderComponent* Text;

	UPROPERTY(Category = "Components", EditAnywhere)
	class UParticleSystemComponent* Particles;
};
