// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boss.generated.h"

UCLASS()
class SHOOTINGSAMPLE_API ABoss : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoss();

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* bossFirePosition;

	UPROPERTY(EditAnywhere)
	float moveSpeed = 200;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyBullet> bossBulletFactory;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector dir;
	FVector startLocation;
	FVector stopLocation;

	float totalDistance;
	float currentDistance;
	
};
