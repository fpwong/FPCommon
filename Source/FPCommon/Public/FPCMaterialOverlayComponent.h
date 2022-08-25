// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Materials/MaterialInterface.h"
#include "FPCMaterialOverlayComponent.generated.h"

class UPoseableMeshComponent;
class UMaterialInterface;

USTRUCT()
struct FFPCSkeletalMeshBinding
{
	GENERATED_BODY()

	UPROPERTY()
	TWeakObjectPtr<USkeletalMeshComponent> OriginalMesh = nullptr;

	UPROPERTY()
	TWeakObjectPtr<UPoseableMeshComponent> PoseableMeshComponent = nullptr;

	bool IsValid();

	FFPCSkeletalMeshBinding() = default;

	FFPCSkeletalMeshBinding(USkeletalMeshComponent* InOriginalMesh, UPoseableMeshComponent* InPoseableMeshComponent);
};

USTRUCT()
struct FFPCMaterialOverlayLayer
{
	GENERATED_BODY()

	// UPROPERTY()
	// TWeakObjectPtr<USkeletalMeshComponent> OriginalMesh = nullptr;
	//
	// UPROPERTY()
	// TWeakObjectPtr<UPoseableMeshComponent> PoseableMeshComponent = nullptr;

	UPROPERTY()
	TArray<FFPCSkeletalMeshBinding> SkeletalMeshBindings;

	UPROPERTY()
	TArray<TWeakObjectPtr<UStaticMeshComponent>> StaticMeshOverlays;

	FFPCMaterialOverlayLayer() = default;
	// FFPCMaterialOverlayLayer(USkeletalMeshComponent* InOriginalMesh, UPoseableMeshComponent* InPoseableMeshComponent);

	void DestroyLayer();
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPCOMMON_API UFPCMaterialOverlayComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFPCMaterialOverlayComponent();

	UFUNCTION(BlueprintCallable)
	void AddLayer(FGameplayTag LayerID, UMeshComponent* MeshComponent, UMaterialInterface* Material);

	UFUNCTION(BlueprintCallable)
	void AddLayerFromMeshes(FGameplayTag LayerID, TArray<UMeshComponent*> MeshComponents, UMaterialInterface* Material);

	UFUNCTION(BlueprintCallable)
	void RemoveLayer(FGameplayTag LayerID);

	FFPCSkeletalMeshBinding CreateSkeletalMeshBinding(UMeshComponent* MeshComponent, UMaterialInterface* Material);

	UStaticMeshComponent* CreateStaticMeshBinding(UMeshComponent* MeshComponent, UMaterialInterface* Material);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TMap<FGameplayTag, FFPCMaterialOverlayLayer> Layers;
};
