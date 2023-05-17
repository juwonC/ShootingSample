// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShootingSampleGameModeBase.h"
#include "ShootingPlayer.h"
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
	// 플레이어 라이프에 따라 라이프 UI 알파값을 따로 지정해 화면에 표시하거나 숨김
	
	if (playerLife == 3)
	{
		mainUI->lifeImage_0->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
		mainUI->lifeImage_1->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
		mainUI->lifeImage_2->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
	else if (playerLife == 2)
	{
		mainUI->lifeImage_0->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f));
		mainUI->lifeImage_1->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
		mainUI->lifeImage_2->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
	else if (playerLife == 1)
	{
		mainUI->lifeImage_0->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f));
		mainUI->lifeImage_1->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f));
		mainUI->lifeImage_2->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
	else if (playerLife == 0)
	{
		mainUI->lifeImage_0->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f));
		mainUI->lifeImage_1->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f));
		mainUI->lifeImage_2->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f));
	}
}