// Fill out your copyright notice in the Description page of Project Settings.

#include "FPCMeshOutline.h"

#include "Components/PoseableMeshComponent.h"

FSkeletalMeshOutline::FSkeletalMeshOutline(USkeletalMeshComponent* InOriginalMesh, UPoseableMeshComponent* InPoseableMeshComponent)
	: OriginalMesh(InOriginalMesh)
	, PoseableMeshComponent(InPoseableMeshComponent)
{
}

// Sets default values for this component's properties
UFPCMeshOutline::UFPCMeshOutline()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostPhysics;
}

// Called when the game starts
void UFPCMeshOutline::BeginPlay()
{
	Super::BeginPlay();
}

void UFPCMeshOutline::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (const auto KeyValue : Layers)
	{
		const FSkeletalMeshOutline& MeshOutline = KeyValue.Value;
		MeshOutline.PoseableMeshComponent->CopyPoseFromSkeletalComponent(MeshOutline.OriginalMesh);
	}
}

void UFPCMeshOutline::AddLayer(FGameplayTag LayerID, UMeshComponent* MeshComponent, UMaterialInterface* Material)
{
	if (!MeshComponent || Material == nullptr)
	{
		return;
	}

	if (Layers.Contains(LayerID))
	{
		return;
	}

	if (USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(MeshComponent))
	{
		UPoseableMeshComponent* PoseableMesh = NewObject<UPoseableMeshComponent>(this);
		if (!PoseableMesh)
		{
			return;
		}
		PoseableMesh->RegisterComponent();
		
		PoseableMesh->SetSkeletalMesh(SkeletalMeshComponent->SkeletalMesh);

		PoseableMesh->SetWorldScale3D(FVector(1.05f));
		PoseableMesh->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		// switch materials
		if (Material)
		{
			const int32 NumMaterials = PoseableMesh->GetNumMaterials();
			for (int32 i = 0; i < NumMaterials; i++)
			{
				PoseableMesh->SetMaterial(i, Material);
			}
		}

		Layers.Add(LayerID, FSkeletalMeshOutline(SkeletalMeshComponent, PoseableMesh));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TODO: Update mesh outline to work with non-skeletal meshes"));
	}
}

void UFPCMeshOutline::RemoveLayer(FGameplayTag LayerID)
{
	if (FSkeletalMeshOutline* MeshOutline = Layers.Find(LayerID))
	{
		(*MeshOutline).PoseableMeshComponent->DestroyComponent();
	}

	Layers.Remove(LayerID);
}