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
	// 每帧都调用Tick，如果不需要可以关掉来提升性能
	PrimaryActorTick.bCanEverTick = true;

	// 创建视觉感知组件，就像是敌人的眼睛
	VisualSenses = CreateDefaultSubobject<USphereComponent>(TEXT("VisualSenses"));
	check(VisualSenses);
	VisualSenses->SetSphereRadius(10.0f);
	VisualSenses->SetRelativeLocation(FVector{0.0f, 0.0f, 50.0f + BaseEyeHeight});
	VisualSenses->Activate(true);
	VisualSenses->SetupAttachment(RootComponent);

	// 设置默认的视觉参数
	VisibleDistance   = 600.0f; // 默认可视距离为六米
	VisibleYawAngle   = 150.0f; // 默认水平视角为150度
	VisiblePitchAngle = 150.0f; // 默认垂直视角为150度
	RotationSpeed     = 20.0f; // 转向速度，每秒20度
	// 生成子弹的位置组件，在这里生成子弹，在蓝图面可以调整位置，比如胸前
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
			// 如果不在开火状态，则开始开火
			if (!bIsFiring)
			{
				bIsFiring = true;
				// 设置循环定时器
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyCharacter::Fire, BetweenLaunchesTime, true);
			}
		}
		else
		{
			// 如果之前在开火，则停止
			if (bIsFiring)
			{
				bIsFiring = false;
				GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			}
		}
	}
}

/**
 * 检查敌人能不能看到某个目标
 * 就像现实中一样，要看得见一个东西需要满足几个条件：
 * 距离不能太远，要在视野范围内，中间不能有东西挡着
 */
bool AEnemyCharacter::CanSeeActor (AActor* TargetActor)
{
	// 先检查最基本的东西
	if (!TargetActor || !VisualSenses)
	{
		return false; // 目标不存在或者眼睛坏了，当然看不见
	}

	// 获取眼睛位置和目标位置
	const FVector StartLocation  = VisualSenses->GetComponentLocation();
	const FVector TargetLocation = TargetActor->GetActorLocation();

	// 检查距离是否太远
	// 用平方距离比较，这样不用开根号，节省性能
	const float DistanceFromTargetActorSquare = (TargetLocation - StartLocation).SizeSquared();
	const float VisibleDistanceSquared        = FMath::Square(VisibleDistance);

	if (VisibleDistanceSquared < DistanceFromTargetActorSquare)
	{
		return false; // 太远了，看不见
	}

	// 检查目标是否在视野角度内
	FVector AIForwardVector = GetActorForwardVector();
	FVector DirectionToTarget = (TargetLocation - StartLocation).GetSafeNormal();

	// 计算点积，得到夹角的余弦值
	float DotProduct = FVector::DotProduct(AIForwardVector, DirectionToTarget);

	// 将视野半角转换为余弦值
	// 注意：这里的 VisibleYawAngle 是总视角，需要用半角
	float VisionConeCosine = FMath::Cos(FMath::DegreesToRadians(VisibleYawAngle / 2.0f));

	// 如果点积小于视野角的余弦值，说明夹角太大，在视野外
	if (DotProduct < VisionConeCosine)
	{
		return false; // 目标在视野角度之外
	}

	// 最后检查中间有没有东西挡着
	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	// 射线检测时忽略自己和目标，不然会被自己挡住
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.AddIgnoredActor(TargetActor);

	// 从眼睛向目标发射一条射线看看有没有障碍物
	const bool bHit = GetWorld()->LineTraceSingleByChannel(
	                                                       HitResult,
	                                                       StartLocation, // 从这里开始
	                                                       TargetLocation, // 到这里结束
	                                                       ECC_Visibility, // 用可见性检测
	                                                       CollisionQueryParams
	                                                      );

	// 如果射线没碰到东西，说明视线清楚，能看见
	return !bHit;
}

/**
 * 让敌人慢慢转向目标
 * 就像人转头看东西一样，不会瞬间转过去，而是平滑地转过去
 */
void AEnemyCharacter::TurnToActor (AActor* TargetActor, float DeltaTime)
{
	if (!TargetActor)
	{
		return; // 没有目标就算了
	}

	// 获取自己和目标的位置
	const FVector StartLocation = this->GetActorLocation();
	const FVector EndLocation   = TargetActor->GetActorLocation();

	// 计算需要转向的角度，只关心水平方向的旋转（左右转头）
	// 不需要上下点头，所以Pitch和Roll都设为0
	const FRotator TargetRotation  = FRotator{0.0f, (EndLocation - StartLocation).Rotation().Yaw, 0.0f};
	const FRotator CurrentRotation = GetActorRotation();

	// 用插值让转向变得平滑，不会很突兀
	const FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, RotationSpeed);

	// 应用新的旋转
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

	//在特定位置生成发射物
	AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectilesSubclassOf, 
		GenerateProjectilesLocation->GetComponentLocation(), 
		GenerateProjectilesLocation->GetComponentRotation(), 
		SpawnParameters);
	if (Projectile)
	{
		FVector LaunchDirection = GenerateProjectilesLocation->GetComponentRotation().Vector();

		if (Projectile->ProjectileMovementComponent)
		{
			// 让弹射物移动组件根据其自身的 InitialSpeed 和我们提供的方向来开始移动。
			Projectile->ProjectileMovementComponent->Velocity = LaunchDirection * Projectile->ProjectileMovementComponent->InitialSpeed;
			// 确保组件是激活状态
			Projectile->ProjectileMovementComponent->Activate();
		}
	}
}

