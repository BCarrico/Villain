// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "VillainGameplayTags.h"
#include "AbilitySystem/VillainAbilitySystemLibrary.h"
#include "AbilitySystem/VillainAttributeSet.h"
#include "Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"

struct VillainDamageStatics
{
	//TODO:
	//DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	//DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	//DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	//DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	//DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	//DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	
	//DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	//DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	//DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);
	//DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);
	
	VillainDamageStatics()
	{
		//TODO:
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UVillainAttributeSet, Armor, Target, false);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UVillainAttributeSet, ArmorPenetration, Source, false);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UVillainAttributeSet, BlockChance, Target, false);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UVillainAttributeSet, CriticalHitChance, Source, false);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UVillainAttributeSet, CriticalHitResistance, Target, false);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UVillainAttributeSet, CriticalHitDamage, Source, false);

		//DEFINE_ATTRIBUTE_CAPTUREDEF(UVillainAttributeSet, FireResistance, Target, false);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UVillainAttributeSet, LightningResistance, Target, false);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UVillainAttributeSet, ArcaneResistance, Target, false);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UVillainAttributeSet, PhysicalResistance, Target, false);
		
	}
};

static const VillainDamageStatics& DamageStatics()
{
	// Accesses DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
	static VillainDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	//TODO:
	//RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	//RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	//RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	//RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	//RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	//RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);

	//RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	//RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	//RelevantAttributesToCapture.Add(DamageStatics().ArcaneResistanceDef);
	//RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
}

