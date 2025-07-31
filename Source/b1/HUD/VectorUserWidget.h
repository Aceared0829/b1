// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VectorUserWidget.generated.h"

class UButton;

UCLASS()
class B1_API UVectorUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitGameButton;

protected:
	UFUNCTION(BlueprintCallable)
	void OnQuitGameButtonClicked();
};
