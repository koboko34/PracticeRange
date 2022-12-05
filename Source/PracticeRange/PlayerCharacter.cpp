// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "BaseGun.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PracticeRangeGameModeBase.h"
#include "MySaveGame.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 64.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	MouseSens = 1.f;
	bInvertMouse = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController != nullptr)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}

	if (HUDClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("HUDClass is not set!"));
		return;
	}
	HUD = CreateWidget(PlayerController, HUDClass);
	HUD->AddToViewport();
	
	if (PauseMenuClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("HUDClass is not set!"));
		return;
	}	
	PauseUI = CreateWidget(PlayerController, PauseMenuClass);

	if (GunClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("GunClass not set on player!"));
		return;
	}

	Gun = GetWorld()->SpawnActor<ABaseGun>(GunClass);
	if (Gun == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Gun not spawned correctly!"));
		return;
	}
	Gun->AttachToComponent(GetFirstPersonCameraComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	Gun->SetOwner(this);

	// TEMPORARY ----------------------------------------------------------------
	Gun->GetMesh()->SetVisibility(false);
	
	if (Controller == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controller is null"));
		return;
	}

	GameMode = Cast<APracticeRangeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode is null on PlayerCharacter!"));
		return;
	}

	if (UGameplayStatics::DoesSaveGameExist(MouseSlot, 0))
	{
		LoadGame();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No game save found. Creating new game save..."));
		SaveGame();
	}
}

void APlayerCharacter::LoadGame()
{
	if (UGameplayStatics::DoesSaveGameExist(MouseSlot, 0))
	{
		UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(MouseSlot, 0));
		SetMouseSens(SaveGameInstance->MouseSens);
		SetInvertMouse(SaveGameInstance->bInvertMouse);
		UE_LOG(LogTemp, Warning, TEXT("Loading complete."));
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("Save game does not exist!"));
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		
		EnhancedInputComponent->BindAction(TogglePauseAction, ETriggerEvent::Started, this, &APlayerCharacter::TogglePause);
		EnhancedInputComponent->BindAction(ToggleShowStatsAction, ETriggerEvent::Started, this, &APlayerCharacter::ToggleShowStats);

		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &APlayerCharacter::StartShoot);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &APlayerCharacter::EndShoot);

	}

}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MoveVector.Y);
		AddMovementInput(GetActorRightVector(), MoveVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	if (bInMenu)
	{
		return;
	}
	
	FVector2D LookVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (bInvertMouse)
		{
			AddControllerYawInput(LookVector.X * 0.1 * MouseSens);
			AddControllerPitchInput(-LookVector.Y * 0.1* MouseSens);
			return;
		}
		AddControllerYawInput(-LookVector.X * 0.1 * MouseSens);
		AddControllerPitchInput(LookVector.Y * 0.1 * MouseSens);
	}
}

void APlayerCharacter::SetInvertMouse(bool NewValue)
{
	bInvertMouse = NewValue;
}

void APlayerCharacter::SetMouseSens(float NewValue)
{
	MouseSens = NewValue;
}

void APlayerCharacter::SaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist(MouseSlot, 0))
	{
		UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(MouseSlot, 0));
		SaveGameInstance->MouseSens = GetMouseSens();
		SaveGameInstance->bInvertMouse = GetInvertMouse();
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, MouseSlot, 0);
	}
	else
	{
		UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		SaveGameInstance->MouseSens = GetMouseSens();
		SaveGameInstance->bInvertMouse = GetInvertMouse();
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, MouseSlot, 0);	
	}
	UE_LOG(LogTemp, Warning, TEXT("Save complete."));
}

void APlayerCharacter::TogglePause()
{
	if (bInMenu)
	{
		// Close pause menu and save settings
		PauseUI->RemoveFromParent();
		PlayerController->SetInputMode(FInputModeGameOnly::FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
		bInMenu = !bInMenu;
		SaveGame();
		PlayerController->SetPause(false);
		return;
	}

	// Open pause menu
	PlayerController->SetPause(true);
	PauseUI->AddToViewport(1);
	PlayerController->SetInputMode(FInputModeGameAndUI::FInputModeGameAndUI());
	PlayerController->bShowMouseCursor = true;
	bInMenu = !bInMenu;
	
}

void APlayerCharacter::ToggleShowStats(const FInputActionValue& Value)
{
	GameMode->SetShowStats(!GameMode->GetShowStats());
}

void APlayerCharacter::StartShoot(const FInputActionValue& Value)
{
	if (Gun	== nullptr)
	{
		return;
	}
	
	bool val = Value.Get<bool>();

	if (val == true)
	{
		// UE_LOG(LogTemp, Warning, TEXT("StartShoot() called!"));
		Gun->ShootSemi(GetFirstPersonCameraComponent()->GetComponentLocation(), GetFirstPersonCameraComponent()->GetForwardVector());
		
	}
}


void APlayerCharacter::EndShoot()
{
	if (Gun == nullptr)
	{
		return;
	}

	Gun->bTriggerReady = true;
}

