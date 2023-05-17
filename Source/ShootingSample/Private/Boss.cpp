// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "BossBullet.h"
#include "ShootingPlayer.h"
#include "ShootingSampleGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "EngineUtils.h"

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

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABoss::OnBossOverlap);

	// bossIgnoreTime 만큼의 시간이 흐른뒤 충돌 판정
	this->SetActorEnableCollision(false);

	GetWorldTimerManager().SetTimer(bossTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			this->SetActorEnableCollision(true);
		}), bossIgnoreTime, false);
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (currentTime > delayTime)
	{	
		if (currentDistance < totalDistance)
		{
			FVector newLocation = GetActorLocation();

			newLocation += dir * moveSpeed * DeltaTime;

			SetActorLocation(newLocation);

			currentDistance = (newLocation - startLocation).Size();
		}

		if (bulletCurrentTime > bulletDelayTime)
		{
			bulletCurrentTime = 0;

			BossFire(DeltaTime);
		}
		else
		{
			bulletCurrentTime += DeltaTime;
		}
	}
	else
	{
		currentTime += DeltaTime;
	}
}

void ABoss::OnBossOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AShootingPlayer* player = Cast<AShootingPlayer>(OtherActor);
	AShootingSampleGameModeBase* currentGameModeBase = Cast<AShootingSampleGameModeBase>(GetWorld()->GetAuthGameMode());

	if (currentGameModeBase != nullptr)
	{
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
				player->RespawnPlayer();

				player->PlayerInvuln();
			}
		}
	}
}

void ABoss::BossFire(float DeltaTime)
{
	ABossBullet* bossBullet = GetWorld()->SpawnActor<ABossBullet>(bossBulletFactory, bossFirePosition->GetComponentLocation(),
		bossFirePosition->GetComponentRotation());
}

int32 ABoss::GetBossHP()
{
	return bossHP;
}

void ABoss::HitByBullet(int32 damage)
{
	bossHP -= damage;
}

void ABoss::IgnoreDamage()
{
	this->SetActorEnableCollision(false);
	
	GetWorldTimerManager().SetTimer(bossTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		this->SetActorEnableCollision(true);
	}), bossIgnoreTime, false);
}