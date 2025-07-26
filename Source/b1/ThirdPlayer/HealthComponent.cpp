// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	//最大生命值
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth; // 初始化当前生命值为最大生命值
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage (float DamageAmount)
{
	if (DamageAmount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Damage amount must be positive."));
		return; // 如果伤害量小于等于0，直接返回
	}
	//扣除血量，并把血量严格限制在0到最大生命值之间
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), CurrentHealth);
	OnHealthDamage.Broadcast(DamageAmount, GetOwner());// 广播伤害事件（调用该委托的子类，绑定之后，可以执行一些附带的逻辑）
	if (CurrentHealth == 0&&!bIsDead)
	{
		//如果当前生命值为0且角色还没死
		Death();
	}
}

void UHealthComponent::TakeHeal (float HealAmount)
{
	if (HealAmount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Heal amount must be positive."));
		return; // 如果回复量小于等于0，直接返回
	}
	if (CurrentHealth == 0||bIsDead)
	{
		return;
	}
	//回复生命值，并把生命值严格限制在0到最大生命值之间
	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), CurrentHealth);
	OnHealthHeal.Broadcast(HealAmount, GetOwner());// 广播回复事件（调用该委托的子类，绑定之后，可以执行一些附带的逻辑）
	if (CurrentHealth == MaxHealth)
	{
		UE_LOG(LogTemp, Warning, TEXT("Health is full."));
	}
}

void UHealthComponent::Death ()
{
	if (!bIsDead) // Check if already dead
	{
		bIsDead = true; // Set dead status
		UE_LOG(LogTemp, Warning, TEXT("Character is dead!"));
		OnHealthDeath.Broadcast();// 广播死亡事件
	}
}

void UHealthComponent::SetMaxHealth(const float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth); // 确保当前生命值不超过新的最大生命值
	if (CurrentHealth == MaxHealth)
	{
		UE_LOG(LogTemp, Warning, TEXT("Health is full."));
	}
}

