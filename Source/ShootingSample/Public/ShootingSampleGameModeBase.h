// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingSampleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGSAMPLE_API AShootingSampleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	int32 playerLife = 3;
	bool isPlayerDie = false;
	
	void AddScore(int32 point);
	void PlayerOnHit(int32 life);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainWidget> mainWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMenuWidget> menuWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPauseWidget> pauseWidget;

	void GameOver();
	void PauseGame();
	void PrintScore();
	void UpdateLifeImage();

	UFUNCTION()
	void RespawnPlayer();

protected:
	virtual void BeginPlay() override;
	
private:
	FTimerHandle respawnTimeHandle;
	int32 currentScore = 0;

	float respawnDelayTime = 2.0f;

	class UMainWidget* mainUI;

	class UMenuWidget* menuUI;

	class UPauseWidget* pauseUI;
};