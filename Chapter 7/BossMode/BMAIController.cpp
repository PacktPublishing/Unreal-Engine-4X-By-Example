// Fill out your copyright notice in the Description page of Project Settings.

#include "BossMode.h"
#include "BMBossCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BMAIController.h"

ABMAIController::ABMAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	check(BlackboardComp);

	BehaviourTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourTreeComp"));
	check(BehaviourTreeComp);
}

void ABMAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	ABMBossCharacter* possessedPawn = Cast<ABMBossCharacter>(InPawn);
	if (InPawn != nullptr)
	{
		BlackboardComp->InitializeBlackboard(*(possessedPawn->BehaviourTree->BlackboardAsset));
		BehaviourTreeComp->StartTree(*(possessedPawn->BehaviourTree));
	}
}


UBlackboardComponent* ABMAIController::GetBlackboard()
{
	return BlackboardComp;
}
