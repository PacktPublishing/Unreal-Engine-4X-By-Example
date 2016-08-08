// Fill out your copyright notice in the Description page of Project Settings.

#include "BountyDash.h"
#include "Engine/TargetPoint.h"
#include "Coin.h"
#include "Floor.h"
#include "CoinSpawner.h"
#include "BountyDashPowerUp.h"

// Sets default values
ACoinSpawner::ACoinSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	MaxSetCoins = 5;
	MinSetCoins = 3;
	CoinSetTimeInterval = 4.0f;
	CoinTimeInterval = 0.5f;
	MovementTimeInterval = 1.0f;
}


// Called when the game starts or when spawned
void ACoinSpawner::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ATargetPoint> TargetIter(GetWorld()); TargetIter; ++TargetIter)
	{
		SpawnTransforms.Add(*TargetIter);
	}

	for (TActorIterator<AFloor> FloorIter(GetWorld()); FloorIter; ++FloorIter)
	{
		if (FloorIter->GetWorld() == GetWorld())
		{
			KillPoint = FloorIter->GetKillPoint();
			SpawnPoint = FloorIter->GetSpawnPoint();
		}
	}

	// Create Timers
	FTimerManager& worldTimeManager = GetWorld()->GetTimerManager();

	worldTimeManager.SetTimer(CoinSetTimerHandle, this, &ACoinSpawner::SpawnCoinSet, CoinSetTimeInterval, false);
	worldTimeManager.SetTimer(SpawnMoveTimerHandle, this, &ACoinSpawner::MoveSpawner, MovementTimeInterval, true);
}

void ACoinSpawner::SpawnCoinSet()
{
	NumCoinsToSpawn = FMath::RandRange(MinSetCoins, MaxSetCoins);
	
	FTimerManager& worldTimeManager = GetWorld()->GetTimerManager();

	// Swap active timers
	worldTimeManager.ClearTimer(CoinSetTimerHandle);
	worldTimeManager.SetTimer(CoinTimerHandle, this, &ACoinSpawner::SpawnCoin, CoinTimeInterval, true);
}

void ACoinSpawner::MoveSpawner()
{
	TargetLoc = FMath::Rand() % SpawnTransforms.Num();
}

void ACoinSpawner::SpawnCoin()
{
	if (FMath::Rand() % 100 < PowerUpChance)
	{
		SpawnPowerUp();
		NumCoinsToSpawn--;
	}
	else
	{
		FActorSpawnParameters spawnParams;

		FTransform coinTransform = SpawnTransforms[TargetLoc]->GetTransform();

		coinTransform.SetLocation(FVector(SpawnPoint, coinTransform.GetLocation().Y, coinTransform.GetLocation().Z));

		ACoin* spawnedCoin = GetWorld()->SpawnActor<ACoin>(CoinObject, coinTransform, spawnParams);

		if (spawnedCoin)
		{
			spawnedCoin->SetKillPoint(KillPoint);

			USphereComponent* coinSphere = Cast<USphereComponent>(spawnedCoin->GetComponentByClass(USphereComponent::StaticClass()));

			if (coinSphere)
			{
				float offset = coinSphere->GetUnscaledSphereRadius();
				spawnedCoin->AddActorLocalOffset(FVector(0.0f, 0.0f, offset));
			}

			NumCoinsToSpawn--;
		}
	}
	
	if (NumCoinsToSpawn <= 0)
	{
		FTimerManager& worldTimeManager = GetWorld()->GetTimerManager();
		worldTimeManager.SetTimer(CoinSetTimerHandle, this, &ACoinSpawner::SpawnCoinSet, CoinSetTimeInterval, false);
		worldTimeManager.ClearTimer(CoinTimerHandle);
	}
}

void ACoinSpawner::SpawnPowerUp()
{
	FActorSpawnParameters SpawnInfo;

	FTransform myTrans = SpawnTransforms[TargetLoc]->GetTransform();

	myTrans.SetLocation(FVector(SpawnPoint, myTrans.GetLocation().Y, myTrans.GetLocation().Z));

	ABountyDashPowerUp* newObs = GetWorld()->SpawnActor<ABountyDashPowerUp>(PowerUpObject, myTrans, SpawnInfo);
	
	if (newObs)
	{
		newObs->SetKillPoint(KillPoint);

		USphereComponent* powerUpSphere = Cast<USphereComponent>(newObs->GetComponentByClass(USphereComponent::StaticClass()));

		if (powerUpSphere)
		{
			float offset = powerUpSphere->GetUnscaledSphereRadius();

			newObs->AddActorLocalOffset(FVector(0.0f, 0.0f,	offset));
		}
	}
}
