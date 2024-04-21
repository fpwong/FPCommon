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

void UFPCUWCommonButton::HandleTriggeringActionCommited()
{
	// HandleButtonClicked();
	Super::HandleTriggeringActionCommited();
}

void UFPCUWCommonButton::NativeOnPressed()
{
	Super::NativeOnPressed();
}

void UFPCUWCommonButton::NativeOnClicked()
{
	// // not using locked in my game but you probably want to check if it is locked and play different sound
	// if (!GetLocked())
	// {
	// 	if (UCommonButtonStyle* CurrentStyle = GetStyle())
	// 	{
	// 		FSlateApplication::Get().PlaySound(CurrentStyle->PressedSlateSound);
	// 	}
	// }
	// else
	// {
	// 	if (UCommonButtonStyle* CurrentStyle = GetStyle())
	// 	{
	// 		if (CurrentStyle->LockedPressedSlateSound.bHasSound)
	// 		{
	// 			FSlateApplication::Get().PlaySound(CurrentStyle->LockedPressedSlateSound.Sound);
	// 		}
	// 	}
	// }

	Super::NativeOnClicked();
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
