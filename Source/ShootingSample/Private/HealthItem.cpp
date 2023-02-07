// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthItem.h"
#include "ShootingPlayer.h"
#include "ShootingSampleGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHealthItem::AHealthItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("HealthItem Box Component"));
	SetRootComponent(boxComp);
	
	boxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HealthItem Static Mesh"));
	meshComp->SetupAttachment(boxComp);

	boxComp->SetCollisionProfileName(TEXT("Item"));
}

// Called when the game starts or when spawned
void AHealthItem::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AHealthItem::OnItemOverlap);
}

// Called every frame
void AHealthItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, rotateSpeed * DeltaTime, 0.0f));

	FVector newLocation = GetActorLocation() + GetActorUpVector() * -1 * moveSpeed * DeltaTime;

	SetActorLocation(newLocation);
}

void AHealthItem::OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AShootingSampleGameModeBase* currentGameMode = Cast<AShootingSampleGameModeBase>(GetWorld()->GetAuthGameMode());

	if (currentGameMode->playerLife < 3)
	{
		currentGameMode->playerLife += 1;
	}

	currentGameMode->UpdateLifeImage();

	Destroy();
}