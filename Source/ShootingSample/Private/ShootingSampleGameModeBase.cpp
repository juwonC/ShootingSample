// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShootingSampleGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "MainWidget.h"
#include "MenuWidget.h"
#include "PauseWidget.h"
#include "LifeWidget.h"

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

	if (lifeWidget != nullptr)
	{
		lifeUI = CreateWidget<ULifeWidget>(GetWorld(), lifeWidget);
		
		if (lifeUI != nullptr)
		{
			lifeUI->AddToViewport();
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
	if (playerLife == 2)
	{
		lifeUI->lifeImage_0->SetColorAndOpacity(FColor(1, 1, 1, 0));
	}
	else if (playerLife == 1)
	{
		lifeUI->lifeImage_1->SetColorAndOpacity(FColor(1, 1, 1, 0));
	}
	else if (playerLife == 0)
	{
		lifeUI->lifeImage_2->SetColorAndOpacity(FColor(1, 1, 1, 0));
	}
}
