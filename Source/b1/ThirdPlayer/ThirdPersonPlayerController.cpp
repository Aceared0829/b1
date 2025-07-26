// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonPlayerController.h"

#include <EnhancedInputSubsystems.h>
#include <InputMappingContext.h>
#include <b1/HUD/PlayerHUD.h>
#include <b1/HUD/RestartUserWidget.h>
#include <Blueprint/UserWidget.h>


void AThirdPersonPlayerController::BeginPlay ()
{
	Super::BeginPlay();
	if (const TObjectPtr<ULocalPlayer> LocalPlayer = Cast<ULocalPlayer>(GetLocalPlayer()))
	{
		if (const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			for (const TSoftObjectPtr<UInputMappingContext>& Context : InputMappingContexts) //��������ӳ������������
			{
				if (!Context.IsValid()) //�����ָ���Ƿ���Ч
				{
					UE_LOG(LogTemp, Warning, TEXT("InputMappingContext is not valid!"));
					continue; //�����Ч��������ǰѭ��
				}
				InputSubsystem->AddMappingContext(Context.Get(), 0); //ʹ��Get()������ȡ��ָ��ָ��Ķ���
			}
		}
	}
	PlayerHUD = Cast<APlayerHUD>(GetHUD());
	if (PlayerHUD)
	{
		PlayerHUD->CreateAndShowHealthWidget(); //��������ʾѪ��UI
		PlayerHUD->CreateRestartWidget();//��������UI
	}
}

void AThirdPersonPlayerController::ShowRestartWidget()
{
	if (PlayerHUD)
	{
		PlayerHUD->ShowRestartWidget();//��ʾ����UI
	}
}

void AThirdPersonPlayerController::HideRestartWidget()
{
	if (PlayerHUD)
	{
		PlayerHUD->HideRestartWidget();//��������UI
	}
}

void AThirdPersonPlayerController::UpdateHealthWidget (float HealthPercent)
{
	if (PlayerHUD)
	{
		PlayerHUD->UpdateHealth(HealthPercent); //����Ѫ��UI
	}
}
