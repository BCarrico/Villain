// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/VillainAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnHealthChanged.Broadcast(GetVillainAS()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetVillainAS()->GetMaxHealth());
}
