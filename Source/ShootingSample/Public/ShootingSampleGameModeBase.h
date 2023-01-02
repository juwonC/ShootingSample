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
	
	void AddScore(int32 point);
	void PlayerOnHit(int32 life);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainWidget> mainWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMenuWidget> menuWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPauseWidget> pauseWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ULifeWidget> lifeWidget;

	void GameOver();
	void PauseGame();
	void SetPlayerLife(int32 life) { playerLife = life; }

protected:
	virtual void BeginPlay() override;

private:
	int32 currentScore = 0;

	class UMainWidget* mainUI;

	class UMenuWidget* menuUI;

	class UPauseWidget* pauseUI;

	class ULifeWidget* lifeUI;

	void PrintScore();
	void UpdateLifeImage();
};