// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGun.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "PlayerCharacter.h"

// Sets default values
ABaseGun::ABaseGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Root);

	Barrel = CreateDefaultSubobject<USceneComponent>("Barrel");
	Barrel->SetupAttachment(Mesh);

	CurrentMag = MaxMag;
	FireInterval = 1 / FireRate;

}

// Called when the game starts or when spawned
void ABaseGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseGun::ShootSemi(const FVector& Start, const FVector& CameraForwardVector)
{
	if (!bTriggerReady || !bShootReady)
	{
		return;
	}
	
	APlayerCharacter* MyOwner = Cast<APlayerCharacter>(GetOwner());

	if (MyOwner == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Gun has no owner!"));
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Gun has owner, yay!"));

	// put shoot logic here
	// timer for bShootReady with FireInterval
	FVector End = Start + (CameraForwardVector * Range);

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5);

	bTriggerReady = false;
}

