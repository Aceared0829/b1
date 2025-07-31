// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include <b1/ThirdPlayer/ThirdPersonPlayerCharacter.h>
#include <Components/SphereComponent.h>
#include <GameFramework/Character.h>
#include <GameFramework/ProjectileMovementComponent.h>

#include "Kismet/GameplayStatics.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitialLifeSpan = 2.5f;

	ProjectileSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileSphere"));
	check(ProjectileSphere);
	ProjectileSphere->SetSphereRadius(10.0f);
	ProjectileSphere->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	SetRootComponent(ProjectileSphere);

	ProjectileStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileStaticMesh"));
	check(ProjectileStaticMesh);
	ProjectileStaticMesh->SetupAttachment(ProjectileSphere);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	check(ProjectileMovementComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	ProjectileMovementComponent->SetUpdatedComponent(ProjectileSphere);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit (UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (TObjectPtr<AThirdPersonPlayerCharacter> Player = Cast<AThirdPersonPlayerCharacter>(OtherActor))
	{
		if (TObjectPtr<UHealthComponent> HealthComponent = Player->FindComponentByClass<UHealthComponent>())
		{
			HealthComponent->TakeDamage(DamageAmount);
		}
		if (HitParticleSystem)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticleSystem, GetActorLocation());
		}
		Destroy();
	}
	if (TObjectPtr<UStaticMesh> StaticMesh = Cast<UStaticMesh>(OtherActor))
	{
		if (HitParticleSystem)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticleSystem, GetActorLocation());
		}
		Destroy();
	}
}

