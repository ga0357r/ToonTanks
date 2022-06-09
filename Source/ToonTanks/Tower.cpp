// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TimerManager.h"


ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	//get player tank
	PlayerTankRef = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (DrawDebugHelpers)
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), FireRange, 25, FColor::Red, true, -1.f);
	}

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	//check distance from the tower to the tank

	if (IsInFireRange())
	{
		Fire();
	}
	
	
}

inline bool ATower::IsInFireRange()
{
	if (PlayerTankRef)
	{
		float DistanceToTank = FVector::Dist(PlayerTankRef->GetActorLocation(), GetActorLocation());
		return DistanceToTank <= FireRange;
	}

	return false;
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//check to see if the tank is in range
	if (IsInFireRange())
	{
		RotateTurret(PlayerTankRef->GetActorLocation());
	}
	
}