// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShootingSampleGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.h"

void AShootingSampleGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (mainWidget != nullptr)
	{
		mainUI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);

		if (mainUI != nullptr)
		{
			mainUI->AddToViewport();
		}
	}
}

void AShootingSampleGameModeBase::AddScore(int32 point)
{
	currentScore += point;
}