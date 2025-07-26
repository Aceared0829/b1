// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class B1_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	TObjectPtr<USphereComponent> ProjectileSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	TObjectPtr<UStaticMeshComponent> ProjectileStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	float DamageAmount = 20.0f;

	UFUNCTION(BlueprintCallable)
	void OnHit (
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);
};
