// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/VillainAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

UVillainAttributeSet::UVillainAttributeSet()
{
	// TODO: Test Attribute Setting. Please Remove.
	InitHealth(100.f);
	InitMaxHealth(125.f);
}

void UVillainAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UVillainAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UVillainAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UVillainAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UVillainAttributeSet, Health, OldHealth);
}

void UVillainAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UVillainAttributeSet, MaxHealth, OldMaxHealth);
}
