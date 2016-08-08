// Fill out your copyright notice in the Description page of Project Settings.

#include "BountyDash.h"
#include "BountyDashGameMode.h"
#include "BountyDashCharacter.h"

ABountyDashGameMode::ABountyDashGameMode()
{
	// set default pawn class to our ABountyDashCharacter
	DefaultPawnClass = ABountyDashCharacter::StaticClass();

	numCoinsForSpeedIncrease = 5;
	gameSpeed = 10.0f;
	gameSpeedIncrease = 5.0f;
	gameLevel = 1;
}

void
ABountyDashGameMode::CharScoreUp(unsigned int charScore)
{
	if (charScore != 0 &&
		charScore % numCoinsForSpeedIncrease == 0)
	{
		gameSpeed += gameSpeedIncrease;
		gameLevel++;
	}
}

float
ABountyDashGameMode::GetInvGameSpeed()
{
	return -gameSpeed;
}

float
ABountyDashGameMode::GetGameSpeed()
{
	return gameSpeed;
}

int32 ABountyDashGameMode::GetGameLevel()
{
	return gameLevel;
}
