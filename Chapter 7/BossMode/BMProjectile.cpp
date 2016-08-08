// Fill out your copyright notice in the Description page of Project Settings.

#include "BossMode.h"
#include "BMProjectile.h"


// Sets default values
ABMProjectile::ABMProjectile()
{
	// Use a sphere as a simple collision representation
	ProjCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));

	ProjCollision->InitSphereRadius(10.0f);
	ProjCollision->BodyInstance.SetCollisionProfileName("BlockAll");
	ProjCollision->OnComponentHit.AddDynamic(this, &ABMProjectile::OnHit);

	OnDestroyed.AddDynamic(this, &ABMProjectile::OnDestoyedProjectile);

	ProjCollision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	ProjCollision->CanCharacterStepUpOn = ECB_No;

	RootComponent = ProjCollision;

	ProjMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("MeshComp"));

	ProjMesh->AttachTo(ProjCollision);
	ProjMesh->SetCollisionProfileName(TEXT("NoCollision"));

	ProjParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));

	ProjParticle->bAutoActivate = false;
	ProjParticle->AttachTo(ProjCollision);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));

	ProjMovement->UpdatedComponent = ProjCollision;
	ProjMovement->InitialSpeed = 3000.f;
	ProjMovement->MaxSpeed = 3000.f;
	ProjMovement->bRotationFollowsVelocity = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ABMProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor->GetClass()->IsChildOf(this->StaticClass()))
	{
		ProjCollision->SetCollisionProfileName(TEXT("NoCollision"));
		ProjCollision->bGenerateOverlapEvents = false;
		ProjMesh->SetVisibility(false);

		ProjParticle->Activate();
		ProjParticle->DetachFromParent(true);
	}
}

void ABMProjectile::OnDestoyedProjectile()
{

}



// Called when the game starts or when spawned
void ABMProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABMProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

