// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "FPCTaggedObjectSubsystem.generated.h"

UCLASS()
class FPCOMMON_API UFPCTaggedObjectSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UFUNCTION(BlueprintCallable)
	void AddObject(UObject* Obj, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable)
	void RemoveObject(UObject* Obj, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable)
	TArray<UObject*> GetTaggedObjects(FGameplayTag Tag);

protected:
	TMap<FGameplayTag, TArray<TWeakObjectPtr<UObject>>> TaggedObjects;
};
