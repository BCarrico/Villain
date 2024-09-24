// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"


class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class VILLAIN_API ACharacterBase : public ACharacter, public IAbilitySystemInterface // <-- Gives ability to GetAbilitySystemComponent()
{
	GENERATED_BODY()

public:

	ACharacterBase();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Ability System */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	
	/* Ability System - Needed For Enemy Class? */
	//TODO: Construct ASC + AS in Enemy Class
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
private:	


};
