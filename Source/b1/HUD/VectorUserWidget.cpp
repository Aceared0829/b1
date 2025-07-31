// Fill out your copyright notice in the Description page of Project Settings.


#include "VectorUserWidget.h"

#include "b1/ThirdPlayer/ThirdPersonPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UVectorUserWidget::OnQuitGameButtonClicked()
{
	if (QuitGameButton)
	{
		//��ȡ��ҿ��������˳���Ϸ
		if (AThirdPersonPlayerController* PlayerController = Cast<AThirdPersonPlayerController>(GetOwningPlayer()))
		{
			UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
		}
	}
}
