// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/VillainGameplayAbilityBase.h"
#include "VillainProjectileAbility.generated.h"

class AVillainProjectile;
/**
 * 
 */
UCLASS()
class VILLAIN_API UVillainProjectileAbility : public UVillainGameplayAbilityBase
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AVillainProjectile> ProjectileClass;
};
