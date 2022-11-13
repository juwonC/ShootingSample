// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

UCLASS()
class SHOOTINGSAMPLE_API ATestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	int32 num = 10;

	UPROPERTY(VisibleAnywhere)
	float num2 = 3.14f;

	//FString name = "Juwon";
	FString name = TEXT("주원");

	bool isReady = true;
	bool isFinished = false;
};
