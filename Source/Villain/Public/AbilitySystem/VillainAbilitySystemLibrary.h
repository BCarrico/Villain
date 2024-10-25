// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VillainAbilitySystemLibrary.generated.h"

struct FGameplayEffectContextHandle;
class UCharacterClassInfo;
enum class ECharacterClass : uint8;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class VILLAIN_API UVillainAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:

	// Widget Controller
	
	//UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	//static bool MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, AAuraHUD*& OutAuraHUD);
	
	//UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	//static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	//UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	//static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	//UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	//static USpellMenuWidgetController* GetSpellMenuWidgetController(const UObject* WorldContextObject);
	
	// Ability System Class Defaults
	
	UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|CharacterClassDefaults")
	static void InitializeDefaultAttributes(ECharacterClass CharacterClass, float Level, const UObject* WorldContextObject, UAbilitySystemComponent* ASC);

	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|CharacterClassDefaults")
	//static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass);

	UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|CharacterClassDefaults")
	//static UAbilityInfo* GetAbilityInfo (const UObject* WorldContextObject);

	// Effect Context Getters
	
	UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|GameplayEffects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	//UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffects")
	//static bool IsSuccessfulDebuff (const FGameplayEffectContextHandle& EffectContextHandle);

	//UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static float GetDebuffDamage (const FGameplayEffectContextHandle& EffectContextHandle);

	//UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static float GetDebuffDuration (const FGameplayEffectContextHandle& EffectContextHandle);

	//UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static float GetDebuffFrequency (const FGameplayEffectContextHandle& EffectContextHandle);

	//UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static FGameplayTag GetDamageType (const FGameplayEffectContextHandle& EffectContextHandle);

	//UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static FVector GetDeathImpulse (const FGameplayEffectContextHandle& EffectContextHandle);

	//UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static FVector GetKnockbackForce (const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|GameplayEffects")
	static bool IsCriticalHit (const FGameplayEffectContextHandle& EffectContextHandle);

	//UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static bool IsRadialDamage(const FGameplayEffectContextHandle& EffectContextHandle);

	//UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static float GetRadialDamageInnerRadius(const FGameplayEffectContextHandle& EffectContextHandle);

	//UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static float GetRadialDamageOuterRadius(const FGameplayEffectContextHandle& EffectContextHandle);
	
	//UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static FVector GetRadialDamageOrigin(const FGameplayEffectContextHandle& EffectContextHandle);

	// Effect Context Setters
	
	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit);

	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);

	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static void SetIsSuccessfulDebuff(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInSuccessfulDebuff);

	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static void SetDebuffDamage(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDebuffDamage);

	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static void SetDebuffDuration(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDebuffDuration);

	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static void SetDebuffFrequency(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDebuffFrequency);

	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static void SetDamageType(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FGameplayTag& InDamageType);

	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static void SetDeathImpulse(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InImpulse);

	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static void SetKnockbackForce(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InForce);

	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static void SetIsRadialDamage(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsRadialDamage);

	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static void SetRadialDamageInnerRadius(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InInnerRadius);

	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static void SetRadialDamageOuterRadius(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InOuterRadius);

	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|GameplayEffects")
	//static void SetRadialDamageOrigin(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InOrigin);
	
	// Gameplay Mechanics
	
	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|GameplayMechanics")
	//static void GetLivePlayersWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin);

	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|GameplayMechanics")
	//static void GetClosestTargets(int32 MaxTargets, const TArray<AActor*>& Actors, TArray<AActor*>& OutClosestTargets, const FVector& Origin);
	
	//UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|GameplayMechanics")
	//static bool IsNotFriend(AActor* FirstActor, AActor* SecondActor);

	UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|DamageEffect")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams);
	
	//UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|GameplayMechanics")
	//static TArray<FRotator> EvenlySpacedRotators(const FVector& Forward, const FVector& Axis, float Spread, int32 NumRotators);
	
	//UFUNCTION(BlueprintPure, Category="VillainAbilitySystemLibray|GameplayMechanics")
	//static TArray<FVector> EvenlyRotatedVectors(const FVector& Forward, const FVector& Axis, float Spread, int32 NumVectors);

	//static int32 GetXPRewardForClassAndLevel(const UObject* WorldContextObject, ECharacterClass CharacterClass, int32 CharacterLevel);

	// Damage Effect Params

	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|DamageEffect")
	//static void SetIsRadialDamageEffectParam(UPARAM(ref) FDamageEffectParams& DamageEffectParams, bool bIsRadial, float InnerRadius, float OuterRadius, FVector Origin);
	
	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|DamageEffect")
	//static void SetKnockbackDirection(UPARAM(ref) FDamageEffectParams& DamageEffectParams, FVector KnockbackDirection, float Magnitude = 0.f);

	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|DamageEffect")
	//static void SetDeathImpulseDirection(UPARAM(ref) FDamageEffectParams& DamageEffectParams, FVector DeathImpulseDirection, float Magnitude = 0.f);

	//UFUNCTION(BlueprintCallable, Category="VillainAbilitySystemLibray|DamageEffect")
	//static void SetTargetEffectParamsASC(UPARAM(ref) FDamageEffectParams& DamageEffectParams, UAbilitySystemComponent* InASC);
};
