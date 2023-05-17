// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossBullet.generated.h"

UCLASS()
class SHOOTINGSAMPLE_API ABossBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossBullet();

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
	class UParticleSystem* explosionFX;

	UPROPERTY(EditAnywhere)
	float moveSpeed = 900.0f;

	UPROPERTY(EditAnywhere)
	float patternDelayTime = 10.0f;

	UPROPERTY(EditAnywhere)
	TArray<float> maxPatternIndex;

	UFUNCTION()
	void OnBulletOverlapPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

private:
	float patternCurTime = 0;
	int32 patternIndex = 0;
	int32 curPatternCount = 0;
	FVector dir;
	FVector dirSin;
	FVector dirAround;

	void FireGuided(float DeltaTime);
	void FireForward(float DeltaTime);
	void FireShot(float DeltaTime);
	void FireArc(float DeltaTime);
	void FireAround(float DeltaTime);

public:
	int32 GetFirePatternIndex();
};
