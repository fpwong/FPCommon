// Fill out your copyright notice in the Description page of Project Settings.

#include "FPCActorPoolSubsystem.h"

AActor* UFPCActorPoolSubsystem::SpawnOrRetrieveFromPool(TSubclassOf<AActor> ActorClass, FTransform Transform)
{
	AActor* PooledActor;

	TArray<TObjectPtr<AActor>>* Pool = PooledActors.Find(ActorClass);
	if (Pool && Pool->Num() > 0)
	{
		PooledActor = Pool->Pop();
		IFPCPoolableActorInterface::Execute_PrepareForGame(PooledActor);
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
		IFPCPoolableActorInterface::Execute_PrepareForGame(PooledActor);
	}

	PooledActor->SetActorHiddenInGame(false);
	PooledActor->SetActorEnableCollision(true);
	return PooledActor;
}

AActor* UFPCActorPoolSubsystem::SpawnOrRetrieveFromPoolInitialize(TSubclassOf<AActor> ActorClass, FTransform Transform, TFunctionRef<void(AActor*)> InitFunc)
{
	AActor* PooledActor;

	TArray<TObjectPtr<AActor>>* Pool = PooledActors.Find(ActorClass);
	if (Pool && Pool->Num() > 0)
	{
		PooledActor = Pool->Pop();
		IFPCPoolableActorInterface::Execute_PrepareForGame(PooledActor);
		PooledActor->SetActorTransform(Transform, false, nullptr, ETeleportType::ResetPhysics);
		InitFunc(PooledActor);
		PooledActor->InitializeComponents();
		--NumActorPooled;
	}
	else // spawn new actor
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		PooledActor = GetWorld()->SpawnActorDeferred<AActor>(ActorClass, Transform);
		InitFunc(PooledActor);
		PooledActor->FinishSpawning(Transform);
		IFPCPoolableActorInterface::Execute_PrepareForGame(PooledActor);
	}

	PooledActor->SetActorTickEnabled(true);
	PooledActor->SetActorHiddenInGame(false);
	PooledActor->SetActorEnableCollision(true);

	return PooledActor;
}

AActor* UFPCActorPoolSubsystem::SpawnOrRetrieveFromPoolDeferred(TSubclassOf<AActor> ActorClass, FTransform Transform)
{
	AActor* PooledActor;

	TArray<TObjectPtr<AActor>>* Pool = PooledActors.Find(ActorClass);
	if (Pool && Pool->Num() > 0)
	{
		PooledActor = Pool->Pop();
		PooledActor->SetActorTransform(Transform, false, nullptr, ETeleportType::ResetPhysics);
		--NumActorPooled;
	}
	else // spawn new actor
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		PooledActor = GetWorld()->SpawnActor<AActor>(ActorClass, Transform, SpawnParameters);
		// PooledActor = GetWorld()->SpawnActorDeferred<AActor>(ActorClass, Transform);
		IFPCPoolableActorInterface::Execute_PrepareForPooling(PooledActor);
		// DeactivateActor(PooledActor);
	}

	return PooledActor;
}

void UFPCActorPoolSubsystem::ReleaseActorToPool(AActor* Actor)
{
	TArray<TObjectPtr<AActor>>& Pool = PooledActors.FindOrAdd(Actor->GetClass());
	if (!Pool.Contains(Actor))
	{
		IFPCPoolableActorInterface::Execute_PrepareForPooling(Actor);
		Actor->SetActorHiddenInGame(true);
		Actor->SetActorEnableCollision(false);
		Actor->SetActorTickEnabled(false);
		Actor->UninitializeComponents();
		Pool.Add(Actor);
		++NumActorPooled;
	}
}

void UFPCActorPoolSubsystem::ActivateActor(AActor* Actor)
{
	Actor->SetActorHiddenInGame(false);
	Actor->SetActorEnableCollision(true);
	Actor->SetActorTickEnabled(true);
	Actor->InitializeComponents();
}

void UFPCActorPoolSubsystem::DeactivateActor(AActor* Actor)
{
	Actor->SetActorHiddenInGame(true);
	Actor->SetActorEnableCollision(false);
	Actor->SetActorTickEnabled(false);
	Actor->UninitializeComponents();
}
