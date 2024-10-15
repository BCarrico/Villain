// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "CharacterBase.generated.h"


class UGameplayEffect;
class UGameplayAbility;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class VILLAIN_API ACharacterBase : public ACharacter, public ICombatInterface, public IAbilitySystemInterface // <-- Gives ability to GetAbilitySystemComponent()
{
	GENERATED_BODY()

public:

	ACharacterBase();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Ability System */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
	FORCEINLINE TArray<TSubclassOf<UGameplayAbility>> GetStartupAbilities(){return StartupAbilities;}
	// Combat Interface
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	TArray<FTaggedMontage> AttackMontages;

	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	
	void AddCharacterAbilities();
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category= "Combat")
	FName WeaponTipSocketName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	virtual void InitializeDefaultAttributes() const;
	
private:	

};
