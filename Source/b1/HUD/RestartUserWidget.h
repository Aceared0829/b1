// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RestartUserWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class B1_API URestartUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//初始化
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> RestartButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;
protected:
	//重置游戏
	UFUNCTION(BlueprintCallable)
	void OnRestartButtonClicked();

	//关闭游戏
	UFUNCTION(BlueprintCallable)
	void OnCloseButtonClicked();
};
