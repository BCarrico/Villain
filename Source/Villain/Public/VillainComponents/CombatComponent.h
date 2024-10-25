// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UI/HUD/VillainHUD.h"
#include "VillainTypes/CombatState.h"
#include "CombatComponent.generated.h"


class AWeapon;
class AVillainPlayerController;
class AVillainCharacter;
class AVillainHUD;
enum class ECombatState : uint8;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VILLAIN_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UCombatComponent();
	friend class AVillainCharacter;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void EquipWeapon(AWeapon* WeaponToEquip);
	void EquipPrimaryWeapon(AWeapon* WeaponToEquip);
	void SetAiming(bool bIsAiming);
	UPROPERTY(ReplicatedUsing=OnRep_CombatState)
	ECombatState CombatState = ECombatState::ECS_Unoccupied;

	UPROPERTY(BlueprintReadOnly)
	FHitResult HitResult;
protected:

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void AttachActorToRightHand(AActor* ActorToAttach);
	void AttachActorToLeftHand(AActor* ActorToAttach);
	UFUNCTION()
	void OnRep_EquippedWeapon();

	UFUNCTION(Server, Reliable)
	void ServerSetAiming(bool bIsAiming);

	void TraceUnderCrosshairs(FHitResult& TraceHitResult);
	void SetHUDCrosshairs(float DeltaTime);
private:
	UPROPERTY()
	AVillainCharacter* Character;
	
	UPROPERTY()
	AVillainPlayerController* Controller;
	
	UPROPERTY()
	AVillainHUD* HUD;

	UPROPERTY(ReplicatedUsing = OnRep_EquippedWeapon)
	AWeapon* EquippedWeapon;
	// HUD and Crosshairs
	
	float CrosshairVelocityFactor;
	float CrosshairInAirFactor;
	float CrosshairAimFactor;
	float CrosshairShootingFactor;
	FHUDPackage HUDPackage;
	
	FVector HitTarget;
	
	UPROPERTY(ReplicatedUsing = OnRep_Aiming)
	bool bAiming = false;

	bool bAimButtonPressed = false;
	
	UPROPERTY(EditAnywhere)
	float BaseWalkSpeed = 600.f;
	
	UPROPERTY(EditAnywhere)
	float AimWalkSpeed = 450.f;
	
	UFUNCTION()
	void OnRep_Aiming();
	
	UFUNCTION()
	void OnRep_CombatState();
	

		
};
