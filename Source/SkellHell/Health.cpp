// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UHealth::PlayerHit()
{
	if (TimeSinceHit < MaxTimeBetweenHit)
	{
		if (IsValid(BonesCharacter) && !GetIsInvincible())
			BonesCharacter->PlayerDied();
		return;
	}
	
	IsHurt = true;
	TimeSinceHit = 0;
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	TimeSinceHit = MaxTimeBetweenHit * 2;

	BonesCharacter = Cast<ABonesCharacter>(GetOwner());
}


bool UHealth::GetIsInvincible()
{
	return TimeSinceHit < InvincibilityTime;
}

// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceHit += DeltaTime;

	if (TimeSinceHit >= MaxTimeBetweenHit)
	{
		IsHurt = false;
	}
}

