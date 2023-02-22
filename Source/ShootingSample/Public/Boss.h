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
	float delayTime = 10.0f;

	UPROPERTY(EditAnywhere)
	float bulletDelayTime = 2.5f;

	UPROPERTY(EditAnywhere)
	int32 bossHP = 10;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* explosionFX;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyBullet> bossBulletFactory;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBossOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	int32 GetBossHP();
	void HitByBullet(int32 damage);

private:
	FVector dir;
	FVector startLocation;
	FVector stopLocation;

	float totalDistance;
	float currentDistance;
	float currentTime = 0;
	float bulletCurrentTime = 0;

	void BossFire();
};
