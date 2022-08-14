// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "FPCIdentityInterface.generated.h"

UCLASS(config=Game)
class FPCOMMON_API UFPCIdentityHelper : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static FGameplayTag GetIdentityTag(UObject* Object);
};

// This class does not need to be modified.
UINTERFACE()
class UFPCIdentityInterface : public UInterface
{
	GENERATED_BODY()
};

class FPCOMMON_API IFPCIdentityInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="FPCommon")
	FGameplayTag GetIdentityTag();
};
