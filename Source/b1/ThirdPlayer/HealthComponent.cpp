// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	//�������ֵ
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth; // ��ʼ����ǰ����ֵΪ�������ֵ
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
		return; // ����˺���С�ڵ���0��ֱ�ӷ���
	}
	//�۳�Ѫ��������Ѫ���ϸ�������0���������ֵ֮��
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), CurrentHealth);
	OnHealthDamage.Broadcast(DamageAmount, GetOwner());// �㲥�˺��¼������ø�ί�е����࣬��֮�󣬿���ִ��һЩ�������߼���
	if (CurrentHealth == 0&&!bIsDead)
	{
		//�����ǰ����ֵΪ0�ҽ�ɫ��û��
		Death();
	}
}

void UHealthComponent::TakeHeal (float HealAmount)
{
	if (HealAmount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Heal amount must be positive."));
		return; // ����ظ���С�ڵ���0��ֱ�ӷ���
	}
	if (CurrentHealth == 0||bIsDead)
	{
		return;
	}
	//�ظ�����ֵ����������ֵ�ϸ�������0���������ֵ֮��
	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), CurrentHealth);
	OnHealthHeal.Broadcast(HealAmount, GetOwner());// �㲥�ظ��¼������ø�ί�е����࣬��֮�󣬿���ִ��һЩ�������߼���
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
		OnHealthDeath.Broadcast();// �㲥�����¼�
	}
}

void UHealthComponent::SetMaxHealth(const float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth); // ȷ����ǰ����ֵ�������µ��������ֵ
	if (CurrentHealth == MaxHealth)
	{
		UE_LOG(LogTemp, Warning, TEXT("Health is full."));
	}
}

