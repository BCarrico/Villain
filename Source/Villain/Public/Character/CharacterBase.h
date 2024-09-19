// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CharacterBase.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UCapsuleComponent;

UCLASS()
class VILLAIN_API ACharacterBase : public APawn
{
	GENERATED_BODY()

public:
	
	ACharacterBase();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* CharacterMesh;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComponent;

};
