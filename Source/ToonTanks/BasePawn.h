// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug Helpers", meta = (AllowPrivateAccess = "true"))
	bool DrawDebugHelpers = false;

	void RotateTurret(FVector LookAtTarget);

	void Fire();

private:
	// Private Serialized Fields
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasePawn Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasePawn Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasePawn Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BasePawn Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint = nullptr;

	//setup components
	void SetupComponents();
};
