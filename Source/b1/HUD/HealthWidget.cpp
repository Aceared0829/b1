// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthWidget.h"

#include <Components/ProgressBar.h>

void UHealthWidget::NativeOnInitialized ()
{
	Super::NativeOnInitialized();

}

void UHealthWidget::UpdateHealthPercent (float HealthPercent)
{
	if (HealthBar)//���ý������Ƿ���Ч
	{
		//�����Ч�����ý������İٷֱ�
		HealthBar->SetPercent(HealthPercent);
	}
}
