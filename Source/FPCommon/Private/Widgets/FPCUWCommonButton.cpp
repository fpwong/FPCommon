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
		ButtonLabel->SetText(ButtonText);
	}

	if (UButton* Button = Cast<UButton>(WidgetTree->RootWidget))
	{
		if (UButtonSlot* ButtonSlot = Cast<UButtonSlot>(Button->GetContentSlot()))
		{
			ButtonSlot->SetHorizontalAlignment(HAlign_Center);
			ButtonSlot->SetVerticalAlignment(VAlign_Center);
		}
	}

	return true;
}

#if WITH_EDITOR
const FText UFPCUWCommonButton::GetPaletteCategory()
{
	return FText::FromString("FPCommonUI");
}
#endif
