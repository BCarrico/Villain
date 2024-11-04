// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "VillainPlayerController.generated.h"

class UDamageTextComponent;
class AVillainCharacter;
class UVillainInputConfig;
class UVillainAbilitySystemComponent;
class IEnemyInterface;
struct FInputActionValue;
/**
 * 
 */
class UInputMappingContext;
class UInputAction;

UCLASS()
class VILLAIN_API AVillainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AVillainPlayerController();
	FORCEINLINE FHitResult GetCursorHitResult(){return CursorHit;}
	
	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool bCriticalHit);
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	bool bIsAiming;
	
	UPROPERTY()
	AVillainCharacter* VillainCharacter;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> VillainInputContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> EquipAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> AimAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LMBAimAction;
	
	UPROPERTY()
	TObjectPtr<UVillainAbilitySystemComponent> VillainAbilitySystemComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UVillainInputConfig> InputConfig;
	
	FHitResult CursorHit;
	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;

	UVillainAbilitySystemComponent* GetASC();
	
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	void Move(const FInputActionValue& InputActionValue);
	void Aim(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	void EquipButtonPressed();
	void CrouchButtonPressed();
	void JumpButtonPressed();
	void LMBAimPressed(const FInputActionValue& InputActionValue);
	void LookAtMouseWhileAiming();
};
