// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/VillainWidgetController.h"
#include "MutationOverlayWidgetController.generated.h"

class UEditableTextBox;
struct FVillainMutateEffectInfo;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class VILLAIN_API UMutationOverlayWidgetController : public UVillainWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ApplyEffect(AActor* TargetActor, int32 Index);
	
	UFUNCTION(BlueprintCallable)
	void SelectRandomMutateEffects(int32 NumToSelect);

	//UFUNCTION(BlueprintCallable)
	//void UpdateMutationEffects(TArray<FVillainMutateEffectInfo> EffectsToShow);

	UPROPERTY(BlueprintReadOnly, Category = "Mutate Effects")
	TArray<FVillainMutateEffectInfo> SelectedEffects;

private:
	TArray<FVillainMutateEffectInfo> MutationPool;
	
};
