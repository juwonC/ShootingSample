// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(LogTemp, Warning, TEXT("%d"), num);
	//UE_LOG(LogTemp, Warning, TEXT("%.2f"), num2);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *name);

	int32 result = Add(num, num2);
	UE_LOG(LogTemp, Warning, TEXT("%d"), result);
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ATestActor::Add(int32 number1, int32 number2)
{
	int32 result = number1 + number2;
	
	return result;
}

