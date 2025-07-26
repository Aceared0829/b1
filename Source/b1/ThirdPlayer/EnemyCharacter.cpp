// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include <b1/Actor/Projectile.h>
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>

#include "gtest/gtest-matchers.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter ()
{
	// ÿ֡������Tick���������Ҫ���Թص�����������
	PrimaryActorTick.bCanEverTick = true;

	// �����Ӿ���֪����������ǵ��˵��۾�
	VisualSenses = CreateDefaultSubobject<USphereComponent>(TEXT("VisualSenses"));
	check(VisualSenses);
	VisualSenses->SetSphereRadius(10.0f);
	VisualSenses->SetRelativeLocation(FVector{0.0f, 0.0f, 50.0f + BaseEyeHeight});
	VisualSenses->Activate(true);
	VisualSenses->SetupAttachment(RootComponent);

	// ����Ĭ�ϵ��Ӿ�����
	VisibleDistance   = 600.0f; // Ĭ�Ͽ��Ӿ���Ϊ����
	VisibleYawAngle   = 150.0f; // Ĭ��ˮƽ�ӽ�Ϊ150��
	VisiblePitchAngle = 150.0f; // Ĭ�ϴ�ֱ�ӽ�Ϊ150��
	RotationSpeed     = 20.0f; // ת���ٶȣ�ÿ��20��
	// �����ӵ���λ������������������ӵ�������ͼ����Ե���λ�ã�������ǰ
	GenerateProjectilesLocation = CreateDefaultSubobject<USceneComponent>(TEXT("GenerateProjectilesLocation"));
	check(GenerateProjectilesLocation);
	GenerateProjectilesLocation->SetRelativeLocation(FVector{ 0.0f,0.0f,40.0f });
	GenerateProjectilesLocation->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay ()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyCharacter::Tick (float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ACharacter* TargetCharacter = UGameplayStatics::GetPlayerCharacter(this, 0))
	{
		if (CanSeeActor(TargetCharacter))
		{
			TurnToActor(TargetCharacter, DeltaTime);
			// ������ڿ���״̬����ʼ����
			if (!bIsFiring)
			{
				bIsFiring = true;
				// ����ѭ����ʱ��
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyCharacter::Fire, BetweenLaunchesTime, true);
			}
		}
		else
		{
			// ���֮ǰ�ڿ�����ֹͣ
			if (bIsFiring)
			{
				bIsFiring = false;
				GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			}
		}
	}
}

/**
 * �������ܲ��ܿ���ĳ��Ŀ��
 * ������ʵ��һ����Ҫ���ü�һ��������Ҫ���㼸��������
 * ���벻��̫Զ��Ҫ����Ұ��Χ�ڣ��м䲻���ж�������
 */
bool AEnemyCharacter::CanSeeActor (AActor* TargetActor)
{
	// �ȼ��������Ķ���
	if (!TargetActor || !VisualSenses)
	{
		return false; // Ŀ�겻���ڻ����۾����ˣ���Ȼ������
	}

	// ��ȡ�۾�λ�ú�Ŀ��λ��
	const FVector StartLocation  = VisualSenses->GetComponentLocation();
	const FVector TargetLocation = TargetActor->GetActorLocation();

	// �������Ƿ�̫Զ
	// ��ƽ������Ƚϣ��������ÿ����ţ���ʡ����
	const float DistanceFromTargetActorSquare = (TargetLocation - StartLocation).SizeSquared();
	const float VisibleDistanceSquared        = FMath::Square(VisibleDistance);

	if (VisibleDistanceSquared < DistanceFromTargetActorSquare)
	{
		return false; // ̫Զ�ˣ�������
	}

	// ���Ŀ���Ƿ�����Ұ�Ƕ���
	FVector AIForwardVector = GetActorForwardVector();
	FVector DirectionToTarget = (TargetLocation - StartLocation).GetSafeNormal();

	// ���������õ��нǵ�����ֵ
	float DotProduct = FVector::DotProduct(AIForwardVector, DirectionToTarget);

	// ����Ұ���ת��Ϊ����ֵ
	// ע�⣺����� VisibleYawAngle �����ӽǣ���Ҫ�ð��
	float VisionConeCosine = FMath::Cos(FMath::DegreesToRadians(VisibleYawAngle / 2.0f));

	// ������С����Ұ�ǵ�����ֵ��˵���н�̫������Ұ��
	if (DotProduct < VisionConeCosine)
	{
		return false; // Ŀ������Ұ�Ƕ�֮��
	}

	// ������м���û�ж�������
	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	// ���߼��ʱ�����Լ���Ŀ�꣬��Ȼ�ᱻ�Լ���ס
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.AddIgnoredActor(TargetActor);

	// ���۾���Ŀ�귢��һ�����߿�����û���ϰ���
	const bool bHit = GetWorld()->LineTraceSingleByChannel(
	                                                       HitResult,
	                                                       StartLocation, // �����￪ʼ
	                                                       TargetLocation, // ���������
	                                                       ECC_Visibility, // �ÿɼ��Լ��
	                                                       CollisionQueryParams
	                                                      );

	// �������û����������˵������������ܿ���
	return !bHit;
}

/**
 * �õ�������ת��Ŀ��
 * ������תͷ������һ��������˲��ת��ȥ������ƽ����ת��ȥ
 */
void AEnemyCharacter::TurnToActor (AActor* TargetActor, float DeltaTime)
{
	if (!TargetActor)
	{
		return; // û��Ŀ�������
	}

	// ��ȡ�Լ���Ŀ���λ��
	const FVector StartLocation = this->GetActorLocation();
	const FVector EndLocation   = TargetActor->GetActorLocation();

	// ������Ҫת��ĽǶȣ�ֻ����ˮƽ�������ת������תͷ��
	// ����Ҫ���µ�ͷ������Pitch��Roll����Ϊ0
	const FRotator TargetRotation  = FRotator{0.0f, (EndLocation - StartLocation).Rotation().Yaw, 0.0f};
	const FRotator CurrentRotation = GetActorRotation();

	// �ò�ֵ��ת����ƽ���������ͻأ
	const FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, RotationSpeed);

	// Ӧ���µ���ת
	this->SetActorRotation(NewRotation);
}

void AEnemyCharacter::Fire ()
{
	if (!ProjectilesSubclassOf)
	{
		return;
	}
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = GetInstigator();

	//���ض�λ�����ɷ�����
	AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectilesSubclassOf, 
		GenerateProjectilesLocation->GetComponentLocation(), 
		GenerateProjectilesLocation->GetComponentRotation(), 
		SpawnParameters);
	if (Projectile)
	{
		FVector LaunchDirection = GenerateProjectilesLocation->GetComponentRotation().Vector();

		if (Projectile->ProjectileMovementComponent)
		{
			// �õ������ƶ��������������� InitialSpeed �������ṩ�ķ�������ʼ�ƶ���
			Projectile->ProjectileMovementComponent->Velocity = LaunchDirection * Projectile->ProjectileMovementComponent->InitialSpeed;
			// ȷ������Ǽ���״̬
			Projectile->ProjectileMovementComponent->Activate();
		}
	}
}

