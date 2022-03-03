// Fill out your copyright notice in the Description page of Project Settings.


#include "SprayCannon.h"

// Sets default values
ASprayCannon::ASprayCannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent=CreateDefaultSubobject<USceneComponent>("RootComponent");

	Cash=CreateDefaultSubobject<UStaticMeshComponent>("Cash");
	Cash->SetupAttachment(RootComponent);

	ProjectileSpawnPoints=CreateDefaultSubobject<UArrowComponent>("ProjectileSpawnPoints");
	Cash->SetupAttachment(RootComponent);

}

void ASprayCannon::SprayShoot(int& AmmoSpray)
{
	if (!bReadyToSprayShoot)
		return;
	switch (Types)
	{
	case ESprayCannonType::FireProjectile:
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, FString(TEXT("SPRAY SHOOT")));
		AmmoSpray--;
		GEngine->AddOnScreenDebugMessage(3, 666, FColor::Cyan, FString::Printf(TEXT("AMMOSPRAY - %i"),AmmoSpray));
		break;
	case ESprayCannonType::FireSpray:
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Orange, FString(TEXT("LALALA")));
		break;
	}
	
	bReadyToSprayShoot = false;
	GetWorld()->GetTimerManager().SetTimer(TimerPencil,FTimerDelegate::CreateUObject(this, &ASprayCannon::ResetSprayShootState), FireRateSpray, false);
	
}

// Called when the game starts or when spawned
void ASprayCannon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASprayCannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(1234, -1, FColor::Purple, FString::Printf(TEXT("RECHARDETWO %f"),GetWorld()->GetTimerManager().GetTimerElapsed(TimerPencil)));
	
}

void ASprayCannon::ResetSprayShootState()
{
	bReadyToSprayShoot = true;
}
