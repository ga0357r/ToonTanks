// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"


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
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerTankRef)
	{
		//Find distance to tank
		float DistanceToTank = FVector::Dist(PlayerTankRef->GetActorLocation(), GetActorLocation());

		//check to see if the tank is in range
		if (DistanceToTank <= FireRange)
		{
			RotateTurret(PlayerTankRef->GetActorLocation());
		}
	}
}