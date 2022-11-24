// Fill out your copyright notice in the Description page of Project Settings.


#include "StartTarget.h"
#include "Kismet/GameplayStatics.h"
#include "PracticeRangeGameModeBase.h"

AStartTarget::AStartTarget()
{
    
}

float AStartTarget::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    APracticeRangeGameModeBase* MyGameMode = Cast<APracticeRangeGameModeBase>(UGameplayStatics::GetGameMode(this));
    if (MyGameMode == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s failed to cast to PracticeRangeGameMode"), *GetActorNameOrLabel());
        return DamageToApply;
    }
    
    MyGameMode->StartSession();
    return DamageToApply;
}
