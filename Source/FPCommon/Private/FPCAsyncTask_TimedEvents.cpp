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

	if (bStartImmediately)
	{
		TimedEvents->StartTimedEvent();
	}

	return TimedEvents;
}

void UFPCAsyncTask_TimedEvents::OnTick()
{
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

		UE_LOG(LogTemp, Warning, TEXT("%d"), i);

		// we have reached the end, end the task
		if (i == Events.Num())
		{
			EndTask();
		}
	}
}

TStatId UFPCAsyncTask_TimedEvents::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UFPCAsyncTask_TimedEvents, STATGROUP_Tickables);
}

void UFPCAsyncTask_TimedEvents::Tick(float DeltaTime)
{
	if (StartTime >= 0)
	{
		OnTick();
	}
}

void UFPCAsyncTask_TimedEvents::StartTimedEvent()
{
	if (!TickHandle.IsValid())
	{
		StartTime = GetWorld()->GetTimeSeconds();
		// GetWorld()->GetTimerManager().SetTimer(TickHandle, this, &UFPCAsyncTask_TimedEvents::OnTick, 0.0f, true);
	}
}

void UFPCAsyncTask_TimedEvents::EndTask()
{
	SetReadyToDestroy();
	MarkAsGarbage();

	if (TickHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(TickHandle);
		TickHandle.Invalidate();
	}
}
