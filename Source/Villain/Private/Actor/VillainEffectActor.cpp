// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/VillainEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"



AVillainEffectActor::AVillainEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Add collision, mesh, etc., in editor
}


void AVillainEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVillainEffectActor::OnOverlap(AActor* TargetActor)
{
}

void AVillainEffectActor::OnEndOverlap(AActor* TargetActor)
{
}

void AVillainEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);
    FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

}

