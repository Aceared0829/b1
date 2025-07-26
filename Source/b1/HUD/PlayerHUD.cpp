// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include <Blueprint/UserWidget.h>
#include "HealthWidget.h"
#include "RestartUserWidget.h"


void APlayerHUD::CreateRestartWidget()
{
	//创建并显示重启UI
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
			PlayerController->SetPause(true);//暂停游戏
			PlayerController->SetInputMode(FInputModeUIOnly());//设置输入模式为UI模式
			PlayerController->bShowMouseCursor = true;//显示鼠标光标
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
			PlayerController->SetPause(false);//取消暂停游戏
			PlayerController->SetInputMode(FInputModeGameOnly());//设置输入模式为游戏模式
			PlayerController->bShowMouseCursor = false;//隐藏鼠标光标
		}
	}
}

void APlayerHUD::CreateAndShowHealthWidget ()
{
	//创建并显示血量UI
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
