// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum ETurningInPlace : uint8
{
	ETIP_Left UMETA(DisplayName = "Turning Left"),
	ETIP_Right UMETA(DisplayName = "Turning Right"),
	ETIP_NotTurning UMETA(DisplayName = "Not Turning"),
	ETIP_MAX UMETA(DisplayName = "DefaultMAX"),
};

/**
 * 
 */
class VILLAIN_API TurningInPlace
{
public:
	TurningInPlace();
};
