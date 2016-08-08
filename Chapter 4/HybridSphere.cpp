// Fill out your copyright notice in the Description page of Project Settings.

#include "HelloCode.h"
#include "HybridSphere.h"


// Sets default values
AHybridSphere::AHybridSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the remaining components and attach to appropriate parents
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	RootComponent = Sphere;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(Sphere);

	Particles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
	Particles->AttachTo(Mesh);

	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	Text->AttachTo(Mesh);

	OnActorBeginOverlap.AddDynamic(this, &AHybridSphere::MyOnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AHybridSphere::MyOnEndOverlap);
}

// Called when the game starts or when spawned
void AHybridSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHybridSphere::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AHybridSphere::MyOnBeginOverlap_Implementation(AActor* OtherActor)
{
	FString outputString;
	outputString = "Hello From C++!";
	Text->SetText(FText::FromString(outputString));
}

void AHybridSphere::MyOnEndOverlap_Implementation(AActor* OtherActor)
{
	Text->SetText(NSLOCTEXT("AnyNS", "Any", "Goodbye From C++"));
}
