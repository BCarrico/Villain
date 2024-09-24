// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class VILLAIN_API AEnemyBase : public ACharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AEnemyBase();

	// Enemy Interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
};
