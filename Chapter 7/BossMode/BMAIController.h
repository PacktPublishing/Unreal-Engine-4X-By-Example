// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BMAIController.generated.h"

/**
 * 
 */
UCLASS()
class BOSSMODE_API ABMAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABMAIController();
	virtual void Possess(APawn* InPawn) override;

	UBlackboardComponent* GetBlackboard();

protected:
	UPROPERTY(BlueprintReadWrite, Category = Behaviour)
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(BlueprintReadWrite, Category = Behaviour)
	class UBehaviorTreeComponent* BehaviourTreeComp;
};
