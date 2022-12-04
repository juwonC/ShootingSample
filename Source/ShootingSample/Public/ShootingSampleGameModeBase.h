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
	void AddScore(int32 point);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainWidget> mainWidget;

protected:
	virtual void BeginPlay() override;

private:
	int32 currentScore = 0;

	class UMainWidget* mainUI;
};
