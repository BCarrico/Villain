// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "VillainInputConfig.generated.h"
struct FGameplayTag;

USTRUCT(BlueprintType)
struct FVillainInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	//TODO: Should be including GameplayTagContainer, not FGameplayTag;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};
/**
 * 
 */
UCLASS()
class VILLAIN_API UVillainInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FVillainInputAction> AbilityInputActions;
};
