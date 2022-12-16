// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleMenuGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.h"

void ATitleMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (titleWidget != nullptr)
	{
		titleUI = CreateWidget<UTitleWidget>(GetWorld(), titleWidget);

		if (titleUI != nullptr)
		{
			titleUI->AddToViewport();
		}
	}
}
