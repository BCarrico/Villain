// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/VillainAbilitySystemComponent.h"
#include "AbilitySystem/VillainAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Villain/Villain.h"

AEnemyBase::AEnemyBase()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	
	AbilitySystemComponent = CreateDefaultSubobject<UVillainAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	AttributeSet = CreateDefaultSubobject<UVillainAttributeSet>("AttributeSet");
}

void AEnemyBase::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
	//TODO: Uncomment weapon if wanting it to be highlighted
	//Weapon->SetRenderCustomDepth(true);
	//Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AEnemyBase::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	
	//TODO: Uncomment weapon if wanting it to be highlighted
	//Weapon->SetRenderCustomDepth(false);
}

int32 AEnemyBase::GetPlayerLevel_Implementation()
{
	return Level;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();
}

void AEnemyBase::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UVillainAbilitySystemComponent>(GetAbilitySystemComponent())->AbilityActorInfoSet();
}
