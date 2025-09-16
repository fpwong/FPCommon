// Fill out your copyright notice in the Description page of Project Settings.

#include "FPCIdentityInterface.h"

FGameplayTag UFPCIdentityHelper::GetIdentityTag(UObject* Object)
{
	if (Object && Object->Implements<UFPCIdentityInterface>())
	{
		return IFPCIdentityInterface::Execute_GetIdentityTag(Object);
	}

	return FGameplayTag();
}
