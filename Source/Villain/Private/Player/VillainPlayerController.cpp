// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VillainPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/VillainAbilitySystemComponent.h"
#include "Character/VillainCharacter.h"
#include "Input/VillainInputComponent.h"
#include "VillainComponents/CombatComponent.h"

AVillainPlayerController::AVillainPlayerController()
{
	bReplicates = true;
}

void AVillainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(VillainInputContext);
	
	//3rd Person Only
	/*FInputModeGameOnly InputModeData;
	SetInputMode(InputModeData);
	*/
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(VillainInputContext, 0);
	};
}

void AVillainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UVillainInputComponent* VillainInputComponent = CastChecked<UVillainInputComponent>(InputComponent);
	
	VillainInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVillainPlayerController::Move);
	VillainInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &AVillainPlayerController::Aim);
	VillainInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVillainPlayerController::Look);
	VillainInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AVillainPlayerController::CrouchButtonPressed); // Also set as triggered in IA_Crouch due to stuttering in game. Fixed it
	VillainInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AVillainPlayerController::JumpButtonPressed);
	VillainInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &AVillainPlayerController::EquipButtonPressed);
	VillainInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AVillainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	LookAtMouseWhileAiming();

}

void AVillainPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	/*AVillainCharacter* VillainCharacter = Cast<AVillainCharacter>(InPawn);
	if (VillainCharacter)
	{
		SetHUDHealth(BlasterCharacter->GetHealth(), BlasterCharacter->GetMaxHealth());
	}*/
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(VillainInputContext, 0);
	}
}

UVillainAbilitySystemComponent* AVillainPlayerController::GetASC()
{
	if (VillainAbilitySystemComponent == nullptr)
	{
		VillainAbilitySystemComponent = Cast<UVillainAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return VillainAbilitySystemComponent;
}

void AVillainPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	// TODO: See AURA for additional functionality for Pressed, Released, and Held
	
	if (GetASC()) GetASC()->AbilityInputTagPressed(InputTag);
}

void AVillainPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
}

void AVillainPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
}

void AVillainPlayerController::Move(const FInputActionValue& InputActionValue)
{
	//TODO: If unable to move due to certain GameplayTag, return early
	
	//FOR 3rd Person
	/*const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}*/

	// Retrieve the movement input value
	FVector2D MoveInput = InputActionValue.Get<FVector2D>();

	// Set a fixed movement direction
	FVector FixedDirection = FVector::ForwardVector * MoveInput.Y + FVector::RightVector * MoveInput.X;

	// Normalize the vector to ensure consistent movement speed
	FixedDirection.Normalize();

	// Move in the fixed world direction
	if (APawn* ControlledPawn = GetPawn<APawn>())
	ControlledPawn->AddMovementInput(FixedDirection, 1.0f);
}

void AVillainPlayerController::Aim(const FInputActionValue& InputActionValue)
{
	bIsAiming = InputActionValue.Get<bool>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		VillainCharacter == nullptr ? VillainCharacter = Cast<AVillainCharacter>(ControlledPawn) : VillainCharacter;
		if (VillainCharacter && VillainCharacter->IsWeaponEquipped())
		{
			//if (VillainCharacter->bDisableGameplay) return;
			if (UCombatComponent* CombatComponent = VillainCharacter->GetCombatComponent())
			{
				CombatComponent->SetAiming(bIsAiming);
			}
		}
	}
}

void AVillainPlayerController::Look(const FInputActionValue& InputActionValue)
{
	// For 3rd Person
	/*
	FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// add yaw and pitch input to controller
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
	}*/
}


void AVillainPlayerController::EquipButtonPressed()
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		VillainCharacter == nullptr ? VillainCharacter = Cast<AVillainCharacter>(ControlledPawn) : VillainCharacter;
		if (VillainCharacter)
		{
			//if (VillainCharacter->bDisableGameplay) return;
			if (VillainCharacter->GetCombatComponent()->CombatState == ECombatState::ECS_Unoccupied)
			{
				VillainCharacter->ServerEquipButtonPressed();
				bShowMouseCursor = false;
			}
			/*if (VillainCharacter->GetCombatComponent()->ShouldSwapWeapons() && !HasAuthority() && BlasterCharacter->GetCombatComponent()->CombatState == ECombatState::ECS_Unoccupied && BlasterCharacter->OverlappingWeapon == nullptr)
			{
				VillainCharacter->PlaySwapMontage();
				VillainCharacter->GetCombatComponent()->CombatState = ECombatState::ECS_SwappingWeapons;
				VillainCharacter->bFinishedSwapping = false;
			}
			*/
		}
	}
}

void AVillainPlayerController::CrouchButtonPressed()
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		VillainCharacter == nullptr ? VillainCharacter = Cast<AVillainCharacter>(ControlledPawn) : VillainCharacter;
		if (VillainCharacter)
		{
			//if (VillainCharacter->bDisableGameplay) return;
		}
		if (ACharacter* ControlledCharacter = Cast<ACharacter>(ControlledPawn))
		{
			if (ControlledCharacter->bIsCrouched)
			{
				ControlledCharacter->UnCrouch();
			}
			else
			{
				ControlledCharacter->Crouch();
			}
		}
	}
}

void AVillainPlayerController::JumpButtonPressed()
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		VillainCharacter == nullptr ? VillainCharacter = Cast<AVillainCharacter>(ControlledPawn) : VillainCharacter;
		//if (VillainCharacter && VillainCharacter->bDisableGameplay) return;
		if (ACharacter* ControlledCharacter = Cast<ACharacter>(ControlledPawn))
		{
			ControlledCharacter->Jump();
		}
	}
}

void AVillainPlayerController::LookAtMouseWhileAiming()
{
	const ECollisionChannel TraceChannel = ECC_Visibility;
	GetHitResultUnderCursor(TraceChannel, false, CursorHit);

	if (!bIsAiming) return;
	// Get the controlled character and ensure it's valid
	if (APawn* ControlledPawn = GetPawn())
	{
		// Determine where to look at based on the trace result
		const FVector LookAtLocation = CursorHit.Location;
		const FVector DirectionToLook = (LookAtLocation - ControlledPawn->GetActorLocation()).GetSafeNormal();
		const FRotator LookRotation = FRotationMatrix::MakeFromX(DirectionToLook).Rotator();

		// Update only the Yaw to make the character face horizontally
		const FRotator NewRotation = FRotator(0.0f, LookRotation.Yaw, 0.0f);

		// Smooth rotation for a natural look
		ControlledPawn->Controller->SetControlRotation(FMath::RInterpTo(ControlledPawn->Controller->GetControlRotation(), NewRotation, GetWorld()->GetDeltaSeconds(), 960));
	}
}
