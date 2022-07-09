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

	TArray<UPrimitiveComponent*> ComponentsWithMaterials;
	OwnerActor->GetComponents<UPrimitiveComponent>(ComponentsWithMaterials);
	for (UPrimitiveComponent* PrimitiveComponent : ComponentsWithMaterials)
	{
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

int32 UFPCMaterialSwapper::AddLayer(UMaterialInterface* Material)
{
	if (Material == nullptr)
	{
		return -1;
	}

	Layers.Push(Material);
	ApplyLayer(Material);

	return Layers.Num() - 1;
}

void UFPCMaterialSwapper::RemoveLayer(int32 Index)
{
	if (Index < 0 || Layers.Num() == 0)
	{
		return;
	}

	if (!Layers.IsValidIndex(Index))
	{
		UE_LOG(LogTemp, Error, TEXT("Index is not valid!"));
		return;
	}

	Layers[Index] = nullptr;

	bool bChangedTopLayer = false;
	while (Layers.Num() > 0 && Layers.Top() == nullptr)
	{
		Layers.Pop();
		bChangedTopLayer = true;
	}

	if (bChangedTopLayer)
	{
		if (Layers.Num() > 0)
		{
			ApplyLayer(Layers.Top());
		}
		else
		{
			ApplyBaseLayer();
		}
	}
}

void UFPCMaterialSwapper::ApplyLayer(UMaterialInterface* Material)
{
	AActor* OwnerActor = GetOwner();
	if (OwnerActor == nullptr || Material == nullptr)
	{
		return;
	}

	TArray<UPrimitiveComponent*> PrimitiveComponents;
	OwnerActor->GetComponents<UPrimitiveComponent>(PrimitiveComponents);
	
	for (UPrimitiveComponent* PrimitiveComponent : PrimitiveComponents)
	{
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

	TArray<UPrimitiveComponent*> PrimitiveComponents;
	OwnerActor->GetComponents<UPrimitiveComponent>(PrimitiveComponents);
	
	for (UPrimitiveComponent* PrimitiveComponent : PrimitiveComponents)
	{
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
