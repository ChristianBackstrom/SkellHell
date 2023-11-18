// Fill out your copyright notice in the Description page of Project Settings.


#include "BonesCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABonesCharacter::ABonesCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoReceiveInput = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ABonesCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->bShowMouseCursor = true;
	if (HitMarkerBP)
	{
		HitMarker = GetWorld()->SpawnActor<AActor>(HitMarkerBP);
		const float scale = MilkBlueprint.GetDefaultObject()->AreaSize*2.f / 100.f;
		HitMarker->SetActorScale3D(FVector(scale));
	}
}

// Called every frame
void ABonesCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CooldownTime += DeltaTime;
	
	FVector mouseLocation, mouseDirection;
	PlayerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);

	FVector intersectLocation = FMath::LinePlaneIntersection(mouseLocation, mouseLocation + mouseDirection, FVector::ZeroVector, FVector::UpVector);

	if (HitMarker)
		HitMarker->SetActorLocation(intersectLocation);
	//
	// FVector playerLocation = GetActorLocation();
	//
	// intersectLocation.Z = playerLocation.Z;
	//
	// SetActorRotation(UKismetMathLibrary::FindLookAtRotation(playerLocation, intersectLocation));
}

// Called to bind functionality to input
void ABonesCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Make sure that we are using a UEnhancedInputComponent; if not, the project is not configured correctly.
	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// There are ways to bind a UInputAction* to a handler function and multiple types of ETriggerEvent that may be of interest.

		// This calls the handler function on the tick when MoveAction triggers, such as when pressing an action button.
		if (IsValid(MoveAction))
		{
			PlayerEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABonesCharacter::Move);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Move Action is not valid"));	
		}

		if (IsValid(FireAction))
		{
			PlayerEnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ABonesCharacter::Fire);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Move Action is not valid"));	
		}
		
		if (IsValid(DashAction))
		{
			PlayerEnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &ABonesCharacter::DashEvent);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Move Action is not valid"));	
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not cast playerInputComponent to UEnhancedInputComponent"));	
	}
}

void ABonesCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	// Make sure that we have a valid PlayerController.
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
			Subsystem->ClearAllMappings();
		
			// Add each mapping context, along with their priority values. Higher values outprioritize lower values.
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Could not cast Local player to UEnhancedInputLocalPlayerSubsystem"));	
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not cast Controller to APlayerController"));	
	}
}

void ABonesCharacter::Move(const FInputActionValue& ActionValue)
{
	FVector2d input = ActionValue.Get<FVector2d>();
	MovementInput = input;

	FVector right = FVector::RightVector * input.X;
	FVector forward = FVector::ForwardVector * input.Y;

	AddMovementInput(forward + right);
}

void ABonesCharacter::Fire(const FInputActionValue& ActionValue)
{
	if (CooldownTime <= WeaponCooldown) return;
	
	CooldownTime = 0;
	FVector mouseLocation, mouseDirection;
	PlayerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);

	FVector intersectLocation = FMath::LinePlaneIntersection(mouseLocation, mouseLocation + mouseDirection, FVector::ZeroVector, FVector::UpVector);
	
	AMilk* Milk = GetWorld()->SpawnActor<AMilk>(MilkBlueprint, GetActorLocation() +FirePoint.RotateAngleAxis(GetActorRotation().Euler().Z, FVector::UpVector), FRotator::ZeroRotator);

	Milk->Throw(intersectLocation, FVector::Distance(intersectLocation, Milk->GetActorLocation()));
}

void ABonesCharacter::DashEvent(const FInputActionValue& ActionValue)
{
	FVector target = FVector(MovementInput.Y, MovementInput.X, 0.f) * 100;
	target.Z = 0;

	Dash(target + GetActorLocation());
}

