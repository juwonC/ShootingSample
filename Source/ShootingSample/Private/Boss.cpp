// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
ABoss::ABoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(boxComp);

	bossFirePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Fire Position"));
	bossFirePosition->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();

	startLocation = GetActorLocation();
	stopLocation = GetActorLocation() + FVector(0, 0, -500);

	dir = stopLocation - startLocation;

	totalDistance = dir.Size();

	dir = dir.GetSafeNormal();
	currentDistance = 0.0f;
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (currentDistance < totalDistance)
	{
		FVector newLocation = GetActorLocation();

		newLocation += dir * moveSpeed * DeltaTime;

		SetActorLocation(newLocation);

		currentDistance = (newLocation - startLocation).Size();
	}
}