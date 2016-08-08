// Fill out your copyright notice in the Description page of Project Settings.

#include "NS.h"
#include "Net/UnrealNetwork.h"
#include "NSGameState.h"

ANSGameState::ANSGameState()
{
	bInMenu = false;
}

void ANSGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANSGameState, bInMenu);
}



