// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/VillainHUD.h"

#include "AssetTypeCategories.h"
#include "Player/VillainPlayerController.h"
#include "UI/Widget/VillainUserWidget.h"
#include "UI/WidgetController/MutationOverlayWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

void AVillainHUD::DrawHUD()
{
	Super::DrawHUD();
	
	//FVector2d ViewportSize;
	if (GEngine)
	{
		//GEngine->GameViewport->GetViewportSize(ViewportSize);
		//const FVector2d ViewportCenter(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);
		if (PlayerController == nullptr ? PlayerController = Cast<AVillainPlayerController>(GetOwningPlayerController()) : PlayerController)
		{
			FHitResult CursorHit = PlayerController->GetCursorHitResult();
			if (CursorHit.bBlockingHit)
			{
				FVector2d ScreenPosition;
				if (PlayerController->ProjectWorldLocationToScreen(CursorHit.Location, ScreenPosition))
				{
					float SpreadScaled = CrosshairSpreadMax * HUDPackage.CrosshairSpread;
					HUDPackage.CrosshairsColor = FLinearColor::White;
					if (HUDPackage.CrosshairsCenter)
					{
						FVector2d Spread(0.f, 0.f);
						DrawCrosshair(HUDPackage.CrosshairsCenter, ScreenPosition, Spread, HUDPackage.CrosshairsColor);	
					}
					if (HUDPackage.CrosshairsLeft)
					{
						FVector2d Spread(-SpreadScaled, 0.f);
						DrawCrosshair(HUDPackage.CrosshairsLeft, ScreenPosition, Spread, HUDPackage.CrosshairsColor);	
					}
					if (HUDPackage.CrosshairsRight)
					{
						FVector2d Spread(SpreadScaled, 0.f);
						DrawCrosshair(HUDPackage.CrosshairsRight, ScreenPosition, Spread, HUDPackage.CrosshairsColor);	
					}
					if (HUDPackage.CrosshairsBottom)
					{
						FVector2d Spread(0.f, SpreadScaled);
						DrawCrosshair(HUDPackage.CrosshairsBottom, ScreenPosition, Spread, HUDPackage.CrosshairsColor);	
					}
					if (HUDPackage.CrosshairsTop)
					{
						FVector2d Spread(0.f, -SpreadScaled);
						DrawCrosshair(HUDPackage.CrosshairsTop, ScreenPosition, Spread, HUDPackage.CrosshairsColor);	
					}
				}
			}
			/*float SpreadScaled = CrosshairSpreadMax * HUDPackage.CrosshairSpread;
			HUDPackage.CrosshairsColor = FLinearColor::White;
			if (HUDPackage.CrosshairsCenter)
			{
				FVector2d Spread(0.f, 0.f);
				DrawCrosshair(HUDPackage.CrosshairsCenter, ViewportCenter, Spread, HUDPackage.CrosshairsColor);	
			}
			if (HUDPackage.CrosshairsLeft)
			{
				FVector2d Spread(-SpreadScaled, 0.f);
				DrawCrosshair(HUDPackage.CrosshairsLeft, ViewportCenter, Spread, HUDPackage.CrosshairsColor);	
			}
			if (HUDPackage.CrosshairsRight)
			{
				FVector2d Spread(SpreadScaled, 0.f);
				DrawCrosshair(HUDPackage.CrosshairsRight, ViewportCenter, Spread, HUDPackage.CrosshairsColor);	
			}
			if (HUDPackage.CrosshairsBottom)
			{
				FVector2d Spread(0.f, SpreadScaled);
				DrawCrosshair(HUDPackage.CrosshairsBottom, ViewportCenter, Spread, HUDPackage.CrosshairsColor);	
			}
			if (HUDPackage.CrosshairsTop)
			{
				FVector2d Spread(0.f, -SpreadScaled);
				DrawCrosshair(HUDPackage.CrosshairsTop, ViewportCenter, Spread, HUDPackage.CrosshairsColor);	
			}*/
		}
	}
}

UOverlayWidgetController* AVillainHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		//OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

UMutationOverlayWidgetController* AVillainHUD::GetMutationOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (MutationWidgetController == nullptr)
	{
		MutationWidgetController = NewObject<UMutationOverlayWidgetController>(this, MutationWidgetControllerClass);
		MutationWidgetController->SetWidgetControllerParams(WCParams);
		//MutationWidgetController->BindCallbacksToDependencies();
	}
	return MutationWidgetController;
}

void AVillainHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"))
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class unititiailzied, please fill out BP_AuraHUD"))
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UVillainUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}

void AVillainHUD::DrawCrosshair(UTexture2D* Texture, FVector2d ViewportCenter, FVector2d Spread, FLinearColor CrosshairColor)
{
	const float TextureWidth = Texture->GetSizeX();
	const float TextureHeight = Texture->GetSizeY();
	const FVector2d TextureDrawPoint (ViewportCenter.X - (TextureWidth / 2.f) + Spread.X, ViewportCenter.Y - (TextureHeight / 2.f) + Spread.Y);
	DrawTexture(Texture, TextureDrawPoint.X, TextureDrawPoint.Y, TextureWidth, TextureHeight, 0.f, 0.f, 1.f, 1.f, CrosshairColor);
}
