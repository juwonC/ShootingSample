// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShootingSampleGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "MainWidget.h"
#include "MenuWidget.h"
#include "PauseWidget.h"

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

void AShootingSampleGameModeBase::GameOver()
{
	if (menuWidget != nullptr)
	{
		menuUI = CreateWidget<UMenuWidget>(GetWorld(), menuWidget);

		if (menuUI != nullptr)
		{
			menuUI->AddToViewport();

			UGameplayStatics::SetGamePaused(GetWorld(), true);

			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		}
	}
}

void AShootingSampleGameModeBase::PauseGame()
{
	if (pauseWidget != nullptr)
	{
		pauseUI = CreateWidget<UPauseWidget>(GetWorld(), pauseWidget);

		if (pauseUI != nullptr)
		{
			pauseUI->AddToViewport();
			
			UGameplayStatics::SetGamePaused(GetWorld(), true);

			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		}
	}
}

void AShootingSampleGameModeBase::PrintScore()
{
	if (mainUI != nullptr)
	{
		mainUI->scoreData->SetText(FText::AsNumber(currentScore));
	}
}

void AShootingSampleGameModeBase::AddScore(int32 point)
{
	currentScore += point;

	PrintScore();
}

void AShootingSampleGameModeBase::PlayerOnHit(int32 life)
{
	playerLife -= life;

	UpdateLifeImage();
}

void AShootingSampleGameModeBase::UpdateLifeImage()
{
	if (playerLife == 3)
	{
		mainUI->lifeImage_0->SetColorAndOpacity(FColor(1, 1, 1, 1));
		mainUI->lifeImage_1->SetColorAndOpacity(FColor(1, 1, 1, 1));
		mainUI->lifeImage_2->SetColorAndOpacity(FColor(1, 1, 1, 1));
	}
	
	if (playerLife == 2)
	{
		mainUI->lifeImage_0->SetColorAndOpacity(FColor(1, 1, 1, 0));
	}
	else if (playerLife == 1)
	{
		mainUI->lifeImage_1->SetColorAndOpacity(FColor(1, 1, 1, 0));
	}
	else if (playerLife == 0)
	{
		mainUI->lifeImage_2->SetColorAndOpacity(FColor(1, 1, 1, 0));
	}
}
