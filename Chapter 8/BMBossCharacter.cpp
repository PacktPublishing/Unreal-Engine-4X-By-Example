// Fill out your copyright notice in the Description page of Project Settings.

#include "BossModeRemake.h"
#include "BMBossCharacter.h"


// Sets default values
ABMBossCharacter::ABMBossCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 100.0f;
}

float ABMBossCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	Health -= Damage;

	return Damage;
}

const float ABMBossCharacter::GetHealth()
{
	return Health;
}