// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VillainPlayerState.h"

#include "AbilitySystem/VillainAbilitySystemComponent.h"
#include "AbilitySystem/VillainAttributeSet.h"

AVillainPlayerState::AVillainPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UVillainAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UVillainAttributeSet>("AttributeSet");
	
	// How often the server will try to update clients. Lyra & Fortnite use about 100.f as well. 
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AVillainPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
