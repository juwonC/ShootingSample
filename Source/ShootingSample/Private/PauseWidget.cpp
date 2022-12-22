// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UPauseWidget::Resume()
{

}

void UPauseWidget::Quit()
{
	UWorld* currentWorld = GetWorld();

	UKismetSystemLibrary::QuitGame(currentWorld, currentWorld->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	buttonQuit->OnClicked.AddDynamic(this, &UPauseWidget::Quit);
}