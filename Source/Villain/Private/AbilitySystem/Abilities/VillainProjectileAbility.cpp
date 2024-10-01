// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/VillainProjectileAbility.h"

#include "Actor/VillainProjectile.h"
#include "Interaction/CombatInterface.h"

void UVillainProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UVillainProjectileAbility::SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag,
                                                bool bOverridePitch, float PitchOverride)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	
	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), SocketTag);
	//FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		
	FTransform SpawnTransform;
	//if (bOverridePitch)
	//{
	//	Rotation.Pitch = PitchOverride;
	//}
	SpawnTransform.SetLocation(SocketLocation);
	//SpawnTransform.SetRotation(Rotation.Quaternion());
	
	AVillainProjectile* Projectile = GetWorld()->SpawnActorDeferred<AVillainProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
	Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
	//TODO Add DamageEffectParams
	//Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
	
	Projectile->FinishSpawning(SpawnTransform);
}
