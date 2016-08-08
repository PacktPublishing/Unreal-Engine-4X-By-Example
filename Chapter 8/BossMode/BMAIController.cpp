// Fill out your copyright notice in the Description page of Project Settings.

#include "BossMode.h"
#include "BMBossCharacter.h"
#include "BMCharacter.h"
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

void ABMAIController::Tick(float DeltaTime)
{
	EBossState bossState;

	if (ControlledChar->GetHealth() > 66.0f)
	{
		bossState = EBossState::BS_FOLLOW;
	}
	else if (ControlledChar->GetHealth() > 33.0f)
	{
		bossState = EBossState::BS_TURRET;
	}
	else
	{
		bossState = EBossState::BS_FINAL;
	}

	BlackboardComp->SetValue<UBlackboardKeyType_Enum>(BossStateBlackboardKey, (uint8)bossState);

	if (bIsTracking && Target != nullptr)
	{
		FVector CharLoc = ControlledChar->GetActorLocation();

		FVector dirToTarget = Target->GetActorLocation() - CharLoc;
		FRotator rotToTarget = dirToTarget.Rotation();

		ControlledChar->SetActorRotation(FMath::Lerp(ControlledChar->GetActorRotation(), rotToTarget, DeltaTime * 5));
	}

}

void ABMAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	ControlledChar = Cast<ABMBossCharacter>(InPawn);

	if (InPawn != nullptr)
	{
		BlackboardComp->InitializeBlackboard(*(ControlledChar->BehaviourTree->BlackboardAsset));
		BehaviourTreeComp->StartTree(*(ControlledChar->BehaviourTree));

		BossStateBlackboardKey = BlackboardComp->GetKeyID("BossState");
		TargetBlackboardKey = BlackboardComp->GetKeyID("TargetToFollow");
	}
}

UBlackboardComponent* ABMAIController::GetBlackboard()
{
	return BlackboardComp;
}

void ABMAIController::TrackToTarget()
{
	Target = Cast<ABMCharacter>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(TargetBlackboardKey));

	if (Target != nullptr)
	{
		bIsTracking = true;
	}
}

void ABMAIController::StopTrack()
{
	bIsTracking = false;
	Target = nullptr;
}

void ABMAIController::FireMissles()
{
	if (Target)
	{
		// Find Launch points (5)
		for (int i = 1; i <= 5; ++i)
		{
			float fAngle = 16 + i * 26;
			FVector circlePoint;

			circlePoint.Y = (FMath::Cos(PI / 2) * FMath::Sin((fAngle * PI / 180.0f)));
			circlePoint.Z = (FMath::Sin(PI / 2) * FMath::Sin((fAngle * PI / 180.0f)));
			circlePoint.X = (FMath::Cos((fAngle * PI / 180.0f)));

			FRotator charRot = ControlledChar->GetActorRotation();
			charRot.Yaw = charRot.Yaw + 90.0f;
			circlePoint = charRot.RotateVector(circlePoint);

			FVector SpawnLoc = ControlledChar->GetActorLocation() + circlePoint * 180.0f;
			ABMProjectile* pThisProj = GetWorld()->SpawnActor<ABMProjectile>(Target->ProjectileClass, SpawnLoc,	ControlledChar->GetActorRotation());

			pThisProj->GetProjectileMovement()->HomingTargetComponent =	Cast<USceneComponent>(Target->GetComponentByClass(USceneComponent::StaticClass()));
		}
	}
}
