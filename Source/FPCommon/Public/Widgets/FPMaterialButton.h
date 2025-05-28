// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "FPMaterialButton.generated.h"

class UImage;

UCLASS(Abstract, Blueprintable, ClassGroup = UI, meta = (Category = "FP Common UI", DisableNativeTick))
class FPCOMMON_API UFPMaterialButton : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	virtual void NativeOnCurrentTextStyleChanged() override;

	virtual bool Initialize() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> ButtonMaterial;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> ButtonImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	TObjectPtr<UCommonTextBlock> ButtonLabel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPCommonButton", meta = (ExposeOnSpawn = true, EditCondition = "ButtonLabel != nullptr", EditConditionHides))
	FText InitialButtonText;

	void SetButtonLabelText(const FText& InText);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;

	virtual void NativeOnHovered() override;
	virtual void NativeOnUnhovered() override;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif
};
