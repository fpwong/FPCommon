// Fill out your copyright notice in the Description page of Project Settings.

#include "FPCHitboxHelper.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

AFPCHitbox::AFPCHitbox()
{
	bHitboxActive = false;
}

void AFPCHitbox::OnHitboxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ignore actors already hit
	if (ActorsHit.Contains(OtherActor))
		return;

	HitboxHelper->OnHitboxOverlap.Broadcast(OtherActor, this, HitboxHelper, SweepResult);
	ActorsHit.Add(OtherActor);
}

void AFPCHitbox::SetHitboxActive(bool bNewActive)
{
	if (bNewActive == bHitboxActive) return;

	if (PrimitiveComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hitbox not registered"));
		return;
	}

	if (bNewActive) // activate hitbox
	{
		TArray<AActor*> OverlappingActors;
		PrimitiveComponent->GetOverlappingActors(OverlappingActors);
		for (AActor* Actor : OverlappingActors)
		{
			OnHitboxOverlap(nullptr, Actor, nullptr, -1, false, FHitResult());
		}

		PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPCHitbox::OnHitboxOverlap);
	}
	else // deactivate hitbox
	{
		//PrimitiveComponent->bHiddenInGame = true;
		PrimitiveComponent->OnComponentBeginOverlap.RemoveDynamic(this, &AFPCHitbox::OnHitboxOverlap);
		ActorsHit.Empty();
	}

	bHitboxActive = bNewActive;
}

// Sets default values for this component's properties
UFPCHitboxHelper::UFPCHitboxHelper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UFPCHitboxHelper::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UFPCHitboxHelper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

AFPCHitbox* UFPCHitboxHelper::GetHitbox(int HitboxID)
{
	if (HitboxID >= Hitboxes.Num())
		return nullptr;

	return Hitboxes[HitboxID];
}

void UFPCHitboxHelper::RegisterHitbox(UPrimitiveComponent* Component, int HitboxID)
{
	const FTransform SpawnTransform(FRotator::ZeroRotator, FVector::ZeroVector);

	AActor* Actor = GetWorld()->SpawnActor(AFPCHitbox::StaticClass(), &SpawnTransform);
	AFPCHitbox* Hitbox = Cast<AFPCHitbox>(Actor);

	check(Hitbox != nullptr);

	Hitbox->HitboxHelper = this;
	Hitbox->PrimitiveComponent = Component;
	Hitbox->HitboxId = HitboxID;
	Hitboxes.Add(Hitbox);
}