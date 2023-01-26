// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPCIdentityInterface.h"
#include "GameFramework/Actor.h"
#include "FPCTaggedActor.generated.h"

UCLASS()
class FPCOMMON_API AFPCTaggedActor
	: public AActor
	, public IFPCIdentityInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPCTaggedActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

public:
	UPROPERTY(EditAnywhere)
	FGameplayTag IdentityTag;

	virtual FGameplayTag GetIdentityTag_Implementation() override { return IdentityTag; }
};
