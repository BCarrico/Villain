// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/VillainCharacter.h"

#include "AbilitySystemComponent.h"
#include "VillainGameplayTags.h"
#include "Weapon/Weapon.h"
#include "AbilitySystem/VillainAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Player/VillainPlayerState.h"
#include "VillainComponents/CombatComponent.h"

AVillainCharacter::AVillainCharacter()
{
	// For 3rd Person
	/*CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 320.f;
	CameraBoom->bUsePawnControlRotation = true;
	*/
	
	//bUseControllerRotationYaw = true;
	
	/*GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 0.f, 850.f);
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	*/
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	
	Combat = CreateDefaultSubobject<UCombatComponent>("CombatComponent");
	Combat->SetIsReplicated(true);  // Components do not need to be registered in GetLifetimeReplicatedProps

	NetUpdateFrequency = 100.f;  // COMMON values for fast-paced games
	MinNetUpdateFrequency = 33.f;
}

void AVillainCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//RotateInPlace(DeltaSeconds);
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

void AVillainCharacter::Jump()
{
	Super::Jump();
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Super::Jump();
	}
}

/*void AVillainCharacter::OnRep_ReplicatedMovement()
{
	Super::OnRep_ReplicatedMovement();
	SimProxiesTurn();
	TimeSinceLastMovementReplication = 0.f;
}*/

AWeapon* AVillainCharacter::GetEquippedWeapon() const
{
	return Combat->EquippedWeapon;
}

int32 AVillainCharacter::GetPlayerLevel_Implementation()
{
	const AVillainPlayerState* VillainPlayerState = GetPlayerState<AVillainPlayerState>();
	check(VillainPlayerState);
	return VillainPlayerState->GetPlayerLevel();
}

FVector AVillainCharacter::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	const FVillainGameplayTags& GameplayTags = FVillainGameplayTags::Get();
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_Weapon) && IsValid(Combat->EquippedWeapon))
	{
		return Combat->EquippedWeapon->GetWeaponMesh()->GetSocketLocation(WeaponTipSocketName);
	}
	return FVector();
}

FVector AVillainCharacter::GetHitTarget() const
{
	if (Combat == nullptr) return FVector();
	return Combat->HitTarget;
}

void AVillainCharacter::BeginWellFedMutation(FVector WellFedMeshSize)
{
	MulticastHandleWellFedMutation(WellFedMeshSize);
}

void AVillainCharacter::MulticastHandleWellFedMutation_Implementation(FVector WellFedMeshSize)
{
	
	GetMesh()->SetWorldScale3D(WellFedMeshSize);
}

/*void AVillainCharacter::CalculateAO_Pitch()
{
	AO_Pitch = GetBaseAimRotation().Pitch;
	if (AO_Pitch > 90.f && !IsLocallyControlled())
	{
		// Map pitch from [270, 360] to [-90, 0]
		const FVector2D InRange(270.f, 360.f);
		const FVector2D OutRange(-90.f, 0.f);
		AO_Pitch = FMath::GetMappedRangeValueClamped(InRange, OutRange, AO_Pitch);
	}
}*/

float AVillainCharacter::CalculateSpeed() 
{
	FVector Velocity = GetVelocity();
	Velocity.Z = 0.f;
	return Velocity.Size();
}

void AVillainCharacter::AimOffset(float DeltaTime)
{
	if (Combat && Combat->EquippedWeapon == nullptr) return;

	const float Speed = CalculateSpeed();
	const bool bIsInAir = GetCharacterMovement()->IsFalling();
	
	if (Speed == 0.f && !bIsInAir) // Standing still and not jumping
	{
		//bRotateRootBone = true;
		const FRotator CurrentAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		const FRotator DeltaAimRotation = UKismetMathLibrary::NormalizedDeltaRotator(CurrentAimRotation, StartingAimRotation);
		AO_Yaw = DeltaAimRotation.Yaw;
		if (TurningInPlace == ETurningInPlace::ETIP_NotTurning)
		{
			InterpAO_Yaw = AO_Yaw;
		}
		//bUseControllerRotationYaw = true;
		//TurnInPlace(DeltaTime);
	}
	if (Speed > 0.f || bIsInAir) // Running or jumping
	{
		//bRotateRootBone = false;
		StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		AO_Yaw = 0.f;
		//bUseControllerRotationYaw = true;
		TurningInPlace = ETurningInPlace::ETIP_NotTurning;
	}

	//CalculateAO_Pitch();
}

/*void AVillainCharacter::TurnInPlace(float DeltaTime)
{
	if (AO_Yaw > 90.f)
	{
		TurningInPlace = ETurningInPlace::ETIP_Right;
	}
	else if (AO_Yaw < -90.f)
	{
		TurningInPlace = ETurningInPlace::ETIP_Left;
	}
	if (TurningInPlace != ETurningInPlace::ETIP_NotTurning)
	{
		InterpAO_Yaw = FMath::FInterpTo(InterpAO_Yaw, 0.f, DeltaTime, 4.f);
		AO_Yaw = InterpAO_Yaw;
		if (FMath::Abs(AO_Yaw) < 15.f)
		{
			TurningInPlace = ETurningInPlace::ETIP_NotTurning;
			StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		}
	}
}*/

/*void AVillainCharacter::SimProxiesTurn()
{
	if (Combat == nullptr || Combat->EquippedWeapon == nullptr) return;
	bRotateRootBone = false;
	
	float Speed = CalculateSpeed();
	if (Speed > 0.f)
	{
		TurningInPlace = ETIP_NotTurning;
		return;
	}

	ProxyRotationLastFrame = ProxyRotation;
	ProxyRotation = GetActorRotation();
	ProxyYaw = UKismetMathLibrary::NormalizedDeltaRotator(ProxyRotation, ProxyRotationLastFrame).Yaw;
	
	if (FMath::Abs(ProxyYaw) > TurnThreshold)
	{
		if (ProxyYaw > TurnThreshold)
		{
			TurningInPlace = ETurningInPlace::ETIP_Right;
		}
		else if (ProxyYaw < TurnThreshold)
		{
			TurningInPlace = ETurningInPlace::ETIP_Left;
		}
		else
		{
			TurningInPlace = ETIP_NotTurning;
		}
		return;
	}
	TurningInPlace = ETIP_NotTurning;
}*/

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

ECombatState AVillainCharacter::GetCombatState() const
{
	if (Combat == nullptr) return ECombatState::ECS_MAX;
	return Combat->CombatState;
}

bool AVillainCharacter::IsWeaponEquipped()
{
	return (Combat && Combat->EquippedWeapon);
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

/*void AVillainCharacter::RotateInPlace(float DeltaTime)
{
	if (Combat && Combat->EquippedWeapon)
	{
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
	if (bDisableGameplay)
	{
		bUseControllerRotationYaw = false;
		TurningInPlace = ETurningInPlace::ETIP_NotTurning;
		return;
	}
	if (GetLocalRole() > ROLE_SimulatedProxy && IsLocallyControlled())
	{
		AimOffset(DeltaTime);
	}
	else
	{
		TimeSinceLastMovementReplication += DeltaTime;
		if (TimeSinceLastMovementReplication > 0.25f)
		{
			OnRep_ReplicatedMovement();
		}
		CalculateAO_Pitch();
	}
}*/

bool AVillainCharacter::IsAiming()
{
	return (Combat && Combat->bAiming);
}

