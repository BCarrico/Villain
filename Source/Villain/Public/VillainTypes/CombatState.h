// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECombatState : uint8
{
 ECS_Unoccupied UMETA(DisplayName = "Unoccupied"),
 ECS_Reloading UMETA(DisplayName = "Reloading"),
 ECS_SwappingWeapons UMETA(DisplayName = "Swapping Weapons"),
 ECS_MAX UMETA(DisplayName = "DefaultMAX")
};