// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "FPCHitboxHelper.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FHitboxHelperDelegate, AActor*, Actor, AFPCHitbox*, Hitbox, UFPCHitboxHelper*, HitboxHelper, const FHitResult&, Hit);

UCLASS()
class FPCOMMON_API AFPCHitbox : public AActor
{
	GENERATED_BODY()

public:
	TArray<AActor*> ActorsHit;
	class UFPCHitboxHelper* HitboxHelper;
	int HitboxId;
	bool bHitboxActive;

	UPrimitiveComponent* PrimitiveComponent;

public:
	AFPCHitbox();

	UFUNCTION()
	void OnHitboxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void SetHitboxActive(bool bNewActive = true);
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPCOMMON_API UFPCHitboxHelper : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FHitboxHelperDelegate OnHitboxOverlap;

	TArray<AFPCHitbox*> Hitboxes;

	// Sets default values for this component's properties
	UFPCHitboxHelper();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	AFPCHitbox* GetHitbox(int HitboxID);

	UFUNCTION(BlueprintCallable)
	void RegisterHitbox(class UPrimitiveComponent* Hitbox, int HitboxID);
};
