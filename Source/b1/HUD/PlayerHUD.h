// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

class UVectorUserWidget;
class UHealthWidget;
class URestartUserWidget;
/**
 * 
 */
UCLASS()
class B1_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = HUD)
	TSubclassOf<UHealthWidget> HealthWidgetSubclassOf;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TObjectPtr<UHealthWidget> HealthWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HUD)
	TSubclassOf<URestartUserWidget> RestartWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HUD)
	TObjectPtr<URestartUserWidget> RestartUserWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<UVectorUserWidget> VectorUserWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TObjectPtr<UVectorUserWidget> VectorUserWidget;

	//创建并显示胜利UI
	void CreateAndShowVectorWidget();

	//创建重启UI
	void CreateRestartWidget();
	//显示重启UI
	void ShowRestartWidget();
	void HideRestartWidget();

	//创建并显示血量UI
	void CreateAndShowHealthWidget();
	void UpdateHealth(float HealthPercent);
};
