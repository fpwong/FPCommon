// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Perception/AISense.h"
// #include "Engine/"
#include "FPCBlueprintLibrary.generated.h"

class UCommonActivatableWidgetContainerBase;
class AGameSession;

UCLASS()
class FPCOMMON_API UFPCBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Affiliation")
	static FAISenseAffiliationFilter MakeAffiliationFilter(bool bDetectEnemies, bool bDetectNeutrals, bool bDetectFriendlies);

	UFUNCTION(BlueprintPure, Category = "Math")
	static float GetAngleBetweenVectors(FVector A, FVector B);

	UFUNCTION(BlueprintCallable, Category = "Misc")
	static float GetDistanceBetweenActors(AActor* A, AActor* B);

	UFUNCTION(BlueprintCallable, Category = "Misc")
	static void SetActorLocationOnGround(AActor* Actor, const FVector& NewLocation);

	UFUNCTION(BlueprintCallable, Category = "Misc", meta=(WorldContext="WorldContextObject", ExpandBoolAsExecs ="ReturnValue"))
	static bool ProjectLocationOnGround(UObject* WorldContextObject, FVector Location, FVector& GroundLocation, double TraceDistance = 2000);

	UFUNCTION(BlueprintCallable, Category = "Misc")
    static AActor* GetClosestActor(const FVector& Location, const TArray<AActor*>& Actors);

	UFUNCTION(BlueprintCallable, Category = "Misc")
	static void SortActorsByDistance(UPARAM(ref) TArray<AActor*>& Actors, const FVector& Location, bool bClosest = true);

	UFUNCTION(BlueprintCallable, Category = "Misc")
	static TArray<AActor*> GetActorsSlice(const TArray<AActor*>& Actors, int Start, int End);

	UFUNCTION(BlueprintPure, Category = "GameSession")
    static AGameSession* GetGameSession(AGameModeBase* GameMode);

	UFUNCTION(BlueprintCallable, Category = "GameSession")
	static bool KickPlayer(AGameSession* GameSession, APlayerController* KickedPlayer, const FText& KickReason);

	UFUNCTION(BlueprintCallable, Category = "GameSession")
	static bool BanPlayer(AGameSession* GameSession, APlayerController* BannedPlayer, const FText& BanReason);

	UFUNCTION(BlueprintCallable, Category = "Misc")
	static AActor* GetViewTarget(APlayerCameraManager* PlayerCameraManager);

	UFUNCTION(BlueprintCallable, Category = "Misc")
	static float GetCurrentTime(UUMGSequencePlayer* SequencePlayer);

	UFUNCTION(BlueprintCallable, Category = "Misc", meta = (WorldContext = "WorldContextObject"))
	static void RegisterComponentWithWorld(UObject* WorldContextObject, UActorComponent* ActorComponent);

	UFUNCTION(BlueprintCallable, Category = "Misc", meta = (DeterminesOutputType = "Class"))
	static UObject* GetClassDefaultObject(TSubclassOf<UObject> Class);

	UFUNCTION(BlueprintCallable, Category = "Misc")
	static void FPBlueprintBreakpoint();

	UFUNCTION(BlueprintCallable, Category = "CommonUI", BlueprintPure)
	static int32 GetNumWidgets(UCommonActivatableWidgetContainerBase* WidgetContainer);

	UFUNCTION(BlueprintCallable, Category = "Misc", meta=(WorldContext="WorldContextObject"))
	static void ServerTravel(UObject* WorldContextObject, TSoftObjectPtr<UWorld> Level, bool bAbsolute = false);
};
