// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "FPCUWCommonButton.generated.h"

UCLASS(Abstract, Blueprintable, ClassGroup = UI, meta = (Category = "FP Common UI", DisableNativeTick))
class FPCOMMON_API UFPCUWCommonButton : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	virtual void NativeOnCurrentTextStyleChanged() override;

	// fix for playing sound when clicked (ignores pressed method)
	virtual void HandleTriggeringActionCommited() override;
	virtual void NativeOnPressed() override;
	virtual void NativeOnClicked() override;
	

	virtual bool Initialize() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UCommonTextBlock* ButtonLabel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPCommonButton", meta = (ExposeOnSpawn = true))
	FText InitialButtonText;

	void SetButtonLabelText(const FText& InText);

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif
};