void UExecCalc_Damage::DetermineDebuff(const FGameplayEffectCustomExecutionParameters& ExecutionParams, const FGameplayEffectSpec& Spec, const FAggregatorEvaluateParameters EvaluationParameters, const TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& InTagsToDefs) const
{
	//TODO:
	/*const FVillainGameplayTags& GameplayTags = FVillainGameplayTags::Get();
	for (TTuple<FGameplayTag, FGameplayTag> Pair : GameplayTags.DamageTypesToDebuffs)
	{
		const FGameplayTag& DamageType = Pair.Key;
		const FGameplayTag& DebuffType = Pair.Value;
		const float TypeDamage = Spec.GetSetByCallerMagnitude(DamageType, false, -1.f);
		if (TypeDamage > -0.5f) // .5 padding for floating point imprecision
		{
			// Determine if there was a successful debuff
			const float SourceDebuffChance = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Chance, false, -1.f);

			float TargetDebuffResistance = 0.f;
			const FGameplayTag& ResistanceTag = GameplayTags.DamageTypesToResistances[DamageType];
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(InTagsToDefs[ResistanceTag], EvaluationParameters, TargetDebuffResistance);
			TargetDebuffResistance = FMath::Max<float>(TargetDebuffResistance, 0.f);
			// Each point in resistance reduces 1% chance of a debuff
			const float EffectiveDebuffChance = SourceDebuffChance * (100 - TargetDebuffResistance) / 100.f;
			const bool bDebuff = FMath::RandRange(1, 100) < EffectiveDebuffChance;
			if (bDebuff)
			{
				FGameplayEffectContextHandle ContextHandle = Spec.GetContext();

				UVillainAbilitySystemLibrary::SetIsSuccessfulDebuff(ContextHandle, true);
				UVillainAbilitySystemLibrary::SetDamageType(ContextHandle, DamageType);

				const float DebuffDamage = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Damage, false, -1.f);
				const float DebuffDuration = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Duration, false, -1.f);
				const float DebuffFrequency = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Frequency, false, -1.f);
				
				UVillainAbilitySystemLibrary::SetDebuffDamage(ContextHandle, DebuffDamage);
				UVillainAbilitySystemLibrary::SetDebuffDuration(ContextHandle, DebuffDuration);
				UVillainAbilitySystemLibrary::SetDebuffFrequency(ContextHandle, DebuffFrequency);
			}
		}
	}*/
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	const FVillainGameplayTags& Tags = FVillainGameplayTags::Get();
		
	//TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Armor, DamageStatics().ArmorDef);
	//TagsToCaptureDefs.Add(Tags.Attributes_Secondary_ArmorPenetration, DamageStatics().ArmorPenetrationDef);
	//TagsToCaptureDefs.Add(Tags.Attributes_Secondary_BlockChance, DamageStatics().BlockChanceDef);
	//TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitChance, DamageStatics().CriticalHitChanceDef);
	//TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitResistance, DamageStatics().CriticalHitResistanceDef);
	//TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitDamage, DamageStatics().CriticalHitDamageDef);
		
	//TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Fire, DamageStatics().FireResistanceDef);
	//TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Lightning, DamageStatics().LightningResistanceDef);
	//TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Arcane, DamageStatics().ArcaneResistanceDef);
	//TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Physical, DamageStatics().PhysicalResistanceDef);
	
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	int32 SourcePlayerLevel = 1;
	if (SourceAvatar->Implements<UCombatInterface>())
	{
		SourcePlayerLevel = ICombatInterface::Execute_GetPlayerLevel(SourceAvatar);
	}
	int32 TargetPlayerLevel = 1;
	if (TargetAvatar->Implements<UCombatInterface>())
	{
		TargetPlayerLevel = ICombatInterface::Execute_GetPlayerLevel(SourceAvatar);
	}
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	//TODO: Debuff
	//DetermineDebuff(ExecutionParams, Spec, EvaluationParameters, TagsToCaptureDefs);
	
	// Get Damage Set by Caller Magnitude
	float Damage = 0.f;
	/*for (auto& Pair : FVillainGameplayTags::Get().DamageTypesToResistances)
	{
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;
		
		checkf(TagsToCaptureDefs.Contains(ResistanceTag), TEXT("TagsToCaptureDefs doesn't contain Tag: [%s] in ExecCalc_Damage"), *ResistanceTag.ToString());
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = TagsToCaptureDefs[ResistanceTag];
		
		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key, false);
		if (DamageTypeValue <= 0)
		{
			continue;
		}
		
		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluationParameters, Resistance);
		Resistance = FMath::Clamp(Resistance, 0.f, 100.f);

		DamageTypeValue *= (100.f - Resistance ) / 100.f;

		if (UVillainAbilitySystemLibrary::IsRadialDamage(EffectContextHandle))
		{
			// 1. Override TakeDamage in AuraCharacterBase *
			// 2. Create delegate OnDamageDelegate, broadcast damage received in TakeDamage * (Check combat interface && AuraCharacterBase)
			// 3. Bind lambda to OnDamageDelegate on the Victim here. 
			// 4. Call UGameplayStatics::ApplyRadialDamageWithFalloff to cause damage (this will result in TakeDamage being called on the Victim, which will then broadcast OnDamageDelegate)
			// 5. In Lambda, set DamageTypeValue to teh damage received from the broadcast

			if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(TargetAvatar))
			{
				CombatInterface->GetOnDamageSignature().AddLambda([&](float DamageAmount)
				{
					DamageTypeValue = DamageAmount;
					
				});
			}
			UGameplayStatics::ApplyRadialDamageWithFalloff(
				TargetAvatar,
				DamageTypeValue,
				0.f,
				UVillainAbilitySystemLibrary::GetRadialDamageOrigin(EffectContextHandle),
				UVillainAbilitySystemLibrary::GetRadialDamageInnerRadius(EffectContextHandle),
				UVillainAbilitySystemLibrary::GetRadialDamageOuterRadius(EffectContextHandle),
				1.f,
				UDamageType::StaticClass(),
				TArray<AActor*>(),
				SourceAvatar,
				nullptr
				);
		}
		
		Damage += DamageTypeValue;
	}*/
	
	//TODO: Capture BlockChance on Target, and determine if there was a successful Block
	
	float TargetBlockChance = 0.f;
	//ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters, TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f);
	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;
	
	//UVillainAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);
	
	//TODO: If Block, halve the damage.
	Damage = bBlocked ? Damage / 2.f : Damage;
	
	/*float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluationParameters, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(SourceArmorPenetration, 0.f);
	
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters, TargetArmor);
	TargetArmor = FMath::Max<float>(TargetArmor, 0.f);

	const UCharacterClassInfo* CharacterClassInfo = UVillainAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourcePlayerLevel);
	
	// ArmorPenetration ignores a percentage of the Target's Armor
	const float EffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.f;

	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetPlayerLevel);
	// Armor ignores a percentage of incoming damage
	Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100.f;

	// Critical Hit Resistance reduces Critical Hit Chance by a certain percentage
	float TargetCriticalHitResistance = 0.f;
	float SourceCriticalHitChance = 0.f;
	float SourceCriticalHitDamage = 0.f;
	
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvaluationParameters, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(SourceCriticalHitChance, 0.f);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef, EvaluationParameters, TargetCriticalHitResistance);
	TargetCriticalHitResistance = FMath::Max<float>(TargetCriticalHitResistance, 0.f);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, EvaluationParameters, SourceCriticalHitDamage);
	SourceCriticalHitDamage = FMath::Max<float>(SourceCriticalHitDamage, 0.f);

	const FRealCurve* CriticalHitResistanceCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("CriticalHitResistance"), FString());
	const float EffectiveCriticalHitResistanceCoefficient = CriticalHitResistanceCurve->Eval(TargetPlayerLevel);
	// Critical Hit Resistance reduces Critical Hit Chance by a certain percentage
	const float EffectiveCriticalHitChance = SourceCriticalHitChance - TargetCriticalHitResistance * EffectiveCriticalHitResistanceCoefficient;
	const bool bCriticalHit = FMath::RandRange(1, 100) < EffectiveCriticalHitChance;
	
	// Set Critical Hit Boolean
	UVillainAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCriticalHit);
	
	// Double damage plus a bonus if critical hit
	Damage = bCriticalHit ? Damage * 2.f + SourceCriticalHitDamage : Damage;
	*/
	const FGameplayModifierEvaluatedData EvaluatedData(UVillainAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}