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

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 64.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}

	if (HUDClass)
	{
		APlayerController* MyController = Cast<APlayerController>(Controller);
		HUD = CreateWidget(MyController, HUDClass);
		HUD->AddToViewport();
	}

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
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
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
	FVector2D LookVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(-LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void APlayerCharacter::TogglePause(const FInputActionValue& Value)
{
	bool val = Value.Get<bool>();
	if (val == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("TooglePause() called"));
	}
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

