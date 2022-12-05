// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class PRACTICERANGE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* MappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* TogglePauseAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* ToggleShowStatsAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void ToggleShowStats(const FInputActionValue& Value);

	void StartShoot(const FInputActionValue& Value);
	void EndShoot();

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION(BlueprintPure)
	float GetMouseSens() const { return MouseSens; }
	UFUNCTION(BlueprintCallable)
	void SetMouseSens(float NewValue);
	UFUNCTION(BlueprintPure)
	bool GetInvertMouse() const { return bInvertMouse; }
	UFUNCTION(BlueprintCallable)
	void SetInvertMouse(bool NewValue);
	UFUNCTION(BlueprintCallable)
	void SaveGame();
	UFUNCTION(BlueprintCallable)
	void TogglePause();


private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;
	UPROPERTY()
	UUserWidget* HUD;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PauseMenuClass;
	UPROPERTY()
	UUserWidget* PauseUI;
	bool bInMenu = false;

	class APlayerController* PlayerController;

	class ABaseGun* Gun;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABaseGun> GunClass;

	class APracticeRangeGameModeBase* GameMode;

	const FString MouseSlot = "MouseSlot";
	UPROPERTY(EditAnywhere)
	float MouseSens;
	UPROPERTY(EditAnywhere)
	bool bInvertMouse;

private:
	void LoadGame();

};
