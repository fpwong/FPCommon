// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FPCAsyncTask_TimedEvents.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimedEvent, FGameplayTag, EventTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFPOnTimedEventsFinished);

USTRUCT(BlueprintType)
struct FTimedEvent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Time = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag EventTag;
};

UCLASS(BlueprintType, meta=(ExposedAsyncProxy = AsyncTask))
class FPCOMMON_API UFPCAsyncTask_TimedEvents
	: public UBlueprintAsyncActionBase
	// , public FTickableGameObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnTimedEvent OnTimedEvent;

	UPROPERTY(BlueprintAssignable)
	FFPOnTimedEventsFinished OnFinished;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"))
	static UFPCAsyncTask_TimedEvents* CreatedTimedEvents(UObject* WorldContextObject, TArray<FTimedEvent> Events, bool bStartImmediately = true);

	UFUNCTION(BlueprintCallable)
	void StartTimedEvent();

	UFUNCTION(BlueprintCallable)
	static TArray<FTimedEvent> MakeTimedEventsFixedDelay(FGameplayTag EventTag, int NumEvents = 1, float Delay = 0.1f, float InitialDelay = 0.0f);

protected:
	// ~ FTickableGameObject
	// virtual void Tick(float DeltaTime) override;
	// virtual TStatId GetStatId() const override;
	// virtual ETickableTickType GetTickableTickType() const override;
	// ~ FTickableGameObject

	void OnTick();

	UFUNCTION(BlueprintCallable)
	void EndTask();
public:
private:
	TArray<FTimedEvent> Events;
	FTimerHandle TickHandle;
	float StartTime = -1;

	int NextEventIndex = 0;

};
