// Fill out your copyright notice in the Description page of Project Settings.


#include "FPCBlueprintLibrary.h"

FAISenseAffiliationFilter UFPCBlueprintLibrary::MakeAffiliationFilter(const bool bDetectEnemies, const bool bDetectNeutrals, const bool bDetectFriendlies)
{
	FAISenseAffiliationFilter Filter;
	Filter.bDetectEnemies = bDetectEnemies;
	Filter.bDetectNeutrals = bDetectNeutrals;
	Filter.bDetectFriendlies = bDetectFriendlies;
	return Filter;
}