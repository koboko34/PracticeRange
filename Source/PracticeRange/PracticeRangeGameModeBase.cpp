// Copyright Epic Games, Inc. All Rights Reserved.

#include "PracticeRangeGameModeBase.h"
#include "Target.h"

APracticeRangeGameModeBase::APracticeRangeGameModeBase()
{
    
}

void APracticeRangeGameModeBase::StartSession()
{
    if (TargetClass == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("TargetClass not set in %s"), *GetActorNameOrLabel());
        return;
    }
    
    FVector Location = FVector(600, 0, 100);
    FRotator Rotation = FRotator::ZeroRotator;
    FTransform SpawnTransform = FTransform(Rotation, Location, FVector(1));
    
    GetWorld()->SpawnActor<ATarget>(TargetClass, SpawnTransform);
}
