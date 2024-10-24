// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * VillainGameplayTags
 * Singleton containing native GameplayTags
 */
struct FVillainGameplayTags
{
 
public:
 static const FVillainGameplayTags& Get(){return GameplayTags;}
 static void InitializeNativeGameplayTags();

 // TEST Tags
 FGameplayTag Test_TestTag;
 
 // Secondary Attributes
 FGameplayTag Attributes_Secondary_MaxHealth;
 
 // Player Tags
 FGameplayTag Player_Block_CursorTrace;

 // Input Tags
 FGameplayTag InputTag_LMB;
 FGameplayTag InputTag_RMB;

 // Combat Socket Tags
 FGameplayTag CombatSocket_Weapon;

 // Weapon Tags
 FGameplayTag EquippedWeapon_Test;

 // Event Tags
 FGameplayTag Event_Montage_Test;

 // Mutation Tags
 FGameplayTag Mutation_WellFed;

 // Damage Type Tags
 FGameplayTag Damage;
 FGameplayTag Damage_TestDamageType;

 // Resistance Type Tags
 FGameplayTag Attributes_Resistance_Test;
 TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;
protected:
private:
 static FVillainGameplayTags GameplayTags;
};
