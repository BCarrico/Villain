// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VillainPlayerState.h"

#include "AbilitySystem/VillainAbilitySystemComponent.h"
#include "AbilitySystem/VillainAttributeSet.h"
#include "Net/UnrealNetwork.h"

AVillainPlayerState::AVillainPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UVillainAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UVillainAttributeSet>("AttributeSet");
	
	// How often the server will try to update clients. Lyra & Fortnite use about 100.f as well. 
	NetUpdateFrequency = 100.f;
}

void AVillainPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AVillainPlayerState, Level);
}

UAbilitySystemComponent* AVillainPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AVillainPlayerState::OnRep_Level(int32 OldLevel)
{
	//OnLevelChangedDelegate.Broadcast(Level);
}
