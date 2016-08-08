// Fill out your copyright notice in the Description page of Project Settings.

#include "BountyDash.h"
#include "BountyDashParticle.h"



ABountyDashParticle::ABountyDashParticle()
{
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explosion"));
	check(ParticleSystem);

	ConstructorHelpers::FObjectFinder<UParticleSystem> thisSys(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));

	if (thisSys.Succeeded())
	{
		ParticleSystem->SetTemplate(thisSys.Object);
	}

	ParticleSystem->AttachTo(RootComponent);
}
