// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/VillainCharacter.h"

#include "AbilitySystemComponent.h"
#include "Weapon/Weapon.h"
#include "AbilitySystem/VillainAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "Player/VillainPlayerState.h"
#include "VillainComponents/CombatComponent.h"

AVillainCharacter::AVillainCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 320.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 0.f, 850.f);
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	
	Combat = CreateDefaultSubobject<UCombatComponent>("CombatComponent");
	Combat->SetIsReplicated(true);  // Components do not need to be registered in GetLifetimeReplicatedProps

	NetUpdateFrequency = 66.f;  // COMMON values for fast-paced games
	MinNetUpdateFrequency = 33.f;
}

void AVillainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Init ability actor info for the Server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AVillainCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void AVillainCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(AVillainCharacter, OverlappingWeapon, COND_OwnerOnly); // Condition that only the Owner of the pawn, will get this replicated to them
}

void AVillainCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (Combat)
	{
		Combat->Character = this; // Character variable is set on the CombatComponent when initialized
	}
}

int32 AVillainCharacter::GetPlayerLevel_Implementation()
{
	const AVillainPlayerState* VillainPlayerState = GetPlayerState<AVillainPlayerState>();
	check(VillainPlayerState);
	return VillainPlayerState->GetPlayerLevel();
}

void AVillainCharacter::InitAbilityActorInfo()
{
	AVillainPlayerState* VillainPlayerState = GetPlayerState<AVillainPlayerState>();
	check(VillainPlayerState)
	VillainPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(VillainPlayerState, this);
	Cast<UVillainAbilitySystemComponent>(VillainPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = VillainPlayerState->GetAbilitySystemComponent();
	AttributeSet = VillainPlayerState->GetAttributeSet();
	
	InitializeDefaultAttributes();
}

bool AVillainCharacter::IsWeaponEquipped()
{
	return EquippedWeapon == nullptr ? false : true;
}


void AVillainCharacter::SetOverlappingWeapon(AWeapon* NewWeapon)
{
	if (OverlappingWeapon)
	{
		OverlappingWeapon->ShowPickupWidget(false);
	}
	OverlappingWeapon = NewWeapon;
	if (IsLocallyControlled() && OverlappingWeapon)
	{
		OverlappingWeapon->ShowPickupWidget(true);
	}
}

void AVillainCharacter::ServerEquipButtonPressed_Implementation()
{
	if (Combat)
	{
		if (OverlappingWeapon)
		{
			Combat->EquipWeapon(OverlappingWeapon);
		}
		/*else if (Combat->ShouldSwapWeapons())
		{
			Combat->SwapWeapons();
		}*/
	}
}

void AVillainCharacter::OnRep_OverlappingWeapon(AWeapon* LastWeapon) // LastWeapon is the last value of Overlapping weapon before replication
{
	if (OverlappingWeapon)
	{
		OverlappingWeapon->ShowPickupWidget(true);
	}
	if (LastWeapon)
	{
		LastWeapon->ShowPickupWidget(false);
	}
}

bool AVillainCharacter::IsAiming()
{
	return (Combat && Combat->bAiming);
}

