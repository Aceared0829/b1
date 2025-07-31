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

	// ���˵�"�۾�"������ȷ�������￪ʼ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Senses", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> VisualSenses;

	// �ܿ���Զ�����ף���Ĭ��6��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Senses", meta = (AllowPrivateAccess = "true"))
	float VisibleDistance;

	// ˮƽ��Ұ�ж����������Ĭ��150��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Senses", meta = (AllowPrivateAccess = "true"))
	float VisibleYawAngle;

	// ��ֱ��Ұ�ж�ߣ���������Ĭ��150��  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Senses", meta = (AllowPrivateAccess = "true"))
	float VisiblePitchAngle;

	// תͷ���ٶȣ���/�룩��Ĭ��ÿ��20��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Senses", meta = (AllowPrivateAccess = "true"))
	float RotationSpeed;

	//���ɵķ�����λ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Movement|Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> ProjectilesLocation;

	//���ɵķ�����λ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Movement|Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> GenerateProjectilesLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Movement|Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> PlayParticleLocation;
	

	//Ҫ���ɵķ�����ӵ������ڵȵȣ���������ʲô����ͼ�ڽ�������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Movement|Projectile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectile> ProjectilesSubclassOf;

	//�����ļ��ʱ�䣨�룩��Ĭ��1��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Movement|Projectile", meta = (AllowPrivateAccess = "true"))
	float BetweenLaunchesTime = 1.0f;

	//��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Movement|Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> FireSound;
	//����������˥������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Movement|Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundAttenuation> FireSoundAttenuation;

	//����������Ч
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core|Movement|Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> FireParticleSystem;

	// ����ܲ��ܿ���ĳ��Ŀ��
	// �ῼ�Ǿ��롢�ǶȺ��Ƿ��ڵ�
	UFUNCTION(BlueprintCallable, Category = "Vision")
	bool CanSeeActor(AActor* TargetActor);

	// ����ת��Ŀ�꣬����ͻȻת��ȥ
	UFUNCTION(BlueprintCallable, Category = "Vision")
	void TurnToActor(AActor* TargetActor,float DeltaTime);

	//����
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Fire();

	//���ſ�����������Ч
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void PlaySoundAndParticle();

	bool bIsFiring = false;
};
