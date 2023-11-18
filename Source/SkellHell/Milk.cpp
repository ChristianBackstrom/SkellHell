// Fill out your copyright notice in the Description page of Project Settings.


#include "Milk.h"

AMilk::AMilk()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");

	SplineComponent = CreateDefaultSubobject<USplineComponent>("Spline");
	SplineComponent->SetAbsolute(true, false, true);
}

void AMilk::Hit()
{
	Super::Hit();

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, "BOOM");

	Destroy();
}

void AMilk::Throw(FVector Target, float Distance)
{
	SplineComponent->SetLocationAtSplinePoint(SplineComponent->GetNumberOfSplinePoints()-1, Target, ESplineCoordinateSpace::World);
	SplineComponent->SetLocationAtSplinePoint(0, GetActorLocation(), ESplineCoordinateSpace::World);
	

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &AMilk::UpdateThrow);
	TimeStarted = GetWorld()->GetTimeSeconds();

	BaseDuration *= Distance / 1000;
	
	GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.001f, true);
}

void AMilk::UpdateThrow()
{
	float timeElapsed = GetWorld()->GetTimeSeconds() - TimeStarted;

	float scaledElapsedTime = timeElapsed / BaseDuration;

	SetActorLocation(SplineComponent->GetLocationAtTime(scaledElapsedTime, ESplineCoordinateSpace::World));

	if (scaledElapsedTime >= 1)
	{
		ThrowComplete();
	}
}

void AMilk::ThrowComplete()
{
	GetWorldTimerManager().ClearAllTimersForObject(this);
	Hit();
}

