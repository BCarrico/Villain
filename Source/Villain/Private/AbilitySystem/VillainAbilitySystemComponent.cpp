// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/VillainAbilitySystemComponent.h"

void UVillainAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UVillainAbilitySystemComponent::ClientEffectApplied);
}

void UVillainAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	//EffectAssetTags.Broadcast(TagContainer);

	//TODO: Uncomment above, once below is in OverlayWidgetController, see video 56
	for (const FGameplayTag& Tag : TagContainer)
	{
		const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);
	}
}
