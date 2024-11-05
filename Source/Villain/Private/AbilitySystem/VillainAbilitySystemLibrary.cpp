// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/VillainAbilitySystemLibrary.h"
#include "AbilitySystemComponent.h"
#include "Data/CharacterClassInfo.h"
#include "Game/VillainGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "VillainAbilityTypes.h"
#include "VillainGameplayTags.h"
#include "Player/VillainPlayerState.h"
#include "UI/HUD/VillainHUD.h"
#include "UI/WidgetController/VillainWidgetController.h"


bool UVillainAbilitySystemLibrary::MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, AVillainHUD*& OutVillainHUD)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		OutVillainHUD = Cast<AVillainHUD>(PC->GetHUD());
		if (OutVillainHUD)
		{
			AVillainPlayerState* PS = PC->GetPlayerState<AVillainPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			OutWCParams.AttributeSet = AS;
			OutWCParams.AbilitySystemComponent= ASC;
			OutWCParams.PlayerController = PC;
			OutWCParams.PlayerState = PS;

			return true;
		}
	}
	return false;
}

UOverlayWidgetController* UVillainAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	AVillainHUD* VillainHUD = nullptr;
	
	if (MakeWidgetControllerParams(WorldContextObject, WCParams, VillainHUD))
	{
		return VillainHUD->GetOverlayWidgetController(WCParams);
	}
	return nullptr;
}

UMutationOverlayWidgetController* UVillainAbilitySystemLibrary::GetMutationOverlayWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	AVillainHUD* VillainHUD = nullptr;
	
	if (MakeWidgetControllerParams(WorldContextObject, WCParams, VillainHUD))
	{
		return VillainHUD->GetMutationOverlayWidgetController(WCParams);
	}
	return nullptr;
}

void UVillainAbilitySystemLibrary::InitializeDefaultAttributes(ECharacterClass CharacterClass, float Level, const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	
	const AActor* AvatarActor = ASC->GetAvatarActor();
	
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return;
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	//FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	//PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	
	//const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	//ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

UCharacterClassInfo* UVillainAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	const AVillainGameModeBase* VillainGameMode = Cast<AVillainGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (VillainGameMode == nullptr) return nullptr;
	return VillainGameMode->CharacterClassInfo;
}

UAbilityInfo* UVillainAbilitySystemLibrary::GetAbilityInfo(const UObject* WorldContextObject)
{
	const AVillainGameModeBase* VillainGameMode = Cast<AVillainGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (VillainGameMode == nullptr) return nullptr;
	return VillainGameMode->AbilityInfo;
}

bool UVillainAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FVillainGameplayEffectContext* VillainEffectContext = static_cast<const FVillainGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return VillainEffectContext->IsBlockedHit();
	};
	return false;
}

bool UVillainAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FVillainGameplayEffectContext* VillainEffectContext = static_cast<const FVillainGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return VillainEffectContext->IsCriticalHit();
	};
	return false;
}

void UVillainAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit)
{
	if (FVillainGameplayEffectContext* AuraEffectContext = static_cast<FVillainGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	};
}

FGameplayEffectContextHandle UVillainAbilitySystemLibrary::ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams)
{
	const FVillainGameplayTags& GameplayTags = FVillainGameplayTags::Get();
	const AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();
	
	FGameplayEffectContextHandle EffectContextHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(SourceAvatarActor);
	//SetDeathImpulse(EffectContextHandle, DamageEffectParams.DeathImpulse);
	//SetKnockbackForce(EffectContextHandle, DamageEffectParams.KnockbackForce);
	
	//SetIsRadialDamage(EffectContextHandle, DamageEffectParams.bIsRadialDamage);
	//SetRadialDamageInnerRadius(EffectContextHandle, DamageEffectParams.RadialDamageInnerRadius);
	//SetRadialDamageOuterRadius(EffectContextHandle, DamageEffectParams.RadialDamageOuterRadius);
	//SetRadialDamageOrigin(EffectContextHandle, DamageEffectParams.RadialDamageOrigin);
	
	const FGameplayEffectSpecHandle SpecHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectParams.DamageGameplayEffectClass, DamageEffectParams.AbilityLevel, EffectContextHandle);
	
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageEffectParams.DamageType, DamageEffectParams.BaseDamage);
	//UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Chance, DamageEffectParams.DebuffChance);
	//UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Damage, DamageEffectParams.DebuffDamage);
	//UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Duration, DamageEffectParams.DebuffDuration);
	//UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Frequency, DamageEffectParams.DebuffFrequency);
	
	DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	return EffectContextHandle;
}
