// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VillainHUD.generated.h"

class AVillainPlayerController;

USTRUCT(BlueprintType)
struct FHUDPackage
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UTexture2D* CrosshairsCenter;
	UPROPERTY()
	UTexture2D* CrosshairsRight;
	UPROPERTY()
	UTexture2D* CrosshairsLeft;
	UPROPERTY()
	UTexture2D* CrosshairsTop;
	UPROPERTY()
	UTexture2D* CrosshairsBottom;
	float CrosshairSpread;
	FLinearColor CrosshairsColor;
};

/**
 * 
 */
UCLASS()
class VILLAIN_API AVillainHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;
	FORCEINLINE void SetHUDPackage(const FHUDPackage& Package){HUDPackage = Package;}

private:
	FHUDPackage HUDPackage;
	
	UPROPERTY()
	AVillainPlayerController* PlayerController;
	
	void DrawCrosshair(UTexture2D* Texture, FVector2d ViewportCenter, FVector2d Spread, FLinearColor CrosshairColor);
	UPROPERTY(EditAnywhere)
	float CrosshairSpreadMax = 16.f;
};
