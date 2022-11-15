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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 num = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 num2 = 30;

	//FString name = "Juwon";
	UPROPERTY(EditInstanceOnly)
	FString name = TEXT("주원");

	bool isReady = true;
	bool isFinished = false;

	UFUNCTION(BlueprintPure)
	int32 Add(int32 number1, int32 number2);
};
