// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

	public:
		bool bAlive = true;

		ATank();
		virtual void Tick(float DeltaTime) override;
		void HandleDestruction();
		APlayerController* GetTankPlayerController() const {return TankPlayerController;}
	
	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
		// void Fire();
	private:
		UPROPERTY(VisibleAnywhere, Category = "Camera Component")
		class USpringArmComponent *SpringArm;

		UPROPERTY(VisibleAnywhere, Category = "Camera Component")
		class UCameraComponent *Camera;

		UPROPERTY(EditAnywhere, Category = "Movement")
		float Speed = 300.f;

		UPROPERTY(EditAnywhere, Category = "Movement")
		float TurnRate = 45.f;

		APlayerController *TankPlayerController;

		void Move(float Value);
		void Turn(float Value);
		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
		
};
