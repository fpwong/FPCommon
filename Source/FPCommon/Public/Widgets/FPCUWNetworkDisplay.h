// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonTextBlock.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "FPCUWNetworkDisplay.generated.h"

/**
 * 
 */
UCLASS()
class FPCOMMON_API UFPCUWNetworkDisplay : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> NetworkLabel;

	virtual void NativeOnInitialized() override;
};
