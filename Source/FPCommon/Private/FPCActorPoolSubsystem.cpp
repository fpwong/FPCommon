// Fill out your copyright notice in the Description page of Project Settings.

#include "FPCActorPoolSubsystem.h"

AActor* UFPCActorPoolSubsystem::SpawnOrRetrieveFromPool(TSubclassOf<AActor> ActorClass, FTransform Transform)
{
	AActor* PooledActor;

	TArray<TObjectPtr<AActor>>* Pool = PooledActors.Find(ActorClass);
	if (Pool && Pool->Num() > 0)
	{
		PooledActor = Pool->Pop();
		PooledActor->SetActorTransform(Transform, false, nullptr, ETeleportType::ResetPhysics);
		PooledActor->SetActorTickEnabled(true);
		PooledActor->InitializeComponents();
		--NumActorPooled;
	}
	else // spawn new actor
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		PooledActor = GetWorld()->SpawnActor<AActor>(ActorClass, Transform, SpawnParameters);
	}

	PooledActor->SetActorHiddenInGame(false);
	PooledActor->SetActorEnableCollision(true);
	IFPCPoolableActorInterface::Execute_ActorPoolActivate(PooledActor);
	return PooledActor;
}

void UFPCActorPoolSubsystem::ReleaseActorToPool(AActor* Actor)
{
	TArray<TObjectPtr<AActor>>& Pool = PooledActors.FindOrAdd(Actor->GetClass());
	if (!Pool.Contains(Actor))
	{
		Actor->SetActorHiddenInGame(true);
		Actor->SetActorEnableCollision(false);
		Actor->SetActorTickEnabled(false);
		Actor->UninitializeComponents();
		IFPCPoolableActorInterface::Execute_ActorPoolDeactivate(Actor);
		Pool.Add(Actor);
		++NumActorPooled;
	}
}
