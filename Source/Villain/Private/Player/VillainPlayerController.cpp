// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VillainPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "VillainGameplayTags.h"
#include "AbilitySystem/VillainAbilitySystemComponent.h"
#include "Interaction/EnemyInterface.h"
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
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AVillainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UVillainInputComponent* VillainInputComponent = CastChecked<UVillainInputComponent>(InputComponent);
	
	VillainInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVillainPlayerController::Move);
	VillainInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVillainPlayerController::Aim);
	//TODO: BindAbilityActions from InputComponent.h
}

void AVillainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

UVillainAbilitySystemComponent* AVillainPlayerController::GetASC()
{
	if (VillainAbilitySystemComponent == nullptr)
	{
		VillainAbilitySystemComponent = Cast<UVillainAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return VillainAbilitySystemComponent;
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

void AVillainPlayerController::Aim(const FInputActionValue& InputActionValue)
{
	// TODO: Use InputActionValue bool for CombatComponent?
	
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		const FVector PawnLocation = ControlledPawn->GetActorLocation();

		const FVector LookDirection = (CursorHitLocation - PawnLocation).GetSafeNormal();
		const FRotator NewRotation = FRotationMatrix::MakeFromX(LookDirection).Rotator();

		// IF wanting smoother input or change to 3rd Person, think of using AddControllerYawInput as SetActorRotation is immediate. 
		ControlledPawn->SetActorRotation(FRotator(NewRotation.Pitch, NewRotation.Yaw, 0.0f));
	}
}

void AVillainPlayerController::CursorTrace()
{
	if (GetASC() && GetASC()->HasMatchingGameplayTag(FVillainGameplayTags::Get().Player_Block_CursorTrace))
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->UnHighlightActor();
		LastActor = nullptr;
		ThisActor = nullptr;
		return;
	}

	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	if (LastActor != ThisActor)
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->HighlightActor();
	}
	
	// Store hit location for player rotation
	CursorHitLocation = CursorHit.Location;
}
