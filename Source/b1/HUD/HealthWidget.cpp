// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthWidget.h"

#include <Components/ProgressBar.h>

void UHealthWidget::NativeOnInitialized ()
{
	Super::NativeOnInitialized();

}

void UHealthWidget::UpdateHealthPercent (float HealthPercent)
{
	if (HealthBar)//检测该进度条是否有效
	{
		//如果有效则设置进度条的百分比
		HealthBar->SetPercent(HealthPercent);
	}
}
