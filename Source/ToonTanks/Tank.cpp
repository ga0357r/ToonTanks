// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

#define OUT

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetupComponents();
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerControllerRef)
	{
		FHitResult HitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, OUT HitResult);
		RotateTurret(HitResult.ImpactPoint);

		if (DrawDebugHelpers)
		{
			DrawDebugSphere(GetWorld(), OUT HitResult.ImpactPoint, 25.f, 12, FColor::Red, false, -1.f);
		}
	}
}

void ATank::SetupComponents()
{
	//Spring Arm Component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Component");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATank::MoveForward);
	PlayerInputComponent->BindAxis("Turn", this, &ATank::Turn);
}

void ATank::MoveForward(float Value)
{
	FVector DeltaLocation(0.f);
	DeltaLocation.X = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * MoveSpeed;
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Tank Turning"));
	FRotator DeltaRotation = FRotator(0.f);
	DeltaRotation.Yaw = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * RotationSpeed;
	AddActorLocalRotation(DeltaRotation, true);
}