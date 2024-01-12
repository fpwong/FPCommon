// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "FPActivatableWidgetStack.generated.h"

/**
 * 
 */
UCLASS()
class FPCOMMON_API UFPActivatableWidgetStack : public UCommonActivatableWidgetStack
{
	GENERATED_BODY()

public:
	virtual void OnWidgetAddedToList(UCommonActivatableWidget& AddedWidget) override;
};
