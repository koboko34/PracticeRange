// Copyright Epic Games, Inc. All Rights Reserved.

#include "PracticeRangeGameModeBase.h"
#include "ShootTarget.h"
#include "Math/UnrealMathUtility.h"


APracticeRangeGameModeBase::APracticeRangeGameModeBase()
{
    
}

void APracticeRangeGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    SessionEndDelegate = FTimerDelegate::CreateUObject(this, &ThisClass::CompleteSession);        
}

void APracticeRangeGameModeBase::StartSession()
{
    if (ShootTargetClass == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("ShootTargetClass not set in %s"), *GetActorNameOrLabel());
        return;
    }

    DestroyLastTarget();
    SetShowStats(false);
    ResetAccuracy();
    GetWorldTimerManager().ClearTimer(SessionHandle);
    GetWorldTimerManager().SetTimer(SessionHandle, SessionEndDelegate, 30, false);
    SpawnNext();

}

void APracticeRangeGameModeBase::CompleteSession()
{
    DestroyLastTarget();
    SetShowStats(true);
}


void APracticeRangeGameModeBase::EndSession()
{
    DestroyLastTarget();
    ResetAccuracy();
    GetWorldTimerManager().ClearTimer(SessionHandle);
}

bool APracticeRangeGameModeBase::GetShowStats() const
{
    return bShowStats;
}

void APracticeRangeGameModeBase::SetShowStats(bool bNewShowStats)
{
    bShowStats = bNewShowStats;
}

void APracticeRangeGameModeBase::SpawnNext()
{
    FVector Location = FVector(SpawnX, FMath::RandRange(MinY, MaxY), FMath::RandRange(MinZ, MaxZ));
    FRotator Rotation = FRotator::ZeroRotator;
    FTransform SpawnTransform = FTransform(Rotation, Location, FVector(1));
    
    LastSpawnedTarget = GetWorld()->SpawnActor<AShootTarget>(ShootTargetClass, SpawnTransform);
}

void APracticeRangeGameModeBase::DestroyLastTarget()
{
    if (LastSpawnedTarget)
    {
        LastSpawnedTarget->Destroy();
    }
}
void APracticeRangeGameModeBase::AddHit()
{
    if (GetWorldTimerManager().IsTimerActive(SessionHandle))
    {
        Hits++;
    }
}

void APracticeRangeGameModeBase::AddShot()
{
    if (GetWorldTimerManager().IsTimerActive(SessionHandle))
    {
        Shots++;
    }
}

void APracticeRangeGameModeBase::Miss()
{
    if (GetWorldTimerManager().IsTimerActive(SessionHandle))
    {
        DestroyLastTarget();
        SpawnNext();
    }
}

float APracticeRangeGameModeBase::GetAccuracy()
{
    if (Shots == 0)
    {
        return Accuracy = 1.f * 100;
    }
    
    return Accuracy = (float)Hits / (float)Shots * 100;
}

bool APracticeRangeGameModeBase::IsSessionTimerActive() const
{
    return GetWorldTimerManager().IsTimerActive(SessionHandle);
}

float APracticeRangeGameModeBase::GetSessionTimeLeft() const
{
    return GetWorldTimerManager().GetTimerRemaining(SessionHandle);
}

void APracticeRangeGameModeBase::ResetAccuracy()
{
    Shots = 0;
    Hits = 0;
}
