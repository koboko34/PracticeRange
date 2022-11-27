// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Target.h"
#include "ShootTarget.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICERANGE_API AShootTarget : public ATarget
{
	GENERATED_BODY()

	AShootTarget();

protected:

	// virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
};
