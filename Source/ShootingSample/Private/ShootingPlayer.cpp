// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingPlayer.h"

// Sets default values
AShootingPlayer::AShootingPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
}

// Called when the game starts or when spawned
void AShootingPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShootingPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShootingPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

