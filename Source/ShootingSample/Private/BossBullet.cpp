// Fill out your copyright notice in the Description page of Project Settings.


#include "BossBullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ShootingPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "ShootingSampleGameModeBase.h"
#include "EngineUtils.h"
#include "Kismet/KismetMathLibrary.h"

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
	
	for (TActorIterator<AShootingPlayer> player(GetWorld()); player; ++player)
	{
		if (player->GetName().Contains(TEXT("BP_ShootingPlayer")))
		{
			dir = player->GetActorLocation() - GetActorLocation();
			dir.Normalize();

			FVector upVector = this->GetActorUpVector();
			FRotator newRotation = UKismetMathLibrary::MakeRotFromXZ(dir, upVector);
			SetActorRotation(newRotation, ETeleportType::None);
		}
	}

	// dirSin = FVector(0, FMath::Sin(PI * curPatternCount / maxPatternIndex[patternIndex] * 2), -1);

	// dirSin = FVector(0, FMath::Sin(PI * -3 * 2), FMath::Cos(PI * 3 * 2));

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABossBullet::OnBulletOverlapPlayer);
}

// Called every frame
void ABossBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FireGuided(DeltaTime);
}

void ABossBullet::OnBulletOverlapPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AShootingPlayer* player = Cast<AShootingPlayer>(OtherActor);

	AGameModeBase* currentMode = GetWorld()->GetAuthGameMode();
	AShootingSampleGameModeBase* currentGameModeBase = Cast<AShootingSampleGameModeBase>(currentMode);

	if (player != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFX, GetActorLocation(), GetActorRotation());

		currentGameModeBase->PlayerOnHit(1);

		if (currentGameModeBase->playerLife <= 0)
		{
			UGameplayStatics::SetGamePaused(GetWorld(), true);
			currentGameModeBase->GameOver();
		}
		else
		{
			// 시작지점 Location [X = 0, Y = 0, Z = -400]에 충돌이 있어서 액터를 스폰할 수 없다는 오류 발생
			// 사망 후 일정시간 동안 무적이 되게 하여 해결

			player->RespawnPlayer();

			player->PlayerInvuln();
		}
	}

	Destroy();
}

void ABossBullet::FireGuided(float DeltaTime)
{
	FVector newLocation = GetActorLocation() + dir * moveSpeed * DeltaTime;

	SetActorLocation(newLocation);
}

void ABossBullet::FireForward(float DeltaTime)
{
	FVector newLocation = GetActorLocation() + GetActorForwardVector() * moveSpeed * DeltaTime;

	SetActorLocation(newLocation);

	++curPatternCount;

	UE_LOG(LogTemp, Log, TEXT("FireForward"));
}

void ABossBullet::FireShot(float DeltaTime)
{
	//FVector newLocation = GetActorLocation() + GetActorForwardVector() * moveSpeed * DeltaTime;
	//FVector* ranVec = new FVector(FMath::RandRange(-5.0f, 5.0f), FMath::RandRange(0.0f, 10.0f), 0);

	//newLocation += *ranVec;

	//SetActorLocation(newLocation);

	++curPatternCount;

	UE_LOG(LogTemp, Log, TEXT("FireShot"));
}

void ABossBullet::FireArc(float DeltaTime)
{		
	FVector newLocation = GetActorLocation() + dirSin * moveSpeed * DeltaTime;
	
	float y = FMath::Sin(PI / curPatternCount * 2);
	//FMath::Sin(PI * 360 / curPatternCount * 10);

	SetActorLocation(newLocation);

	UE_LOG(LogTemp, Log, TEXT("FireArc"));

	++curPatternCount;
}

void ABossBullet::FireAround(float DeltaTime)
{
	FVector newLocation = GetActorLocation() + GetActorForwardVector() * moveSpeed * DeltaTime;
	//
	//FVector dirVec = FVector(FMath::Sin(PI * DeltaTime * 2), FMath::Sin(PI * DeltaTime * 2), -1);
	//newLocation += dirVec;
	//
	SetActorLocation(newLocation);

	++curPatternCount;

	UE_LOG(LogTemp, Log, TEXT("FireAround"));

}

int32 ABossBullet::GetFirePatternIndex()
{
	return patternIndex;
}
