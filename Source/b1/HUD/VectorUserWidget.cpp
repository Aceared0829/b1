// Fill out your copyright notice in the Description page of Project Settings.


#include "VectorUserWidget.h"

#include "b1/ThirdPlayer/ThirdPersonPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UVectorUserWidget::OnQuitGameButtonClicked()
{
	if (QuitGameButton)
	{
		//获取玩家控制器并退出游戏
		if (AThirdPersonPlayerController* PlayerController = Cast<AThirdPersonPlayerController>(GetOwningPlayer()))
		{
			UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
		}
	}
}
