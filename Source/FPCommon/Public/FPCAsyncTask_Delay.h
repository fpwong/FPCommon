

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "FPCAsyncTask_Delay.generated.h"

// DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTagChanged, UAbilitySystemComponent*, AbilitySystemComponent, const FGameplayTag, Tag, int32, NewCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDelayEnded, int, TaskId);

/**
 * Blueprint node to automatically register a listener for changes (Begin and End) to an array of Tag tags.
 * Useful to use in UI.
 */
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = FPGAAsyncTask))
class FPCOMMON_API UFPCAsyncTask_Delay : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnDelayEnded OnDelayEnded;
		
	virtual void Activate() override;

    UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	static UFPCAsyncTask_Delay* FPCDelay(UObject* WorldContextObject, float Delay = 0.0f);
	
	// For UMG Widgets, you would call it in the Widget's Destruct event.
	UFUNCTION(BlueprintCallable)
	void EndTask();

	UFUNCTION(BlueprintPure)
	int GetTaskId();

protected:
	float DelayTime;

	FTimerHandle DelayHandle;

	UPROPERTY()
	UObject* WorldContextObject = nullptr;

	virtual void DelayEnded();
};
