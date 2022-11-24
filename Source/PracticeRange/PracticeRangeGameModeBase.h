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

protected:

private:

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ATarget> TargetClass;

};
