// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pant.generated.h"

UCLASS()
class SKELLHELL_API APant : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APant();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	float Duration = 1;

	UPROPERTY(EditAnywhere)
	FVector UpAmount = FVector::UpVector * 50;

	bool GoingUp = true;

	float Time;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
