// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VillainTypes/CombatState.h"
#include "CombatComponent.generated.h"


class AWeapon;
class AVillainPlayerController;
class AVillainCharacter;
enum class ECombatState : uint8;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VILLAIN_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UCombatComponent();
	friend class AVillainCharacter;

	void EquipWeapon(AWeapon* WeaponToEquip);
	void EquipPrimaryWeapon(AWeapon* WeaponToEquip);
	
	UPROPERTY(ReplicatedUsing=OnRep_CombatState)
	ECombatState CombatState = ECombatState::ECS_Unoccupied;
protected:

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void AttachActorToRightHand(AActor* ActorToAttach);
	UFUNCTION()
	void OnRep_EquippedWeapon();
private:
	UPROPERTY()
	AVillainCharacter* Character;
	
	UPROPERTY()
	AVillainPlayerController* Controller;

	UPROPERTY(ReplicatedUsing = OnRep_EquippedWeapon)
	AWeapon* EquippedWeapon;

	UFUNCTION()
	void OnRep_CombatState();

	

		
};
