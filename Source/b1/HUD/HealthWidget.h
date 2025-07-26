// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class B1_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	//生命值进度条（主要控件）
	UPROPERTY(meta= (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	//核心逻辑，更新进度条的百分比
	UFUNCTION(BlueprintCallable)
	void UpdateHealthPercent(float HealthPercent);
	
};
