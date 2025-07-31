// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThirdPersonPlayerController.generated.h"

class APlayerHUD;
class UHealthWidget;
class URestartUserWidget;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class B1_API AThirdPersonPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TArray<TSoftObjectPtr<UInputMappingContext>> InputMappingContexts;

	//��ʾ����UI
	void ShowRestartWidget();
	//��������UI
	void HideRestartWidget();
	//����Ѫ��UI
	void UpdateHealthWidget(float HealthPercent);
	//��������ʾʤ��UI
	void CreateAndShowVictoryWidget();

	UPROPERTY()
	TObjectPtr<APlayerHUD> PlayerHUD;
};
