// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/FPMaterialButton.h"

#include "CommonTextBlock.h"
#include "Components/Image.h"
#include "Kismet/KismetMaterialLibrary.h"

void UFPMaterialButton::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();

	if (ButtonLabel)
	{
		ButtonLabel->SetStyle(GetCurrentTextStyleClass());
	}
}

bool UFPMaterialButton::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (ButtonLabel)
	{
		ButtonLabel->SetText(InitialButtonText);
	}

	if (ButtonMaterial)
	{
		DynamicMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, ButtonMaterial);
		ButtonImage->SetBrushFromMaterial(DynamicMaterial);
	}

	return true;
}

void UFPMaterialButton::SetButtonLabelText(const FText& InText)
{
	if (ButtonLabel)
	{
		ButtonLabel->SetText(InText);
	}
}

void UFPMaterialButton::NativeOnHovered()
{
	Super::NativeOnHovered();

	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue("IsHovered", true);
	}
}

void UFPMaterialButton::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();

	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue("IsHovered", false);
	}
}

#if WITH_EDITOR
const FText UFPMaterialButton::GetPaletteCategory()
{
	return FText::FromString("FPCommon");
}
#endif
