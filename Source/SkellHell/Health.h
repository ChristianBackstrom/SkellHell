// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonesCharacter.h"
#include "Components/ActorComponent.h"
#include "Health.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKELLHELL_API UHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealth();

	UFUNCTION(BlueprintCallable)
	void PlayerHit();

	UPROPERTY(BlueprintReadOnly)
	bool IsHurt = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY()
	ABonesCharacter* BonesCharacter;

	UPROPERTY(EditAnywhere)
	float MaxTimeBetweenHit = 3.f;

	UPROPERTY(EditAnywhere)
	float InvincibilityTime = 1.f;

	UPROPERTY(VisibleAnywhere)
	float TimeSinceHit = 0;

	UFUNCTION(BlueprintCallable)
	bool GetIsInvincible();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
