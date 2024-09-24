// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/VillainCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/VillainAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/VillainPlayerState.h"

AVillainCharacter::AVillainCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>("TopDownCameraComponet");
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AVillainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Init ability actor info for the Server
	InitAbilityActorInfo();
}

void AVillainCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void AVillainCharacter::InitAbilityActorInfo()
{
	AVillainPlayerState* VillainPlayerState = GetPlayerState<AVillainPlayerState>();
	check(VillainPlayerState)
	VillainPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(VillainPlayerState, this);
	Cast<UVillainAbilitySystemComponent>(VillainPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = VillainPlayerState->GetAbilitySystemComponent();
	AttributeSet = VillainPlayerState->GetAttributeSet();
}