// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "NSGameMode.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	BLUE_TEAM,
	RED_TEAM
};

UCLASS(minimalapi)
class ANSGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ANSGameMode();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void SpawnTeams();
	void Respawn(class ANSCharacter* Character);
	void Spawn(class ANSCharacter* Character);

private:
	TArray<class ANSCharacter*> RedTeam;
	TArray<class ANSCharacter*> BlueTeam;

	TArray<class ANSSpawnPoint*> RedSpawns;
	TArray<class ANSSpawnPoint*> BlueSpawns;
	TArray<class ANSCharacter*> ToBeSpawned;

	bool bGameStarted;
	static bool bInGameMenu;
};



