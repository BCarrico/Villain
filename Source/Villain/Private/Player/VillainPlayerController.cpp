// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VillainPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Input/VillainInputComponent.h"

AVillainPlayerController::AVillainPlayerController()
{
	bReplicates = true;
}

void AVillainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(VillainInputContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(VillainInputContext, 0);
	};

	// Show mouse cursor, and use default arrow-shaped cursor
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AVillainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UVillainInputComponent* VillainInputComponent = CastChecked<UVillainInputComponent>(InputComponent);
	
	VillainInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVillainPlayerController::Move);
	//TODO: BindAbilityActions from InputComponent.h
}

void AVillainPlayerController::Move(const FInputActionValue& InputActionValue)
{
	//TODO: If unable to move due to certain GameplayTag, return early
	
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
