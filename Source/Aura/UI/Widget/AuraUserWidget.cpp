// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* Controller)
{
	WidgetController = Controller;
	WidgetContollerSet();
}