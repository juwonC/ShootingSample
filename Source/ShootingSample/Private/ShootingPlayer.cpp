// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingPlayer.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Bullet.h"
#include "Kismet/GameplayStatics.h"
#include "ShootingSampleGameModeBase.h"

// Sets default values
AShootingPlayer::AShootingPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Box Component
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));

	// Set Box Component as the Root Component
	SetRootComponent(boxComp);

	// Create Static Mesh Component
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static Mesh"));

	// Set Static Mesh Component as a box component's child component
	meshComp->SetupAttachment(boxComp);

	// Adjust Box Component size
	FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
	boxComp->SetBoxExtent(boxSize);

	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Fire Position"));
	firePosition->SetupAttachment(boxComp);

	// Generate Overlap Event
	boxComp->SetGenerateOverlapEvents(true);

	// Set Query And Physics
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// Set Object Type on channel1
	boxComp->SetCollisionObjectType(ECC_GameTraceChannel1);

	// Set All Channels to ignore
	boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	// Check Collision with Enemys
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	boxComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
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

	// Create Direction Vector
	FVector dir = FVector(0, h, v);

	// Normalize Vector
	dir.Normalize();

	// Get Location
	FVector newLocation = GetActorLocation() + dir * moveSpeed * DeltaTime;

	// Update new location
	SetActorLocation(newLocation, true);
}

// Called to bind functionality to input
void AShootingPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Horizontal", this, &AShootingPlayer::MoveHorizontal);
	PlayerInputComponent->BindAxis("Vertical", this, &AShootingPlayer::MoveVertical);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShootingPlayer::Fire);

	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AShootingPlayer::Pause);
}

void AShootingPlayer::PlayerRevive(bool isPlayerDie)
{
	if (isPlayerDie == true)
	{
		GetWorldTimerManager().SetTimer(timerHandle, FTimerDelegate::CreateLambda([&]()
			{
				this->SetActorEnableCollision(false);
			}), ignoreDamageTime, false);
		
		
	}

	this->SetActorEnableCollision(true);
}

void AShootingPlayer::MoveHorizontal(float value)
{
	// Assign input Axis values to h
	h = value;
}

void AShootingPlayer::MoveVertical(float value)
{
	// Assign input Axis values to v
	v = value;
}

void AShootingPlayer::Fire()
{
	ABullet* bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition->GetComponentLocation(),
		firePosition->GetComponentRotation());

	UGameplayStatics::PlaySound2D(GetWorld(), fireSound);
}

void AShootingPlayer::Pause()
{
	AShootingSampleGameModeBase* currentGameMode = Cast<AShootingSampleGameModeBase>(GetWorld()->GetAuthGameMode());

	if (currentGameMode != nullptr)
	{
		currentGameMode->PauseGame();
	}
}
