// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Milk.h"
#include "BonesCharacter.generated.h"

UCLASS()
class SKELLHELL_API ABonesCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABonesCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> HitMarkerBP;

	UPROPERTY()
	AActor* HitMarker;

	UPROPERTY(EditAnywhere, Category="Inputs")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, Category="Inputs")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category="Inputs")
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, Category="Inputs")
	UInputAction* DashAction;
	
	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, Category="Weapon")
	TSubclassOf<AMilk> MilkBlueprint;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
	FVector FirePoint = FVector::ForwardVector * 50 + FVector::UpVector * 50;

	UPROPERTY(EditAnywhere, Category="Weapon")
	float WeaponCooldown = .2;

	float CooldownTime;

	FVector2d MovementInput;

	UFUNCTION(BlueprintImplementableEvent)
	void Dash(FVector Target);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PawnClientRestart() override;

	
private:
	void Move(const FInputActionValue& ActionValue);
	void Fire(const FInputActionValue& ActionValue);
	void DashEvent(const FInputActionValue& ActionValue);
};
