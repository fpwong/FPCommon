// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FPNetTimer.generated.h"

USTRUCT()
struct FPCOMMON_API FFPNetTimer
{
	GENERATED_BODY()

	void StartTimer(UObject* WorldContext);

	float GetTimeRemaining(UObject* WorldContext) const;

	bool HasEnded(UObject* WorldContext) const { return IsValid() && GetTimeRemaining(WorldContext) <= 0.0f; }

	bool IsValid() const { return StartTime >= 0; }

	void Clear() { StartTime = INDEX_NONE; };

	UPROPERTY(EditAnywhere)
	float Duration = 5.0f;

	UPROPERTY(Transient)
	double StartTime = INDEX_NONE;
};
