// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICERANGE_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

	UMySaveGame();


public:
	UPROPERTY(EditAnywhere)
	float MouseSens = 2.f;
	UPROPERTY(EditAnywhere)
	bool bInvertMouse = false;

	// float GetMouseSens() { return MouseSens; }
	// bool GetInvertMouse() { return bInvertMouse; }

	// void SetMouseSens(float NewValue);
	// void SetInvertMouse(bool NewValue);
	
};
