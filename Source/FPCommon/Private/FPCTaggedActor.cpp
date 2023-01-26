// Fill out your copyright notice in the Description page of Project Settings.

#include "FPCTaggedActor.h"

#include "FPCTaggedObjectSubsystem.h"

// Sets default values
AFPCTaggedActor::AFPCTaggedActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AFPCTaggedActor::BeginPlay()
{
	Super::BeginPlay();

	if (UFPCTaggedObjectSubsystem* TaggedObjectSubsystem = GetWorld()->GetSubsystem<UFPCTaggedObjectSubsystem>())
	{
		TaggedObjectSubsystem->AddObject(this, IdentityTag);
	}
}

void AFPCTaggedActor::Destroyed()
{
	Super::Destroyed();

	if (UFPCTaggedObjectSubsystem* TaggedObjectSubsystem = GetWorld()->GetSubsystem<UFPCTaggedObjectSubsystem>())
	{
		TaggedObjectSubsystem->RemoveObject(this, IdentityTag);
	}
}

