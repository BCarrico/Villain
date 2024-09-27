// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VillainPlayerController.generated.h"

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

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere, Category= Input)
	TObjectPtr<UInputMappingContext> VillainInputContext;

	UPROPERTY(EditAnywhere, Category= Input)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category= Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY()
	TObjectPtr<UVillainAbilitySystemComponent> VillainAbilitySystemComponent;

	FHitResult CursorHit;
	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;

	UVillainAbilitySystemComponent* GetASC();
	void Move(const FInputActionValue& InputActionValue);
	void LookAtMouseLocation() const;
	void CursorTrace();
	FVector_NetQuantize CursorHitLocation;
};
