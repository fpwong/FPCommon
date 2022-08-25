// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FPCAsyncTask_TimedEvents.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimedEvent, FGameplayTag, EventTag);

USTRUCT(BlueprintType)
struct FTimedEvent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Time;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag EventTag;
};

UCLASS(BlueprintType, meta=(ExposedAsyncProxy = AsyncTask))
class FPCOMMON_API UFPCAsyncTask_TimedEvents
	: public UBlueprintAsyncActionBase
	, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnTimedEvent OnTimedEvent;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"))
	static UFPCAsyncTask_TimedEvents* CreatedTimedEvents(UObject* WorldContextObject, TArray<FTimedEvent> Events, bool bStartImmediately = true);

	UFUNCTION(BlueprintCallable)
	void StartTimedEvent();

protected:
	// ~ FTickableGameObject
	void OnTick();
	virtual TStatId GetStatId() const override;
	// ~ FTickableGameObject

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void EndTask();
public:
private:
	TArray<FTimedEvent> Events;
	FTimerHandle TickHandle;
	float StartTime = -1;

	int NextEventIndex = 0;
};
