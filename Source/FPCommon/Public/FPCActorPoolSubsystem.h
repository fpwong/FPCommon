// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "FPCActorPoolSubsystem.generated.h"

UINTERFACE(Blueprintable)
class FPCOMMON_API UFPCPoolableActorInterface : public UInterface
{
	GENERATED_BODY()
};

class FPCOMMON_API IFPCPoolableActorInterface : public IInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Actor Pooling")
	void PrepareForGame();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Actor Pooling")
	void PrepareForPooling();
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FFPActorPoolInitialize, AActor*, Actor);

UCLASS()
class FPCOMMON_API UFPCActorPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType="ActorClass"))
	AActor* SpawnOrRetrieveFromPool(TSubclassOf<AActor> ActorClass, FTransform Transform);

	AActor* SpawnOrRetrieveFromPoolInitialize(TSubclassOf<AActor> ActorClass, FTransform Transform, TFunctionRef<void(AActor*)> InitFunc);

	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType="ActorClass"))
	AActor* SpawnOrRetrieveFromPoolDeferred(TSubclassOf<AActor> ActorClass, FTransform Transform);

	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType="ActorClass"))
	void ReleaseActorToPool(AActor* Actor);

	template <class T>
	T* SpawnOrRetrieveFromPoolCasted(TSubclassOf<AActor> ActorClass, const FTransform& Transform)
	{
		return Cast<T>(SpawnOrRetrieveFromPool(ActorClass, Transform));
	}

	void ActivateActor(AActor* Actor, bool bInitComponents);
	void DeactivateActor(AActor* Actor);

protected:
	TMap<TSubclassOf<AActor>, TArray<TObjectPtr<AActor>>> PooledActors;

	mutable int32 NumActorSpawned = 0;
	mutable int32 NumActorPooled = 0;
};
