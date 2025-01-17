// Fill out your copyright notice in the Description page of Project Settings.


#include "FPNetTimer.h"

#include "GameFramework/GameState.h"

void FFPNetTimer::StartTimer(UObject* WorldContext)
{
	if (WorldContext)
	{
		StartTime = WorldContext->GetWorld()->GetGameStateChecked<AGameState>()->GetServerWorldTimeSeconds();
	}
}

float FFPNetTimer::GetTimeRemaining(UObject* WorldContext) const
{
	if (!WorldContext)
	{
		return 0;
	}

	const double CurrTime = WorldContext->GetWorld()->GetGameStateChecked<AGameState>()->GetServerWorldTimeSeconds();
	return Duration - (CurrTime - StartTime);
}
