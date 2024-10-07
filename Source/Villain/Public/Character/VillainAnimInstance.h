// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "VillainAnimInstance.generated.h"

class AWeapon;
class AVillainCharacter;
/**
 * 
 */
UCLASS()
class VILLAIN_API UVillainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(BlueprintReadOnly, Category="Character", meta = (AllowPrivateAccess="true"))
	AVillainCharacter* VillainCharacter;
	
	UPROPERTY(BlueprintReadOnly, Category="Movement", meta = (AllowPrivateAccess="true"))
	float Speed;
	
	UPROPERTY(BlueprintReadOnly, Category="Movement", meta = (AllowPrivateAccess="true"))
	bool bIsInAir;

	UPROPERTY(BlueprintReadOnly, Category="Movement", meta = (AllowPrivateAccess="true"))
	bool bIsAccelerating;

	UPROPERTY(BlueprintReadOnly, Category="Movement", meta = (AllowPrivateAccess="true"))
	bool bWeaponEquipped;

	AWeapon* EquippedWeapon;

	UPROPERTY(BlueprintReadOnly, Category="Movement", meta = (AllowPrivateAccess="true"))
	bool bIsCrouched;

	UPROPERTY(BlueprintReadOnly, Category="Movement", meta = (AllowPrivateAccess="true"))
	bool bAiming;
};
