// Fill out your copyright notice in the Description page of Project Settings.

#include "FPCTaggedObjectSubsystem.h"

void UFPCTaggedObjectSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UFPCTaggedObjectSubsystem::AddObject(UObject* Obj, FGameplayTag Tag)
{
	TaggedObjects.FindOrAdd(Tag).Add(Obj);
}

void UFPCTaggedObjectSubsystem::RemoveObject(UObject* Obj, FGameplayTag Tag)
{
	TaggedObjects.FindOrAdd(Tag).Remove(Obj);
}

TArray<UObject*> UFPCTaggedObjectSubsystem::GetTaggedObjects(FGameplayTag Tag)
{
	TArray<UObject*> OutObjects;
	if (TArray<TWeakObjectPtr<UObject>>* ObjectsPtr = TaggedObjects.Find(Tag))
	{
		for (TWeakObjectPtr<UObject> Obj : *ObjectsPtr)
		{
			if (Obj.IsValid())
			{
				OutObjects.Add(Obj.Get());
			}
		}
	}

	return OutObjects;
}
