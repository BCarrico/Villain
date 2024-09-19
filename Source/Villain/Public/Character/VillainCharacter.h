// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "VillainCharacter.generated.h"

class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class VILLAIN_API AVillainCharacter : public ACharacterBase
{
	GENERATED_BODY()
public:
	AVillainCharacter();
private:
	
	UPROPERTY(VisibleAnywhere, Category="Camera")
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category="Camera")
	UCameraComponent* TopDownCamera;

	UPROPERTY(EditAnywhere)
	UCharacterMovementComponent* CharacterMovementComponent;
};
