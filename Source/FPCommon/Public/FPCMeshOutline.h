// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Materials/MaterialInterface.h"
#include "FPCMeshOutline.generated.h"

class UPoseableMeshComponent;
class UMaterialInterface;

USTRUCT()
struct FSkeletalMeshOutline
{
	GENERATED_BODY()
	
	USkeletalMeshComponent* OriginalMesh;
	UPoseableMeshComponent* PoseableMeshComponent;

	FSkeletalMeshOutline() { OriginalMesh = nullptr; PoseableMeshComponent = nullptr; }
	FSkeletalMeshOutline(USkeletalMeshComponent* InOriginalMesh, UPoseableMeshComponent* InPoseableMeshComponent);
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPCOMMON_API UFPCMeshOutline : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFPCMeshOutline();

	UFUNCTION(BlueprintCallable)
	void AddLayer(FGameplayTag LayerID, UMeshComponent* MeshComponent, UMaterialInterface* Material);

	UFUNCTION(BlueprintCallable)
	void RemoveLayer(FGameplayTag LayerID);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// TMap<FGameplayTag, UMeshComponent*> Outlines; 
	TMap<FGameplayTag, FSkeletalMeshOutline> Layers; 
};
