// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PantCollector.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKELLHELL_API UPantCollector : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPantCollector();

	UPROPERTY(BlueprintReadWrite)
	int PantCollectedAmount = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float SuckForce = 10;
	
	UPROPERTY()
	AActor* Parent;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> SuckedPant;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void PantCollected(AActor* Actor);
};
