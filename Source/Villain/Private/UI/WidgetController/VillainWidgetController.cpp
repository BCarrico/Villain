// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/VillainWidgetController.h"

#include "AbilitySystem/VillainAbilitySystemComponent.h"
#include "AbilitySystem/VillainAttributeSet.h"
#include "Character/VillainCharacter.h"
#include "Player/VillainPlayerController.h"
#include "Player/VillainPlayerState.h"

void UVillainWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UVillainWidgetController::BroadcastInitialValues()
{
	
}

void UVillainWidgetController::BindCallbacksToDependencies()
{
	
}

AVillainPlayerController* UVillainWidgetController::GetVillainPC()
{
	if(VillainPlayerController == nullptr)
	{
		VillainPlayerController = Cast<AVillainPlayerController>(PlayerController);
	}
	return VillainPlayerController;
}

AVillainPlayerState* UVillainWidgetController::GetVillainPS()
{
	if(VillainPlayerState == nullptr)
	{
		VillainPlayerState = Cast<AVillainPlayerState>(PlayerState);
	}
	return VillainPlayerState;
}

UVillainAbilitySystemComponent* UVillainWidgetController::GetVillainASC()
{
	if(VillainAbilitySystemComponent == nullptr)
	{
		VillainAbilitySystemComponent = Cast<UVillainAbilitySystemComponent>(AbilitySystemComponent);
	}
	return VillainAbilitySystemComponent;
}

UVillainAttributeSet* UVillainWidgetController::GetVillainAS()
{
	if(VillainAttributeSet == nullptr)
	{
		VillainAttributeSet = Cast<UVillainAttributeSet>(AttributeSet);
	}
	return VillainAttributeSet;
}


