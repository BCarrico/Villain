// Fill out your copyright notice in the Description page of Project Settings.


#include "VillainAssetManager.h"
#include "AbilitySystemGlobals.h"
#include "VillainGameplayTags.h"

UVillainAssetManager& UVillainAssetManager::Get()
{
	check (GEngine);
	UVillainAssetManager* AuraAssetManager = Cast<UVillainAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UVillainAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FVillainGameplayTags::InitializeNativeGameplayTags();

	// Required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}
