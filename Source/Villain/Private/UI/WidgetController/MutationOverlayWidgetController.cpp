// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/MutationOverlayWidgetController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Actor/VillainEffectActor.h"
#include "Character/VillainCharacter.h"
#include "Data/MutateEffectInfo.h"

void UMutationOverlayWidgetController::BroadcastInitialValues()
{
	
}

void UMutationOverlayWidgetController::BindCallbacksToDependencies()
{
	
}

void UMutationOverlayWidgetController::ApplyEffect_Implementation(AActor* TargetActor, int32 Index)
{

	AVillainCharacter* VillainCharacter = Cast<AVillainCharacter>(TargetActor);
	VillainCharacter->ApplyEffectToSelf(SelectedEffects[Index].GameplayEffect, 0);
	
}


void UMutationOverlayWidgetController::SelectRandomMutateEffects(int32 NumToSelect)
{
	if (MutateEffectInfo->MutateEffectInformation.Num() == 0 || NumToSelect <= 0) return;
	MutationPool = MutateEffectInfo->MutateEffectInformation;
	for (int32 i = 0; i < NumToSelect; i++)
	{
		int32 RandomIndex = FMath::RandRange(0, MutationPool.Num() - 1);
		SelectedEffects.Add(MutationPool[RandomIndex]);
		MutationPool.RemoveAt(RandomIndex);
	}
}

