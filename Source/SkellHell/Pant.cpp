// Fill out your copyright notice in the Description page of Project Settings.


#include "Pant.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
APant::APant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");

	FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
	StaticMeshComponent->AttachToComponent(RootComponent, TransformRules);
}

// Called when the game starts or when spawned
void APant::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	return;
	Time += DeltaTime / Duration;
	
	FVector ALocation = GoingUp ? FVector::ZeroVector : UpAmount;
	FVector BLocation = GoingUp ? UpAmount : FVector::ZeroVector;
	float Alpha = UKismetMathLibrary::Ease(0.f, 1.f, Time, EEasingFunc::EaseInOut);
	Alpha = FMath::Clamp(Alpha, 0.f, 1.f);

	FVector LerpedLocation = FMath::Lerp(ALocation, BLocation, Alpha);

	StaticMeshComponent->SetWorldLocation(GetActorLocation() + LerpedLocation);
	
	if (Time >= 1)
	{
		GoingUp = !GoingUp;
		Time = 0;
	}
}

