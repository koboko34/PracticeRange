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
	void Miss();
	void ResetAccuracy();
	UFUNCTION(BlueprintPure)
	float GetAccuracy();
	UFUNCTION(BlueprintPure)
	int GetShots() { return Shots; }
	UFUNCTION(BlueprintPure)
	int GetHits() { return Hits; }

	UFUNCTION(BlueprintPure)
	bool IsSessionTimerActive() const;
	UFUNCTION(BlueprintPure)
	float GetSessionTimeLeft() const;

	void SetShowStats(bool bNewShowStats);
	UFUNCTION(BlueprintPure)
	bool GetShowStats() const;

	float Accuracy = 100.f;
	int Shots = 0;
	int Hits = 0;

protected:
	virtual void BeginPlay();

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

	FTimerHandle SessionHandle;
	FTimerDelegate SessionEndDelegate;

	bool bShowStats = false;
	
	void CompleteSession();
	
	void DestroyLastTarget();

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class USoundBase* StartPing;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class USoundBase* EndSiren;

};
