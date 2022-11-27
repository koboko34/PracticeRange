// Copyright Epic Games, Inc. All Rights Reserved.

#include "PracticeRangeGameModeBase.h"
#include "ShootTarget.h"
#include "Math/UnrealMathUtility.h"


APracticeRangeGameModeBase::APracticeRangeGameModeBase()
{
    
}

void APracticeRangeGameModeBase::StartSession()
{
    if (ShootTargetClass == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("ShootTargetClass not set in %s"), *GetActorNameOrLabel());
        return;
    }

    if (LastSpawnedTarget)
    {
        LastSpawnedTarget->Destroy();
    }

    ResetAccuracy();
    SpawnNext();

}

void APracticeRangeGameModeBase::EndSession()
{
    if (LastSpawnedTarget)
    {
        LastSpawnedTarget->Destroy();
    }
}



void APracticeRangeGameModeBase::SpawnNext()
{
    FVector Location = FVector(SpawnX, FMath::RandRange(MinY, MaxY), FMath::RandRange(MinZ, MaxZ));
    FRotator Rotation = FRotator::ZeroRotator;
    FTransform SpawnTransform = FTransform(Rotation, Location, FVector(1));
    
    LastSpawnedTarget = GetWorld()->SpawnActor<AShootTarget>(ShootTargetClass, SpawnTransform);
}

void APracticeRangeGameModeBase::AddHit()
{
    Hits++;
}

void APracticeRangeGameModeBase::AddShot()
{
    Shots++;
}

float APracticeRangeGameModeBase::GetAccuracy() const
{
    if (Shots == 0)
    {
        return 1 * 100;
    }
    return Hits / Shots * 100;
}

void APracticeRangeGameModeBase::ResetAccuracy()
{
    Shots = 0;
    Hits = 0;
}
