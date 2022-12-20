// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"

void UTitleWidget::Start()
{
	UGameplayStatics::OpenLevel(GetWorld(), "ShootingMap");
}

void UTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	FOnInputAction callBack = {};
	callBack.BindUFunction(this, "Start");

	ListenForInputAction(TEXT("AnyKey"), IE_Pressed, true, callBack);
}
