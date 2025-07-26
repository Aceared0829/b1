// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class USceneComponent;
class AProjectile;
class USphereComponent;

UCLASS()
class B1_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	FTimerHandle TimerHandle;

	// 敌人的"眼睛"，用来确定从哪里开始看
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Senses", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> VisualSenses;

	// 能看多远（厘米），默认6米
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Senses", meta = (AllowPrivateAccess = "true"))
	float VisibleDistance;

	// 水平视野有多宽（度数），默认150度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Senses", meta = (AllowPrivateAccess = "true"))
	float VisibleYawAngle;

	// 垂直视野有多高（度数），默认150度  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Senses", meta = (AllowPrivateAccess = "true"))
	float VisiblePitchAngle;

	// 转头的速度（度/秒），默认每秒20度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Senses", meta = (AllowPrivateAccess = "true"))
	float RotationSpeed;

	//生成的发射物位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Movement|Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> GenerateProjectilesLocation;

	//要生成的发射物（子弹、飞镖等等）、具体是什么由蓝图内进行设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Movement|Projectile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectile> ProjectilesSubclassOf;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Movement|Projectile", meta = (AllowPrivateAccess = "true"))
	float BetweenLaunchesTime = 1.0f;

	// 检查能不能看到某个目标
	// 会考虑距离、角度和是否被遮挡
	UFUNCTION(BlueprintCallable, Category = "Vision")
	bool CanSeeActor(AActor* TargetActor);

	// 慢慢转向目标，不会突然转过去
	UFUNCTION(BlueprintCallable, Category = "Vision")
	void TurnToActor(AActor* TargetActor,float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Fire();

	bool bIsFiring = false;
};
