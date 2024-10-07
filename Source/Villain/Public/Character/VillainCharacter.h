// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "VillainCharacter.generated.h"

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
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;
	FORCEINLINE void SetEquippedWeapon(AWeapon* WeaponToEquip) {EquippedWeapon = WeaponToEquip;}
	FORCEINLINE AWeapon* GetEquippedWeapon() const {return EquippedWeapon;}
	FORCEINLINE UCombatComponent* GetCombatComponent() const {return Combat;};
	bool IsWeaponEquipped();
	bool IsAiming();
	void SetOverlappingWeapon(AWeapon* Weapon);
	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();
	/* Combat Interface */
	virtual int32 GetPlayerLevel_Implementation() override;
protected:

	// Villain Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCombatComponent* Combat;

	UPROPERTY(BlueprintReadOnly)
	AWeapon* EquippedWeapon;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon) // Creates a replicated variable, calls OnRep_OverlappingWeapon when changed.
	AWeapon* OverlappingWeapon;
	
	virtual void InitAbilityActorInfo() override;
	
	UFUNCTION()
	void OnRep_OverlappingWeapon(AWeapon* LastWeapon);

	

};
