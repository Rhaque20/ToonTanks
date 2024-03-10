// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class USoundBase;
UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	
	void HandleDestruction();

protected:
	UPROPERTY(EditAnywhere,Category ="Particles")
	class UParticleSystem *DeathParticles;

	void RotateTurret(FVector LookAtTarget);
	void Fire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent *CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent *ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	float _moveSpeed = 100.0;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase *DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat");
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
