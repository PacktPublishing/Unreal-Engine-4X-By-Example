// Fill out your copyright notice in the Description page of Project Settings.

#include "BountyDash.h"
#include "DestroyedFloorPiece.h"
#include "Engine/DestructibleMesh.h"


// Sets default values
ADestroyedFloorPiece::ADestroyedFloorPiece()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	check(RootComponent);

	Destructable = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructable"));
	check(Destructable);

	Destructable->AttachTo(RootComponent);
	Destructable->SetCollisionProfileName("OverlapAllDynamic");

	ConstructorHelpers::FObjectFinder<UDestructibleMesh> myDestMesh(TEXT("/Game/Barrel_Hopper/Destroyable_Mesh_DM.Destroyable_Mesh_DM"));

	if (myDestMesh.Succeeded())
	{
		Destructable->SetDestructibleMesh(myDestMesh.Object);
	}

}

void ADestroyedFloorPiece::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle thisTimer;
	GetWorld()->GetTimerManager().SetTimer(thisTimer, this, &ADestroyedFloorPiece::Death, 4.0f, false);
}

void ADestroyedFloorPiece::Death()
{
	GetWorld()->DestroyActor(this);
}
