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
 // Vital Attributes
 FGameplayTag Attributes_Vital_MaxHealth;
protected:
private:
 static FVillainGameplayTags GameplayTags;
};
