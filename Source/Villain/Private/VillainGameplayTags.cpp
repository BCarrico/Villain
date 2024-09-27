// Fill out your copyright notice in the Description page of Project Settings.


#include "VillainGameplayTags.h"
#include "GameplayTagsManager.h"

FVillainGameplayTags FVillainGameplayTags::GameplayTags;

void FVillainGameplayTags::InitializeNativeGameplayTags()
{
	// TEST Tags
	GameplayTags.Test_TestTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Test.TestTag"), FString("Tag used for testing"));
	
	// Vital Attributes
	GameplayTags.Attributes_Vital_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxHealth"), FString("Maximum amount of Health obtainable"));
	
	// Player Tags
	GameplayTags.Player_Block_CursorTrace = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.CursorTrace"), FString("Block tracing under cursor"));

	// Input Tags
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"), FString("InputTag for LMB"));
}
