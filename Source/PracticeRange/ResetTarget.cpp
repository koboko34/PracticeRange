// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetTarget.h"
#include "Kismet/GameplayStatics.h"
#include "PracticeRangeGameModeBase.h"


AResetTarget::AResetTarget()
{
    
}

void AResetTarget::BeginPlay()
{
    Super::BeginPlay();

    GameMode = Cast<APracticeRangeGameModeBase>(UGameplayStatics::GetGameMode(this));
}

float AResetTarget::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    float Damages = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    GameMode->EndSession();

    return Damages;
}

