// Fill out your copyright notice in the Description page of Project Settings.

#include "NS.h"
#include "NSSpawnPoint.h"


// Sets default values
ANSSpawnPoint::ANSSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SpawnCapsule->SetCollisionProfileName("OverlapAllDynamic");
	SpawnCapsule->bGenerateOverlapEvents = true;
	SpawnCapsule->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);

	OnActorBeginOverlap.AddDynamic(this, &ANSSpawnPoint::ActorBeginOverlaps);
	OnActorEndOverlap.AddDynamic(this, &ANSSpawnPoint::ActorEndOverlaps);
}

void ANSSpawnPoint::OnConstruction(const FTransform& Transform)
{
	if (Team == ETeam::RED_TEAM)
	{
		SpawnCapsule->ShapeColor = FColor(255, 0, 0);
	}
	else // (Team == ETeam::BLUE_TEAM)
	{
		SpawnCapsule->ShapeColor = FColor(0, 0, 255);
	}

}

// Called every frame
void ANSSpawnPoint::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);
	SpawnCapsule->UpdateOverlaps();

}

void ANSSpawnPoint::ActorBeginOverlaps(AActor* OtherActor)
{
	if (ROLE_Authority == Role)
	{
		if (OverlappingActors.Find(OtherActor) == INDEX_NONE)
		{
			OverlappingActors.Add(OtherActor);
		}
	}
}

void ANSSpawnPoint::ActorEndOverlaps(AActor* OtherActor)
{
	if (ROLE_Authority == Role)
	{
		if (OverlappingActors.Find(OtherActor) != INDEX_NONE)
		{
			OverlappingActors.Remove(OtherActor);
		}
	}
}


