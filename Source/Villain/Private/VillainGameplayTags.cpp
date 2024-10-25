// Fill out your copyright notice in the Description page of Project Settings.


#include "VillainGameplayTags.h"
#include "GameplayTagsManager.h"

FVillainGameplayTags FVillainGameplayTags::GameplayTags;

void FVillainGameplayTags::InitializeNativeGameplayTags()
{
	// TEST Tags
	GameplayTags.Test_TestTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Test.TestTag"), FString("Tag used for testing"));
	
	// Secondary Attributes
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxHealth"), FString("Maximum amount of Health obtainable"));
	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"), FString("Chance to double damage plus critical hit bonus"));
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"), FString("Bonus damage added when a critical hit is scored"));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"), FString("Reduces Critical Hit Chance of attacking enemies"));
	
	// Player Tags
	GameplayTags.Player_Block_CursorTrace = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.CursorTrace"), FString("Block tracing under cursor"));

	// Input Tags
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"), FString("InputTag for LMB"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"), FString("InputTag for RMB"));

	// Combat Sockets
	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Weapon"), FString("Weapon"));

	// Weapon Tags
	GameplayTags.EquippedWeapon_Test = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("EquippedWeapon.Test"), FString("Test Weapon Tag"));

	// Event Tags
	GameplayTags.Event_Montage_Test = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Montage.Test"), FString("Test Event Montage Tag"));

	// Mutation Tags
	GameplayTags.Mutation_WellFed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Mutation.WellFed"), FString("Increase character size scale"));

	// Damage Types
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("Damage"));
	GameplayTags.Damage_TestDamageType = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.TestDamageType"), FString("Test Damage Type"));

	// Resistance Types
	GameplayTags.Attributes_Resistance_Test = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Test")), FString("Test Resistance Type");
	// Map of Damage Types to Resistances
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_TestDamageType, GameplayTags.Attributes_Resistance_Test);


}
