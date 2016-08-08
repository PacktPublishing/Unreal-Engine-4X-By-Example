// Fill out your copyright notice in the Description page of Project Settings.

#include "NS.h"
#include "Net/UnrealNetwork.h"
#include "NSPlayerState.h"


ANSPlayerState::ANSPlayerState(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	Health = 100.0f;
	Deaths = 0;
	Team = ETeam::BLUE_TEAM;
}


void ANSPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANSPlayerState, Health);
	DOREPLIFETIME(ANSPlayerState, Deaths);
	DOREPLIFETIME(ANSPlayerState, Team);
}
