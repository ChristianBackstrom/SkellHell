// Fill out your copyright notice in the Description page of Project Settings.


#include "PantCollector.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UPantCollector::UPantCollector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPantCollector::BeginPlay()
{
	Super::BeginPlay();

	Parent = GetOwner();
}


// Called every frame
void UPantCollector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> PantToRemove;

	for (auto Pant : SuckedPant)
	{
		FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(Pant->GetActorLocation(), (Parent->GetActorLocation() + FVector::UpVector * 50));

		Pant->AddActorWorldOffset(Direction*SuckForce*DeltaTime);

		if (FVector::Distance(Parent->GetActorLocation()  + FVector::UpVector * 50, Pant->GetActorLocation()) <= 100.f)
		{
			PantCollectedAmount++;
			PantToRemove.Add(Pant);
		}
	}

	for (auto Pant : PantToRemove)
	{
		SuckedPant.Remove(Pant);
		Pant->Destroy();
	}
	
}

void UPantCollector::PantCollected(AActor* Actor)
{
	SuckedPant.AddUnique(Actor);
}

