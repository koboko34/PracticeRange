// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"

#include "BaseGun.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
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

	// put shoot logic here
	// timer for bShootReady with FireInterval
	FVector End = Start + (CameraForwardVector * Range);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel1, Params);

	if (Hit.IsValidBlockingHit())
	{
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 16, 8, FColor::Blue, false, 5);
		UE_LOG(LogTemp, Warning, TEXT("Actor hit: %s"), *Hit.GetActor()->GetActorNameOrLabel());
		UGameplayStatics::ApplyDamage(Hit.GetActor(), 1, MyOwner->GetController(), this, UDamageType::StaticClass());
	}
	
	bTriggerReady = false;
}

