// Fill out your copyright notice in the Description page of Project Settings.

#include "BossModeRemake.h"
#include "BMHUD.h"
#include "BossModeRemakeGameMode.h"



ABossModeRemakeGameMode::ABossModeRemakeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FPCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = ABMHUD::StaticClass();
}
