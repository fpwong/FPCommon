// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "FPCMontageInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UFPCMontageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FPCOMMON_API IFPCMontageInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UAnimMontage* GetMontageByTag(FGameplayTag GameplayTag);
};
