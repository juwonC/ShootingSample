// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"

void UMenuWidget::Restart()
{
	UGameplayStatics::OpenLevel(GetWorld(), "ShootingMap");
}

void UMenuWidget::Quit()
{
	UWorld* currentWorld = GetWorld();

	UKismetSystemLibrary::QuitGame(currentWorld, currentWorld->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	buttonRestart->OnClicked.AddDynamic(this, &UMenuWidget::Restart);

	buttonQuit->OnClicked.AddDynamic(this, &UMenuWidget::Quit);
}
