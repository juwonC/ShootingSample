// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGSAMPLE_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* scoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* scoreData;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* lifeImage_0;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* lifeImage_1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* lifeImage_2;
};
