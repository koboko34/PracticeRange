// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PracticeRangeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICERANGE_API APracticeRangeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	APracticeRangeGameModeBase();

	void StartSession();
	void EndSession();
	void SpawnNext();
	void AddHit();
	void AddShot();
	void ResetAccuracy();
	UFUNCTION(BlueprintPure)
	float GetAccuracy() const;

protected:

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AShootTarget> ShootTargetClass;

	AShootTarget* LastSpawnedTarget;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float SpawnX = 990.f;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
    float MinY = -1800.f, MaxY = 1800.f;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
    float MinZ = 50.f, MaxZ = 750.f;

	float Accuracy = 100.f;
	int Shots;
	int Hits;

};
