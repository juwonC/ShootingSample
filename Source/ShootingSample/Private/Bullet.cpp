// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyActor.h"
#include "ShootingPlayer.h"
#include "HealthItem.h"
#include "Kismet/GameplayStatics.h"
#include "ShootingSampleGameModeBase.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	boxComp->SetWorldScale3D(FVector(0.75f, 0.25f, 1.0f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(boxComp);

	// Set Bullet Collision Preset
	boxComp->SetCollisionProfileName(TEXT("Bullet"));
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletOverlapEnemy);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get Forward Location
	FVector newLocation = GetActorLocation() + GetActorForwardVector() * moveSpeed * DeltaTime;

	SetActorLocation(newLocation);
}

void ABullet::OnBulletOverlapEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
							  bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
	AShootingPlayer* player = Cast<AShootingPlayer>(OtherActor);

	AGameModeBase* currentMode = GetWorld()->GetAuthGameMode();
	AShootingSampleGameModeBase* currentGameModeBase = Cast<AShootingSampleGameModeBase>(currentMode);

	if (enemy != nullptr)
	{
		OtherActor->Destroy();

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFX, GetActorLocation(), GetActorRotation());

		if (currentGameModeBase != nullptr)
		{
			currentGameModeBase->AddScore(1);
		}


		if (random == 1)
		{
			AHealthItem* healthItem = GetWorld()->SpawnActor<AHealthItem>(health, GetActorLocation(), FRotator::ZeroRotator);
		}
	}
	

	Destroy();
}