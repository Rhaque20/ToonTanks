// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if(ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }

        GameOver(false);
            
    }
    else if(ATower *DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        TargetTowers--;

        if(TargetTowers == 0)
        {
            GameOver(true);
        }
    }
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
    TArray<AActor*> TowerList;

    UGameplayStatics::GetAllActorsOfClass(this,ATower::StaticClass(),TowerList);

    return TowerList.Num();
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();


}

void AToonTanksGameMode::HandleGameStart()
{
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0));
    TargetTowers = GetTargetTowerCount();
    StartGame();

    if(ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);
        FTimerHandle PlayerEnableTimerHandle;


        //Sets up timer delegate passing in true to the enabled state function
        // in ToonTanksPlayerController
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController, 
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true
            );

            // Implements the delegate holder, and the delegate
            GetWorldTimerManager().SetTimer(
                PlayerEnableTimerHandle,
                PlayerEnableTimerDelegate,
                StartDelay,
                false
                );
    }
}