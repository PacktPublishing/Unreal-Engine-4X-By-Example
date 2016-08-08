// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "NS.h"
#include "NSGameMode.h"
#include "NSHUD.h"
#include "NSPlayerState.h"
#include "NSSpawnPoint.h"
#include "NSGameState.h"
#include "NSCharacter.h"

bool ANSGameMode::bInGameMenu = true;

ANSGameMode::ANSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	PlayerStateClass = ANSPlayerState::StaticClass();
	GameStateClass = ANSGameState::StaticClass();

	// use our custom HUD class
	HUDClass = ANSHUD::StaticClass();

	bReplicates = true;
	//bUseSeamlessTravel = true;
}

void ANSGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (Role == ROLE_Authority)
	{
		for (TActorIterator<ANSSpawnPoint> Iter(GetWorld()); Iter; ++Iter)
		{
			if ((*Iter)->Team == ETeam::RED_TEAM)
			{
				RedSpawns.Add(*Iter);
			}
			else
			{
				BlueSpawns.Add(*Iter);
			}
		}

		// Spawn the server
		APlayerController* thisCont = GetWorld()->GetFirstPlayerController();
		if (thisCont)
		{
			ANSCharacter* thisChar = Cast<ANSCharacter>(thisCont->GetPawn());
			BlueTeam.Add(thisChar);
			thisChar->SetTeam(ETeam::BLUE_TEAM);
			Spawn(thisChar); 
		}

		Cast<ANSGameState>(GameState)->bInMenu = bInGameMenu;
	}
}

void ANSGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (EndPlayReason == EEndPlayReason::Quit || EndPlayReason == EEndPlayReason::EndPlayInEditor)
	{
		bInGameMenu = true;
	}
}

void ANSGameMode::Tick(float DeltaSeconds)
{
	APlayerController* thisCont = GetWorld()->GetFirstPlayerController();

	if (Role == ROLE_Authority)
	{
		if (ToBeSpawned.Num() != 0)
		{
			for (auto charToSpawn : ToBeSpawned)
			{
				Spawn(charToSpawn);
			}
		}

		if (thisCont != nullptr && thisCont->IsInputKeyDown(EKeys::R))
		{
			bInGameMenu = false;
			GetWorld()->ServerTravel(L"/Game/FirstPersonCPP/Maps/FirstPersonExampleMap?Listen");
			Cast<ANSGameState>(GameState)->bInMenu = bInGameMenu;
		}
	}
}

void ANSGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ANSCharacter* Teamless = Cast<ANSCharacter>(NewPlayer->GetPawn());
	ANSPlayerState* NPlayerState = Cast<ANSPlayerState>(NewPlayer->PlayerState);

	if (Teamless != nullptr && NPlayerState != nullptr)
	{
		Teamless->SetNSPlayerState(NPlayerState);
	}
	// Assign Team and spawn
	if (Role == ROLE_Authority && Teamless != nullptr)
	{
		if (BlueTeam.Num() > RedTeam.Num())
		{
			RedTeam.Add(Teamless);
			NPlayerState->Team = ETeam::RED_TEAM;
		}
		else if (BlueTeam.Num() < RedTeam.Num())
		{
			BlueTeam.Add(Teamless);
			NPlayerState->Team = ETeam::BLUE_TEAM;
		}
		else // Teams are equal
		{
			BlueTeam.Add(Teamless);
			NPlayerState->Team = ETeam::BLUE_TEAM;
		}

		Teamless->CurrentTeam = NPlayerState->Team;
		Teamless->SetTeam(NPlayerState->Team);
		Spawn(Teamless);
	}
}


void ANSGameMode::Spawn(class ANSCharacter* Character)
{
	if (Role == ROLE_Authority)
	{
		// Find Spawn point that is not blocked
		TArray<ANSSpawnPoint*>* targetTeam = nullptr;

		if (Character->CurrentTeam == ETeam::BLUE_TEAM)
		{
			targetTeam = &BlueSpawns;
		}
		else
		{
			targetTeam = &RedSpawns;
		}

		for (auto Spawn : (*targetTeam))
		{
			if (!Spawn->GetBlocked())
			{
				// Remove from spawn queue if found and set location
				if (ToBeSpawned.Find(Character) != INDEX_NONE)
				{
					ToBeSpawned.Remove(Character);
				}

				// Otherwise set actor location
				Character->SetActorLocation(Spawn->GetActorLocation());
				Spawn->UpdateOverlaps();

				return;
			}
		}

		if (ToBeSpawned.Find(Character) == INDEX_NONE)
		{
			ToBeSpawned.Add(Character);
		}
	}
}


void ANSGameMode::Respawn(class ANSCharacter* Character)
{
	if (Role == ROLE_Authority)
	{
		AController* thisPC = Character->GetController();
		Character->DetachFromControllerPendingDestroy();

		ANSCharacter* newChar = Cast<ANSCharacter>(GetWorld()->SpawnActor(DefaultPawnClass));

		if (newChar)
		{
			thisPC->Possess(newChar);
			ANSPlayerState* thisPS = Cast<ANSPlayerState>(newChar->GetController()->PlayerState);

			newChar->CurrentTeam = thisPS->Team;
			newChar->SetNSPlayerState(thisPS);

			Spawn(newChar);

			newChar->SetTeam(newChar->GetNSPlayerState()->Team);
		}
	}
}
