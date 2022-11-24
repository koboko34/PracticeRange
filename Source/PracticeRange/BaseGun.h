// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGun.generated.h"

UCLASS()
class PRACTICERANGE_API ABaseGun : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	class USceneComponent* Barrel;
	
public:	
	// Sets default values for this actor's properties
	ABaseGun();

	UPROPERTY(EditAnywhere, Category = "Combat")
	int MaxMag = 10;
	UPROPERTY(VisibleInstanceOnly, Category = "Combat")
	int CurrentMag;
	UPROPERTY(EditAnywhere, Category = "Combat")
	int FireRate = 500;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float Range = 20000;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float ReloadTime = 1.0;
	
	int FireInterval;

	bool bShootReady = true;
	bool bTriggerReady = true;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	void ShootSemi(const FVector& Start, const FVector& CameraForwardVector);

	UStaticMeshComponent* GetMesh() const { return Mesh; }

};
