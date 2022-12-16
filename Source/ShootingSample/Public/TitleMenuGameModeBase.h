// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TitleMenuGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGSAMPLE_API ATitleMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UTitleWidget> titleWidget;

protected:
	virtual void BeginPlay() override;

private:
	class UTitleWidget* titleUI;
};
