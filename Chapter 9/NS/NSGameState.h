// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "NSGameState.generated.h"

/**
 * 
 */
UCLASS()
class NS_API ANSGameState : public AGameState
{
	GENERATED_BODY()

public:
	ANSGameState();

	UPROPERTY(Replicated)
	bool bInMenu;
};

