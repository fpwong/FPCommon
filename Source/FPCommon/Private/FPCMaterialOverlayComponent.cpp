// Fill out your copyright notice in the Description page of Project Settings.

#include "FPCMaterialOverlayComponent.h"

#include "Components/PoseableMeshComponent.h"

FFPCSkeletalMeshBinding::FFPCSkeletalMeshBinding(USkeletalMeshComponent* InOriginalMesh, UPoseableMeshComponent* InPoseableMeshComponent)
	: OriginalMesh(InOriginalMesh), PoseableMeshComponent(InPoseableMeshComponent)
{
}

bool FFPCSkeletalMeshBinding::IsValid()
{
	return OriginalMesh.IsValid() && PoseableMeshComponent.IsValid();
}

void FFPCMaterialOverlayLayer::DestroyLayer()
{
	for (FFPCSkeletalMeshBinding& SkeletalMeshBinding : SkeletalMeshBindings)
	{
		if (SkeletalMeshBinding.PoseableMeshComponent.IsValid())
		{
			SkeletalMeshBinding.PoseableMeshComponent->DestroyComponent();
		}
	}

	for (TWeakObjectPtr<UStaticMeshComponent> StaticMeshComponent : StaticMeshOverlays)
	{
		if (StaticMeshComponent.IsValid())
		{
			StaticMeshComponent->DestroyComponent();
		}
	}
}

// Sets default values for this component's properties
UFPCMaterialOverlayComponent::UFPCMaterialOverlayComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostPhysics;
}

// Called when the game starts
void UFPCMaterialOverlayComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UFPCMaterialOverlayComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (auto It = Layers.CreateIterator(); It; ++It)
	{
		auto& Tag = It.Key();
		auto& Layer = It.Value();

		Layer.LifeTime += DeltaTime;

		if (FFPMaterialOverlayLayerSettings* Settings = LayerSettings.Find(Tag))
		{
			if (Settings->DestroyAfterTime > 0 && Layer.LifeTime >= Settings->DestroyAfterTime)
			{
				Layer.DestroyLayer();
				It.RemoveCurrent();
				continue;
			}
		}

		for (const FFPCSkeletalMeshBinding& SkeletalMeshBinding : Layer.SkeletalMeshBindings)
		{
			if (SkeletalMeshBinding.OriginalMesh.IsValid() && SkeletalMeshBinding.PoseableMeshComponent.IsValid())
			{
				SkeletalMeshBinding.PoseableMeshComponent->CopyPoseFromSkeletalComponent(SkeletalMeshBinding.OriginalMesh.Get());
			}
		}
	}
}

void UFPCMaterialOverlayComponent::AddLayer(FGameplayTag LayerID, UMeshComponent* MeshComponent, UMaterialInterface* Material)
{
	if (!MeshComponent || Material == nullptr)
	{
		return;
	}

	if (FFPMaterialOverlayLayerSettings* Settings = LayerSettings.Find(LayerID))
	{
		if (Settings->RetriggerTime > 0)
		{
			float TimeSinceLastTriggered = GetWorld()->GetTimeSeconds() - Settings->LastTriggered;

			if (TimeSinceLastTriggered > Settings->RetriggerTime)
			{
				Settings->LastTriggered = GetWorld()->GetTimeSeconds();
			}
			else
			{
				return;
			}
		}
	}

	AddLayerFromMeshes(LayerID, {MeshComponent}, Material);
}

void UFPCMaterialOverlayComponent::AddLayerFromMeshes(FGameplayTag LayerID, TArray<UMeshComponent*> MeshComponents, UMaterialInterface* Material)
{
	if (MeshComponents.Num() == 0 || !Material)
	{
		return;
	}

	if (Layers.Contains(LayerID))
	{
		return;
	}

	FFPCMaterialOverlayLayer Layer;

	for (UMeshComponent* MeshComponent : MeshComponents)
	{
		FFPCSkeletalMeshBinding MeshBinding = CreateSkeletalMeshBinding(MeshComponent, Material);
		if (MeshBinding.IsValid())
		{
			Layer.SkeletalMeshBindings.Add(MeshBinding);
			continue;
		}

		CreateStaticMeshBinding(MeshComponent, Material);
	}

	Layers.Add(LayerID, Layer);
}

void UFPCMaterialOverlayComponent::RemoveLayer(FGameplayTag LayerID)
{
	if (FFPCMaterialOverlayLayer* Layer = Layers.Find(LayerID))
	{
		Layer->DestroyLayer();
	}

	Layers.Remove(LayerID);
}

FFPCSkeletalMeshBinding UFPCMaterialOverlayComponent::CreateSkeletalMeshBinding(UMeshComponent* MeshComponent, UMaterialInterface* Material)
{
	USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(MeshComponent);
	if (!SkeletalMeshComponent)
	{
		return FFPCSkeletalMeshBinding();
	}

	UPoseableMeshComponent* PoseableMesh = NewObject<UPoseableMeshComponent>(this);
	if (!PoseableMesh)
	{
		return FFPCSkeletalMeshBinding();
	}

	PoseableMesh->CastShadow = false;

	PoseableMesh->SetWorldScale3D(SkeletalMeshComponent->GetComponentScale() * 1.05f);
	PoseableMesh->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	PoseableMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	PoseableMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PoseableMesh->RegisterComponent();

	PoseableMesh->SetSkinnedAssetAndUpdate(SkeletalMeshComponent->GetSkeletalMeshAsset());
	PoseableMesh->CopyPoseFromSkeletalComponent(SkeletalMeshComponent);

	// switch materials
	if (Material)
	{
		const int32 NumMaterials = PoseableMesh->GetNumMaterials();
		for (int32 i = 0; i < NumMaterials; i++)
		{
			PoseableMesh->SetMaterial(i, Material);
		}
	}

	return FFPCSkeletalMeshBinding(SkeletalMeshComponent, PoseableMesh);
}

UStaticMeshComponent* UFPCMaterialOverlayComponent::CreateStaticMeshBinding(UMeshComponent* MeshComponent, UMaterialInterface* Material)
{
	UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(MeshComponent);
	if (!StaticMeshComponent)
	{
		return nullptr;
	}

	UStaticMeshComponent* NewStaticMesh = NewObject<UStaticMeshComponent>(this);
	if (!NewStaticMesh)
	{
		return nullptr;
	}

	NewStaticMesh->SetStaticMesh(StaticMeshComponent->GetStaticMesh());

	NewStaticMesh->SetWorldScale3D(StaticMeshComponent->GetComponentScale() * 1.05f);
	NewStaticMesh->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
	NewStaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	NewStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	NewStaticMesh->RegisterComponent();

	// switch materials
	if (Material)
	{
		const int32 NumMaterials = NewStaticMesh->GetNumMaterials();
		for (int32 i = 0; i < NumMaterials; i++)
		{
			NewStaticMesh->SetMaterial(i, Material);
		}
	}

	return NewStaticMesh;
}
