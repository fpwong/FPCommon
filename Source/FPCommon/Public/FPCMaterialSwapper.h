// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Materials/MaterialInterface.h"
#include "FPCMaterialSwapper.generated.h"

class UMaterialInterface;

using FComponentMaterials = TMap<UPrimitiveComponent*, TArray<UMaterialInterface*>>;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPCOMMON_API UFPCMaterialSwapper : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFPCMaterialSwapper();

	UFUNCTION(BlueprintCallable)
	void SaveBaseMaterials();

	UFUNCTION(BlueprintCallable)
	void SaveComponentMaterials(UPrimitiveComponent* Component);

	UFUNCTION(BlueprintCallable)
	int32 AddLayer(UMaterialInterface* Material);

	UFUNCTION(BlueprintCallable)
	void RemoveLayer(int32 Index);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FComponentMaterials BaseLayer;
	TArray<UMaterialInterface*> Layers;

	void ApplyLayer(UMaterialInterface* Material);

	void ApplyBaseLayer();
};
