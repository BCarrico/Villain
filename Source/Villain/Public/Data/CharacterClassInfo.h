// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterClassInfo.generated.h"

class UGameplayAbility;
class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
 VillainClass,
 EnemyClass
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
 GENERATED_BODY()

 UPROPERTY(EditDefaultsOnly, Category="Class Defaults")
 TSubclassOf<UGameplayEffect> PrimaryAttributes;

 UPROPERTY(EditDefaultsOnly, Category="Class Defaults")
 TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

 //UPROPERTY(EditDefaultsOnly, Category="Class Defaults")
 //FScalableFloat XPReward = FScalableFloat();
};

/**
 * 
 */
UCLASS()
class VILLAIN_API UCharacterClassInfo : public UDataAsset
{
 GENERATED_BODY()

public:

 UPROPERTY(EditDefaultsOnly, Category= "Character Class Defaults")
 TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInformation;
	
 UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults")
 TSubclassOf<UGameplayEffect> SecondaryAttributes;

 UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults")
 TSubclassOf<UGameplayEffect> VitalAttributes;

 UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults")
 TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;

 FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass CharacterClass);

 UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults|Damage")
 TObjectPtr<UCurveTable> DamageCalculationCoefficients;
};
