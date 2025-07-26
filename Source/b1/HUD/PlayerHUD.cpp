// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include <Blueprint/UserWidget.h>
#include "HealthWidget.h"
#include "RestartUserWidget.h"


void APlayerHUD::CreateRestartWidget()
{
	//��������ʾ����UI
	if (TObjectPtr<APlayerController> PlayerController = GetOwningPlayerController())
	{
		if (RestartWidgetClass)
		{
			RestartUserWidget = CreateWidget<URestartUserWidget>(PlayerController, RestartWidgetClass);
		}
	}
}

void APlayerHUD::ShowRestartWidget()
{
	if (TObjectPtr<APlayerController> PlayerController = GetOwningPlayerController())
	{
		if (RestartWidgetClass)
		{
			PlayerController->SetPause(true);//��ͣ��Ϸ
			PlayerController->SetInputMode(FInputModeUIOnly());//��������ģʽΪUIģʽ
			PlayerController->bShowMouseCursor = true;//��ʾ�����
			if (RestartUserWidget)
			{
				RestartUserWidget->AddToViewport();
			}
		}
	}
}

void APlayerHUD::HideRestartWidget()
{
	if (TObjectPtr<APlayerController> PlayerController = GetOwningPlayerController())
	{
		if (RestartWidgetClass)
		{
			if (RestartUserWidget)
			{
				RestartUserWidget->RemoveFromParent();
			}
			PlayerController->SetPause(false);//ȡ����ͣ��Ϸ
			PlayerController->SetInputMode(FInputModeGameOnly());//��������ģʽΪ��Ϸģʽ
			PlayerController->bShowMouseCursor = false;//���������
		}
	}
}

void APlayerHUD::CreateAndShowHealthWidget ()
{
	//��������ʾѪ��UI
	if (TObjectPtr<APlayerController> PlayerController = GetOwningPlayerController())
	{
		if (HealthWidgetSubclassOf)
		{
			HealthWidget = CreateWidget<UHealthWidget>(PlayerController, HealthWidgetSubclassOf);
			if (HealthWidget)
			{
				HealthWidget->AddToViewport();
			}
		}
	}
}

void APlayerHUD::UpdateHealth (float HealthPercent)
{
	if (HealthWidget)
	{
		HealthWidget->UpdateHealthPercent(HealthPercent);
	}
}
