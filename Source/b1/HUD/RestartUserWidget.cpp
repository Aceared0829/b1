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
	//��ȡ��ҿ�����
	if(TObjectPtr<AThirdPersonPlayerController> PlayerController = Cast<AThirdPersonPlayerController>(GetOwningPlayer()))
	{
		//�����������UI������
		PlayerController->HideRestartWidget();
	}
	//���¼��ص�ǰ�ؿ������´�һ������ؿ���
	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}

void URestartUserWidget::OnCloseButtonClicked ()
{
	//��ȡ��ҿ��������˳���Ϸ
	if (AThirdPersonPlayerController* PlayerController = Cast<AThirdPersonPlayerController>(GetOwningPlayer()))
	{
		UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
	}
}
