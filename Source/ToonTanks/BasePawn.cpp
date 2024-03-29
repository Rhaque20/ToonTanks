// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Projectile.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BASE MESH"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TURRET MESH"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void ABasePawn::HandleDestruction()
{
	if(DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
	if(DeathSound)
		UGameplayStatics::PlaySoundAtLocation(this,DeathSound,GetActorLocation());
	if (DeathParticles)
		UGameplayStatics::SpawnEmitterAtLocation(this,DeathParticles,GetActorLocation(),GetActorRotation());
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f,ToTarget.Rotation().Yaw,0.f);

	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(),
	LookAtRotation,
	UGameplayStatics::GetWorldDeltaSeconds(this),
	25.f));
}

void ABasePawn::Fire()
{
		FVector ProjPos = ProjectileSpawnPoint->GetComponentLocation();
		FRotator ProjRot = ProjectileSpawnPoint->GetComponentRotation();

		AProjectile *Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,ProjPos,ProjRot);
		Projectile->SetOwner(this);
}

