// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define TRACE_LENGTH 80000

//#define CUSTOM_DEPTH_PURPLE 250
//#define CUSTOM_DEPTH_BLUE 251
//#define CUSTOM_DEPTH_TAN 252

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_AssaultRifle UMETA(DisplayName = "Assault Rifle"),
	EWT_OneHandedWeapon UMETA(DisplayName = "OneHanded Weapon"),
	EWT_OneHand_Left UMETA(DisplayName = "OneHanded Left"),
	EWT_TwoHandedSword UMETA(DisplayName = "TwoHanded Weapon"),
	EWT_MAX UMETA(DisplayName = "DefaultMAX"),
};


