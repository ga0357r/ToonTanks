// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

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
	PlayerInputComponent->BindAxis("RotateTurret", this, &ATank::RotateTurret);
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

void ATank::RotateTurret(float value)
{
	UE_LOG(LogTemp, Warning, TEXT("Tank Turret Rotating"));
}