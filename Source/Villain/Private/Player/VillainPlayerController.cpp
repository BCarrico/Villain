// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VillainPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "VillainGameplayTags.h"
#include "AbilitySystem/VillainAbilitySystemComponent.h"
#include "Character/VillainCharacter.h"
#include "Interaction/EnemyInterface.h"
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
	
	FInputModeGameOnly InputModeData;
	SetInputMode(InputModeData);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(VillainInputContext, 0);
	};

	// Show mouse cursor, and use default arrow-shaped cursor
	//bShowMouseCursor = true;
	//DefaultMouseCursor = EMouseCursor::Default;
	
	//FInputModeGameAndUI InputModeData;
	//InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//InputModeData.SetHideCursorDuringCapture(false);
	//SetInputMode(InputModeData);
}

void AVillainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UVillainInputComponent* VillainInputComponent = CastChecked<UVillainInputComponent>(InputComponent);
	
	VillainInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVillainPlayerController::Move);
	VillainInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVillainPlayerController::Aim);
	VillainInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AVillainPlayerController::CrouchButtonPressed); // Also set as triggered in IA_Crouch due to stuttering in game. Fixed it
	VillainInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVillainPlayerController::Look);
	VillainInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AVillainPlayerController::JumpButtonPressed);
	VillainInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &AVillainPlayerController::EquipButtonPressed);
	VillainInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AVillainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
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

void AVillainPlayerController::Look(const FInputActionValue& InputActionValue)
{
	FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// add yaw and pitch input to controller
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AVillainPlayerController::JumpButtonPressed()
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (ACharacter* ControlledCharacter = Cast<ACharacter>(ControlledPawn))
		{
			ControlledCharacter->Jump();
		}
	}
}

void AVillainPlayerController::CrouchButtonPressed()
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
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

void AVillainPlayerController::EquipButtonPressed()
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (AVillainCharacter* VillainCharacter = Cast<AVillainCharacter>(ControlledPawn))
		{
			//if (VillainCharacter->bDisableGameplay) return;
			if (VillainCharacter->GetCombatComponent()->CombatState == ECombatState::ECS_Unoccupied) VillainCharacter->ServerEquipButtonPressed();
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
