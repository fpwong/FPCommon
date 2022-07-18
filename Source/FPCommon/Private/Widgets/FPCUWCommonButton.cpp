// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/FPCUWCommonButton.h"

#include "CommonTextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ButtonSlot.h"

void UFPCUWCommonButton::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();

	if (ButtonLabel)
	{
		ButtonLabel->SetStyle(GetCurrentTextStyleClass());
	}
}

bool UFPCUWCommonButton::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (ButtonLabel)
	{
		ButtonLabel->SetText(InitialButtonText);
	}

	return true;
}

void UFPCUWCommonButton::SetButtonLabelText(const FText& InText)
{
	if (ButtonLabel)
	{
		ButtonLabel->SetText(InText);
	}
}

#if WITH_EDITOR
const FText UFPCUWCommonButton::GetPaletteCategory()
{
	return FText::FromString("FPCommon");
}
#endif
