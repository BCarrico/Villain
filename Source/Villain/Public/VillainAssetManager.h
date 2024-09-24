// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "VillainAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class VILLAIN_API UVillainAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UVillainAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
