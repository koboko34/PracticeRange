// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Target.h"
#include "ResetTarget.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICERANGE_API AResetTarget : public ATarget
{
	GENERATED_BODY()

	AResetTarget();

protected:
	virtual void BeginPlay();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	class APracticeRangeGameModeBase* GameMode;
};
