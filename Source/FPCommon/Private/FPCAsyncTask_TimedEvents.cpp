// Fill out your copyright notice in the Description page of Project Settings.

#include "FPCAsyncTask_TimedEvents.h"

UFPCAsyncTask_TimedEvents* UFPCAsyncTask_TimedEvents::CreatedTimedEvents(UObject* WorldContextObject, TArray<FTimedEvent> Events, bool bStartImmediately)
{
	if (Events.Num() == 0)
	{
		return nullptr;
	}

	UFPCAsyncTask_TimedEvents* TimedEvents = NewObject<UFPCAsyncTask_TimedEvents>(WorldContextObject);
	TimedEvents->Events = Events;
	TimedEvents->RegisterWithGameInstance(WorldContextObject);

	if (bStartImmediately)
	{
		TimedEvents->StartTimedEvent();
	}

	return TimedEvents;
}

void UFPCAsyncTask_TimedEvents::OnTick()
{
	if (!IsValid(this))
	{
		// UE_LOG(LogTemp, Warning, TEXT("Why am i still ticking %p"), this);
		return;
	}

	const float TimeSinceStart = GetWorld()->GetTimeSeconds() - StartTime;

	// assume events are in time order
	for (int i = NextEventIndex; i < Events.Num(); ++i)
	{
		if (TimeSinceStart <= Events[i].Time)
		{
			break;
		}

		// trigger the event since our time is greater than the event
		NextEventIndex = i + 1;

		OnTimedEvent.Broadcast(Events[i].EventTag);

		// UE_LOG(LogTemp, Warning, TEXT("%d"), i);

		// we have reached the end, end the task
		if (NextEventIndex == Events.Num())
		{
			// UE_LOG(LogTemp, Warning, TEXT("Finished?"));
			OnFinished.Broadcast();
			EndTask();
		}
	}
}

// TStatId UFPCAsyncTask_TimedEvents::GetStatId() const
// {
// 	RETURN_QUICK_DECLARE_CYCLE_STAT(UFPCAsyncTask_TimedEvents, STATGROUP_Tickables);
// }

// void UFPCAsyncTask_TimedEvents::Tick(float DeltaTime)
// {
// 	if (StartTime >= 0)
// 	{
// 		OnTick();
// 	}
// }

void UFPCAsyncTask_TimedEvents::StartTimedEvent()
{
	StartTime = GetWorld()->GetTimeSeconds();

	if (!TickHandle.IsValid())
	{
		// TODO figure out how to delete FTickableGameObject, for some reason the obj never gets cleaned up?
		GetWorld()->GetTimerManager().SetTimer(TickHandle, this, &UFPCAsyncTask_TimedEvents::OnTick, 0.025f, true);
	}
}

TArray<FTimedEvent> UFPCAsyncTask_TimedEvents::MakeTimedEventsFixedDelay(FGameplayTag EventTag, int NumEvents, float Delay, float InitialDelay)
{
	TArray<FTimedEvent> OutEvents;

	for (int i = 0; i < NumEvents; ++i)
	{
		OutEvents.Add(FTimedEvent(InitialDelay + (i * Delay), EventTag));
	}

	return OutEvents;
}

void UFPCAsyncTask_TimedEvents::EndTask()
{
	if (IsRooted())
	{
		RemoveFromRoot();
	}

	SetReadyToDestroy();
	MarkAsGarbage();

	// UE_LOG(LogTemp, Warning, TEXT("END TASK %p"), this);

	if (TickHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(TickHandle);
		TickHandle.Invalidate();
	}
}

// ETickableTickType UFPCAsyncTask_TimedEvents::GetTickableTickType() const
// {
// 	return HasAnyFlags(RF_ClassDefaultObject) ? ETickableTickType::Never : ETickableTickType::Always;
// }
