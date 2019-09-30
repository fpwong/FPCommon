// Fill out your copyright notice in the Description page of Project Settings.

#include "FPCBlueprintLibrary.h"
#include "ISlateEditableTextWidget.h"
#include "GameFramework/PlayerController.h"

FAISenseAffiliationFilter UFPCBlueprintLibrary::MakeAffiliationFilter(const bool bDetectEnemies, const bool bDetectNeutrals, const bool bDetectFriendlies)
{
	FAISenseAffiliationFilter Filter;
	Filter.bDetectEnemies = bDetectEnemies;
	Filter.bDetectNeutrals = bDetectNeutrals;
	Filter.bDetectFriendlies = bDetectFriendlies;
	return Filter;
}

float UFPCBlueprintLibrary::GetAngleBetweenVectors(FVector A, FVector B)
{
	return FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(A, B)));
}