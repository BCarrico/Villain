// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "VillainCharacter.generated.h"

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
	void SetOverlappingWeapon(AWeapon* Weapon);
	/* Combat Interface */
	virtual int32 GetPlayerLevel_Implementation() override;
protected:

	
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
