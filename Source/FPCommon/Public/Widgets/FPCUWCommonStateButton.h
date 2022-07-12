// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPCUWCommonButton.h"
#include "FPCUWCommonStateButton.generated.h"

UCLASS(Abstract, Blueprintable, ClassGroup = UI, meta = (Category = "FP Common UI", DisableNativeTick))
class FPCOMMON_API UFPCUWCommonStateButton : public UFPCUWCommonButton
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FText> States;

	int32 CurrentState = 0;

	virtual void NativePreConstruct() override;

	virtual void NativeOnInitialized() override;

	UFUNCTION()
	virtual void HandleToggleButtonClicked();

	virtual void UpdateButtonTextFromState();
};
