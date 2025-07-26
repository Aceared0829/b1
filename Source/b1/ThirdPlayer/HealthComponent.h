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
	//�������ֵ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	float MaxHealth;
	//��ǰ����ֵ
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Core")
	float CurrentHealth;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//������غ��ĺ���
	//�յ��˺�
	void TakeDamage(float DamageAmount);
	//�ظ�����
	void TakeHeal(float HealAmount);
	//����
	void Death();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthDamage OnHealthDamage;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthHeal OnHealthHeal;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthDeath OnHealthDeath;

	//״̬���
	bool bIsDead = false;

	//Setters����
	void SetMaxHealth(const float NewMaxHealth);

	//Getters����
	FORCEINLINE float GetMaxHealth () const { return MaxHealth; }
	FORCEINLINE float GetCurrentHealth () const { return CurrentHealth; }
	FORCEINLINE float GetHealthPercent () const { return CurrentHealth / MaxHealth; }
};
