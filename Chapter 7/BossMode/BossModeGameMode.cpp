// Fill out your copyright notice in the Description page of Project Settings.

#include "BossMode.h"
#include "BMHUD.h"
#include "BossModeGameMode.h"

ABossModeGameMode::ABossModeGameMode()
	:Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FPCharacter"));

	DefaultPawnClass = PlayerPawnClassFinder.Class;
	HUDClass = ABMHUD::StaticClass();

}


