// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/VillainAbilitySystemGlobals.h"

#include "VillainAbilityTypes.h"

FGameplayEffectContext* UVillainAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FVillainGameplayEffectContext();
}
