// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGSAMPLE_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* pauseText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* buttonResume;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* buttonQuit;

	UFUNCTION()
	void Resume();

	UFUNCTION()
	void Quit();

protected:
	virtual void NativeConstruct() override;
};
