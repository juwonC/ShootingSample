// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "ShootingPlayer.h"
#include "ShootingSampleGameModeBase.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(boxComp);

	// Set Enemy Collision Preset
	boxComp->SetCollisionProfileName(TEXT("Enemy"));
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
	int32 drawResult = FMath::RandRange(1, 100);

	if (drawResult <= traceRate)
	{
		for (TActorIterator<AShootingPlayer> player(GetWorld()); player; ++player)
		{
			if (player->GetName().Contains(TEXT("BP_ShootingPlayer")))
			{
				dir = player->GetActorLocation() - GetActorLocation();
				dir.Normalize();

				// Rotate Enemies
				FVector upVector = player->GetActorUpVector();
				FRotator newRotation = UKismetMathLibrary::MakeRotFromXZ(dir, upVector);
				SetActorRotation(newRotation, ETeleportType::None);
			}
		}
	}
	else
	{
		dir = GetActorForwardVector();
	}

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnEnemyOverlap);
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newLocation = GetActorLocation() + dir * moveSpeed * DeltaTime;
	SetActorLocation(newLocation);
}

void AEnemyActor::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
								 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
								 bool bFromSweep, const FHitResult& SweepResult)
{
	AShootingPlayer* player = Cast<AShootingPlayer>(OtherActor);
	AShootingSampleGameModeBase* currentGameMode = Cast<AShootingSampleGameModeBase>(GetWorld()->GetAuthGameMode());

	FTimerHandle timerHandle;

	if (currentGameMode != nullptr)
	{
		if (player != nullptr)
		{
			OtherActor->Destroy();

			currentGameMode->PlayerOnHit(1);

			if (currentGameMode->playerLife <= 0)
			{
				UGameplayStatics::SetGamePaused(GetWorld(), true);
				currentGameMode->GameOver();
			}
			else
			{
				currentGameMode->RestartPlayer(GetWorld()->GetFirstPlayerController());
			}
			
			Destroy();
		}
	}
}

