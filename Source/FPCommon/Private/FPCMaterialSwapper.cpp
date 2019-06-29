// Fill out your copyright notice in the Description page of Project Settings.

#include "FPCMaterialSwapper.h"

#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UFPCMaterialSwapper::UFPCMaterialSwapper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UFPCMaterialSwapper::BeginPlay()
{
	Super::BeginPlay();
}

void UFPCMaterialSwapper::SaveBaseMaterials()
{
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor)
	{
		return;
	}

	TArray<UActorComponent*> ComponentsWithMaterials = OwnerActor->GetComponentsByClass(UPrimitiveComponent::StaticClass());
	for (UActorComponent* ActorComponent : ComponentsWithMaterials)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(ActorComponent);
		SaveComponentMaterials(PrimitiveComponent);
	}
}

void UFPCMaterialSwapper::SaveComponentMaterials(UPrimitiveComponent* Component)
{
	TArray<UMaterialInterface*>& BaseLayerMaterials = BaseLayer.FindOrAdd(Component);
	const int32 NumMaterials = Component->GetNumMaterials();
	BaseLayerMaterials.Reserve(NumMaterials);

	for (int32 i = 0; i < NumMaterials; i++)
	{
		if (UMaterialInterface* Material = Component->GetMaterial(i))
		{
			BaseLayerMaterials.Add(Material);
		}
	}
}

void UFPCMaterialSwapper::AddLayer(UMaterialInterface* Material)
{
	if (Material == nullptr)
	{
		return;
	}

	Layers.Push(Material);
	ApplyLayer(Material);
}

void UFPCMaterialSwapper::RemoveLayer(UMaterialInterface* Material)
{
	if (Material == nullptr)
	{
		return;
	}

	const int32 LayerIndex = Layers.IndexOfByKey(Material);
	if (LayerIndex != -1 && LayerIndex == Layers.Num() - 1)
	{
		Layers.Pop();

		if (Layers.Num() > 0)
		{
			ApplyLayer(Layers.Last());
		}
		else
		{
			ApplyBaseLayer();
		}
	}
	else
	{
		Layers.RemoveAt(LayerIndex);
	}
}

void UFPCMaterialSwapper::ApplyLayer(UMaterialInterface* Material)
{
	AActor* OwnerActor = GetOwner();
	if (OwnerActor == nullptr || Material == nullptr)
	{
		return;
	}

	TArray<UActorComponent*> ComponentsWithMaterials = OwnerActor->GetComponentsByClass(UPrimitiveComponent::StaticClass());
	for (UActorComponent* ActorComponent : ComponentsWithMaterials)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(ActorComponent);
		const int32 NumMaterials = PrimitiveComponent->GetNumMaterials();

		for (int32 i = 0; i < NumMaterials; i++)
		{
			PrimitiveComponent->SetMaterial(i, Material);
		}
	}
}

void UFPCMaterialSwapper::ApplyBaseLayer()
{
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor)
	{
		return;
	}

	TArray<UActorComponent*> ComponentsWithMaterials = OwnerActor->GetComponentsByClass(UPrimitiveComponent::StaticClass());
	for (UActorComponent* ActorComponent : ComponentsWithMaterials)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(ActorComponent);

		if (const auto MaterialsArrayPtr = BaseLayer.Find(PrimitiveComponent))
		{
			const int32 NumMaterials = MaterialsArrayPtr->Num();
			for (int i = 0; i < NumMaterials; i++)
			{
				PrimitiveComponent->SetMaterial(i, (*MaterialsArrayPtr)[i]);
			}
		}
	}
}
