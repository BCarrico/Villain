// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/VillainAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/VillainCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapon/Weapon.h"
#include "VillainTypes/CombatState.h"

void UVillainAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	VillainCharacter = Cast<AVillainCharacter>(TryGetPawnOwner());
}

void UVillainAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (VillainCharacter == nullptr) // if not initialized yet, just do it now.
	{
		VillainCharacter = Cast<AVillainCharacter>(TryGetPawnOwner());
	}
	if (VillainCharacter == nullptr) return; // If unable to initialize, return.

	FVector Velocity = VillainCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = VillainCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = VillainCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0 ? true : false;
	bWeaponEquipped = VillainCharacter->IsWeaponEquipped();
	EquippedWeapon = VillainCharacter->GetEquippedWeapon();
	bIsCrouched = VillainCharacter->bIsCrouched;
	bAiming = VillainCharacter->IsAiming();
	TurningInPlace = VillainCharacter->GetTurningInPlace();
	//bRotateRootBone = VillainCharacter->ShouldRotateRootBone();
	//bEliminated = VillainCharacter->IsEliminated();
	
	// Offset Yaw for Strafing
	FRotator AimRotation = VillainCharacter->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(VillainCharacter->GetVelocity());
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaSeconds, 6.f);
	YawOffset = DeltaRotation.Yaw;
	
	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = VillainCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	const float Target = Delta.Yaw / DeltaSeconds;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaSeconds, 6.f);
	Lean = FMath::Clamp(Interp, -90.f, 90.f);

	AO_Yaw = VillainCharacter->GetAO_Yaw();
	AO_Pitch = VillainCharacter->GetAO_Pitch();

	if (bWeaponEquipped && EquippedWeapon && EquippedWeapon->GetWeaponMesh() && VillainCharacter->GetMesh())
	{
		LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket"), RTS_World);
		FVector OutPosition;
		FRotator OutRotation;
		VillainCharacter->GetMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);
		LeftHandTransform.SetLocation(OutPosition);
		LeftHandTransform.SetRotation(FQuat(OutRotation));

		if (VillainCharacter->IsLocallyControlled())
		{
			bLocallyControlled = true;
			const FTransform RightHandTransform = VillainCharacter->GetMesh()->GetSocketTransform(FName("hand_r"), RTS_World);
			const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(RightHandTransform.GetLocation(), RightHandTransform.GetLocation() + (RightHandTransform.GetLocation() - VillainCharacter->GetHitTarget()));
			RightHandRotation = FMath::RInterpTo(RightHandRotation, LookAtRotation, DeltaSeconds, 30.f);
		}
	}

	
	bUseFABRIK = VillainCharacter->GetCombatState() == ECombatState::ECS_Unoccupied;
	/*if (VillainCharacter->IsLocallyControlled() && VillainCharacter->GetCombatState() != ECombatState::ECS_ThrowingGrenade && VillainCharacter->GetCombatState() != ECombatState::ECS_SwappingWeapons  && VillainCharacter->bFinishedSwapping)
	{
		bUseFABRIK = !VillainCharacter->IsLocallyReloading();
	}*/
	
	//bUseAimOffsets = VillainCharacter->GetCombatState() == ECombatState::ECS_Unoccupied && !VillainCharacter->GetDisableGameplay();
	//bTransformRightHand = VillainCharacter->GetCombatState() == ECombatState::ECS_Unoccupied && !VillainCharacter->GetDisableGameplay();
	

}
