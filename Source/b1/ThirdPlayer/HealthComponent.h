// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthDamage, float, DamageAmount, AActor*, ActorCauser);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthHeal, float, HealAmount, AActor*, ActorCauser);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthDeath);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class B1_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//最大生命值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	float MaxHealth;
	//当前生命值
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Core")
	float CurrentHealth;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//生命相关核心函数
	//收到伤害
	void TakeDamage(float DamageAmount);
	//回复生命
	void TakeHeal(float HealAmount);
	//死亡
	void Death();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthDamage OnHealthDamage;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthHeal OnHealthHeal;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthDeath OnHealthDeath;

	//状态相关
	bool bIsDead = false;

	//Setters方法
	void SetMaxHealth(const float NewMaxHealth);

	//Getters方法
	FORCEINLINE float GetMaxHealth () const { return MaxHealth; }
	FORCEINLINE float GetCurrentHealth () const { return CurrentHealth; }
	FORCEINLINE float GetHealthPercent () const { return CurrentHealth / MaxHealth; }
};
