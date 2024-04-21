// Copyright 2020 Dan Kestranek.

#include "FPCAsyncTask_Delay.h"
#include "Kismet/KismetSystemLibrary.h"

void UFPCAsyncTask_Delay::Activate()
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->GetTimerManager().SetTimer(DelayHandle, this, &UFPCAsyncTask_Delay::DelayEnded, DelayTime);
	}
}

UFPCAsyncTask_Delay* UFPCAsyncTask_Delay::FPCDelay(UObject* WorldContextObject, float Delay)
{
	UFPCAsyncTask_Delay* DelayTask = NewObject<UFPCAsyncTask_Delay>();
	DelayTask->DelayTime = Delay;
	DelayTask->WorldContextObject = WorldContextObject;
	return DelayTask;
}

void UFPCAsyncTask_Delay::EndTask()
{
	SetReadyToDestroy();
	GetWorld()->GetTimerManager().ClearTimer(DelayHandle);
}

int UFPCAsyncTask_Delay::GetTaskId()
{
	return GetUniqueID();
}

void UFPCAsyncTask_Delay::DelayEnded()
{
	OnDelayEnded.Broadcast(GetUniqueID());
}
