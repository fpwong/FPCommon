// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/FPActivatableWidgetStack.h"

#include "CommonActivatableWidget.h"

void UFPActivatableWidgetStack::OnWidgetAddedToList(UCommonActivatableWidget& AddedWidget)
{
	Super::OnWidgetAddedToList(AddedWidget);

	DisplayedWidget = AddedWidget;
	DisplayedWidget->ActivateWidget();
}
