// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class SHOOTINGSAMPLE_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* enemyFirePosition;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> bulletFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyBullet> enemyBulletFactory;

	UPROPERTY(EditAnywhere)
	int32 traceRate = 50;

	UPROPERTY(EditAnywhere)
	float moveSpeed = 800;

	UPROPERTY(EditAnywhere)
	float bulletDelayTime = 1.0f;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* explosionFX;

	UFUNCTION()
	void OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
							bool bFromSweep, const FHitResult& SweepResult);

private:
	FVector dir;
	float bulletCurrentTime = 0;

	void EnemyFire();
};
