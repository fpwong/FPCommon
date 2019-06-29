// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Perception/AISense.h"
#include "FPCBlueprintLibrary.generated.h"

UCLASS()
class FPCOMMON_API UFPCBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, Category = "Affiliation")
	static FAISenseAffiliationFilter MakeAffiliationFilter(bool bDetectEnemies, bool bDetectNeutrals, bool bDetectFriendlies);
};
