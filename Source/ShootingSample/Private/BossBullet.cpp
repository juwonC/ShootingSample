// Fill out your copyright notice in the Description page of Project Settings.


#include "BossBullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ShootingPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "ShootingSampleGameModeBase.h"

// Sets default values
ABossBullet::ABossBullet()
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
	boxComp->SetCollisionProfileName(TEXT("BossBullet"));
}

// Called when the game starts or when spawned
void ABossBullet::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABossBullet::OnBulletOverlapPlayer);
}

// Called every frame
void ABossBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newLocation = GetActorLocation() + GetActorForwardVector() * moveSpeed * DeltaTime;
	float deltaHeight = FMath::Sin(DeltaTime * PI * 2);
	newLocation.Y += deltaHeight * 50.0f;

	SetActorLocation(newLocation);
}

void ABossBullet::OnBulletOverlapPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AShootingPlayer* player = Cast<AShootingPlayer>(OtherActor);

	AGameModeBase* currentMode = GetWorld()->GetAuthGameMode();
	AShootingSampleGameModeBase* currentGameModeBase = Cast<AShootingSampleGameModeBase>(currentMode);

	if (player != nullptr)
	{
		OtherActor->Destroy();

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFX, GetActorLocation(), GetActorRotation());

		currentGameModeBase->PlayerOnHit(1);

		if (currentGameModeBase->playerLife <= 0)
		{
			UGameplayStatics::SetGamePaused(GetWorld(), true);
			currentGameModeBase->GameOver();
		}
		else
		{
			currentGameModeBase->RestartPlayer(GetWorld()->GetFirstPlayerController());
		}
	}

	Destroy();
}