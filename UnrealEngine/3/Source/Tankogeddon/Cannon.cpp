// Fill out your copyright notice in the Description page of Project Settings.

#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include "Cannon.h"
#include <Engine/Engine.h>
#include <TimerManager.h>

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComp;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(SceneComp);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);
}

void ACannon::Fire()
{
	if (!IsReadyToFire()) {
		return;
	}

	if (Cannontype == ECannonType::FireProjectile) {
		GEngine->AddOnScreenDebugMessage(-1, FireRate, FColor::Purple, 
			FString::Printf(TEXT("Fire Projectile %d"), --CountAmmunition));
		TimeRate();
	}
	else if(Cannontype == ECannonType::FireTrace){
		GEngine->AddOnScreenDebugMessage(-1, FireRate, FColor::Red, 
			FString::Printf(TEXT("Fire trace %d"), --CountAmmunition));
		TimeRate();
	}
	else {
		countAmmo = 4;
		bReadyToFire = false;
		GetWorld()->GetTimerManager().SetTimer(SeriesAmmoTimer, this, &ACannon::FireSeries, FireRate / 4, true);
	}

}

// альтернативный вариант стрельбы
void ACannon::FireSpecial()
{
	if (!IsReadyToFire()) {
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, FireRate / 2, FColor::Green, 
		FString::Printf(TEXT("Fire Special %d"), --CountAmmunition));

	
}

// стрельба серией снарядов
void ACannon::FireSeries()
{
	GEngine->AddOnScreenDebugMessage(-1, FireRate+2, FColor::Blue,
		FString::Printf(TEXT("Fire series")));
	
	if (--countAmmo < 1) {
		GetWorldTimerManager().ClearTimer(SeriesAmmoTimer);
		Reload();
		
		GEngine->AddOnScreenDebugMessage(-1, FireRate, FColor::Blue,
			FString::Printf(TEXT("ammo %d"), --CountAmmunition));
	}
}

bool ACannon::IsReadyToFire()
{
	return bReadyToFire && CountAmmunition > 0;
}

void ACannon::Reload()
{
	bReadyToFire = true;
}

void ACannon::Recharge()
{
	CountAmmunition = 10;
}

void ACannon::TimeRate()
{
	bReadyToFire = false;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, FireRate, false);
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();

	bReadyToFire = true;
	
}

// Called every frame
//void ACannon::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//}

