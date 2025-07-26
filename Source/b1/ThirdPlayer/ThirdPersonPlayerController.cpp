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
			for (const TSoftObjectPtr<UInputMappingContext>& Context : InputMappingContexts) //遍历输入映射上下文数组
			{
				if (!Context.IsValid()) //检查软指针是否有效
				{
					UE_LOG(LogTemp, Warning, TEXT("InputMappingContext is not valid!"));
					continue; //如果无效，跳过当前循环
				}
				InputSubsystem->AddMappingContext(Context.Get(), 0); //使用Get()方法获取软指针指向的对象
			}
		}
	}
	PlayerHUD = Cast<APlayerHUD>(GetHUD());
	if (PlayerHUD)
	{
		PlayerHUD->CreateAndShowHealthWidget(); //创建并显示血量UI
		PlayerHUD->CreateRestartWidget();//创建重启UI
	}
}

void AThirdPersonPlayerController::ShowRestartWidget()
{
	if (PlayerHUD)
	{
		PlayerHUD->ShowRestartWidget();//显示重启UI
	}
}

void AThirdPersonPlayerController::HideRestartWidget()
{
	if (PlayerHUD)
	{
		PlayerHUD->HideRestartWidget();//隐藏重启UI
	}
}

void AThirdPersonPlayerController::UpdateHealthWidget (float HealthPercent)
{
	if (PlayerHUD)
	{
		PlayerHUD->UpdateHealth(HealthPercent); //更新血量UI
	}
}
