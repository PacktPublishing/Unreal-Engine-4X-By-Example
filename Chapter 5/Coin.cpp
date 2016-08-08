// Fill out your copyright notice in the Description page of Project Settings.

#include "BountyDash.h"
#include "BountyDashCharacter.h"
#include "BountyDashGameMode.h"
#include "Coin.h"


ACoin::ACoin()
{

}

void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mesh->AddLocalRotation(FRotator(5.0f, 0.0f, 0.0f));
}


void ACoin::MyOnActorOverlap(AActor* otherActor)
{
	if (otherActor->GetClass()->IsChildOf(AObstacle::StaticClass()))
	{
		USphereComponent* thisSphere = Cast<USphereComponent>(GetComponentByClass(USphereComponent::StaticClass()));

		USphereComponent* otherSpehre = Cast<USphereComponent>(otherActor->GetComponentByClass(USphereComponent::StaticClass()));

		if (otherSpehre)
		{
			AddActorLocalOffset(FVector(0.0f, 0.0f, (otherSpehre->GetUnscaledSphereRadius() * 2.0f) + Collider->GetUnscaledSphereRadius()));
		}
	}

	if (otherActor->GetClass()->IsChildOf(ABountyDashCharacter::StaticClass()))
	{
		ABountyDashCharacter* myChar = Cast<ABountyDashCharacter>(otherActor);

		myChar->ScoreUp();

		GetWorld()->DestroyActor(this);
	}
}



