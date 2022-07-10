// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonTabListWidgetBase.h"
#include "CommonTextBlock.h"
#include "FPCUWTabList.generated.h"

class UCommonAnimatedSwitcher;



UCLASS(Abstract, Blueprintable, ClassGroup = UI, meta = (Category = "FPCommon", DisableNativeTick))
class FPCOMMON_API UFPCUWTabList : public UCommonTabListWidgetBase
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UPanelWidget* TabPanel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPCommonTabList", meta = (ExposeOnSpawn = true))
	UCommonAnimatedSwitcher* WidgetSwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPCommonTabList", meta = (ExposeOnSpawn = true))
	TSubclassOf<UCommonButtonBase> TabButtonWidgetType;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif
};
