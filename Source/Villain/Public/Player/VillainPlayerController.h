// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VillainPlayerController.generated.h"

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
private:
	UPROPERTY(EditAnywhere, Category= Input)
	TObjectPtr<UInputMappingContext> VillainInputContext;

	UPROPERTY(EditAnywhere, Category= Input)
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);
};
