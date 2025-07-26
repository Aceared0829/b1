// Fill out your copyright notice in the Description page of Project Settings.


#include "RestartUserWidget.h"

#include <b1/ThirdPlayer/ThirdPersonPlayerController.h>
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

void URestartUserWidget::NativeOnInitialized ()
{
	Super::NativeOnInitialized();
}

void URestartUserWidget::OnRestartButtonClicked ()
{
	//获取玩家控制器
	if(TObjectPtr<AThirdPersonPlayerController> PlayerController = Cast<AThirdPersonPlayerController>(GetOwningPlayer()))
	{
		//如果存在重启UI则隐藏
		PlayerController->HideRestartWidget();
	}
	//重新加载当前关卡（重新打开一次这个关卡）
	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}

void URestartUserWidget::OnCloseButtonClicked ()
{
	//获取玩家控制器并退出游戏
	if (AThirdPersonPlayerController* PlayerController = Cast<AThirdPersonPlayerController>(GetOwningPlayer()))
	{
		UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
	}
}
