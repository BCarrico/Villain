// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/VillainUserWidget.h"

void UVillainUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
