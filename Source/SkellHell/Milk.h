// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Components/SplineComponent.h"
#include "Milk.generated.h"

/**
 * 
 */
UCLASS()
class SKELLHELL_API AMilk : public AWeaponBase
{
	GENERATED_BODY()

	AMilk();

public:
	virtual void Hit() override;

	void Throw(FVector Target, float Distance);
protected:
	UFUNCTION()
	void UpdateThrow();
	UFUNCTION()
	void ThrowComplete();
	
	UPROPERTY(EditAnywhere)
	float BaseDuration = .8f;

	float TimeStarted;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	USplineComponent* SplineComponent;
};
