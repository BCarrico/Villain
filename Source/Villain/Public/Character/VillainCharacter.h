// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "VillainTypes/CombatState.h"
#include "VillainTypes/TurningInPlace.h"
#include "VillainCharacter.generated.h"

class AVillainPlayerController;
class UCombatComponent;
class AWeapon;
class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class VILLAIN_API AVillainCharacter : public ACharacterBase
{
	GENERATED_BODY()
public:
	AVillainCharacter();
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;
	virtual void Jump() override;
	virtual void OnRep_ReplicatedMovement() override;
	FORCEINLINE void SetEquippedWeapon(AWeapon* WeaponToEquip) {EquippedWeapon = WeaponToEquip;}
	AWeapon* GetEquippedWeapon() const;
	FORCEINLINE UCombatComponent* GetCombatComponent() const {return Combat;}
	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw;}
	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch;}
	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace;}
	ECombatState GetCombatState() const;
	bool IsWeaponEquipped();
	UFUNCTION(BlueprintCallable)
	bool IsAiming();
	void SetOverlappingWeapon(AWeapon* Weapon);
	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();
	/* Combat Interface */
	virtual int32 GetPlayerLevel_Implementation() override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	FVector GetHitTarget() const;

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleWellFedMutation(FVector WellFedMeshSize);

	UFUNCTION(BlueprintCallable)
	void BeginWellFedMutation(FVector WellFedMeshSize);
	
protected:

	// Villain Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCombatComponent* Combat;

	UPROPERTY(BlueprintReadOnly)
	AWeapon* EquippedWeapon;
	
	void CalculateAO_Pitch();
	float CalculateSpeed();
	void AimOffset(float DeltaTime);
	void TurnInPlace(float DeltaTime);
	void SimProxiesTurn();

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon) // Creates a replicated variable, calls OnRep_OverlappingWeapon when changed.
	AWeapon* OverlappingWeapon;
	
	TEnumAsByte<ETurningInPlace> TurningInPlace = ETurningInPlace::ETIP_NotTurning;
	float AO_Yaw;
	float InterpAO_Yaw;
	float AO_Pitch;
	FRotator StartingAimRotation;
	bool bRotateRootBone;
	float TurnThreshold = 0.5f;
	FRotator ProxyRotationLastFrame;
	FRotator ProxyRotation;
	float ProxyYaw;
	float TimeSinceLastMovementReplication;
	
	virtual void InitAbilityActorInfo() override;
	
	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

	void RotateInPlace(float DeltaTime);

	
};
