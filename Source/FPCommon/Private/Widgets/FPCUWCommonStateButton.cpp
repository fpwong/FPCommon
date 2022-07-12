// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/FPCUWCommonStateButton.h"

void UFPCUWCommonStateButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateButtonTextFromState();
}

void UFPCUWCommonStateButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UpdateButtonTextFromState();
	OnClicked().AddUObject(this, &UFPCUWCommonStateButton::HandleToggleButtonClicked);
}

void UFPCUWCommonStateButton::HandleToggleButtonClicked()
{
	CurrentState = (CurrentState + 1) % States.Num();
	UpdateButtonTextFromState();
}

void UFPCUWCommonStateButton::UpdateButtonTextFromState()
{
	if (!ButtonLabel)
	{
		return;
	}

	if (States.IsValidIndex(CurrentState))
	{
		ButtonLabel->SetText(States[CurrentState]);
	}
	else
	{
		ButtonLabel->SetText(FText::FromString("None"));
	}
}
