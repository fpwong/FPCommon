// Fill out your copyright notice in the Description page of Project Settings.

#include "FPCBlueprintLibrary.h"

#include "CommonActivatableWidget.h"
#include "Animation/UMGSequencePlayer.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextWidgetTypes.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameSession.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

FAISenseAffiliationFilter UFPCBlueprintLibrary::MakeAffiliationFilter(const bool bDetectEnemies, const bool bDetectNeutrals, const bool bDetectFriendlies)
{
	FAISenseAffiliationFilter Filter;
	Filter.bDetectEnemies = bDetectEnemies;
	Filter.bDetectNeutrals = bDetectNeutrals;
	Filter.bDetectFriendlies = bDetectFriendlies;
	return Filter;
}

float UFPCBlueprintLibrary::GetAngleBetweenVectors(FVector A, FVector B)
{
	return FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(A, B)));
}

float UFPCBlueprintLibrary::GetDistanceBetweenActors(AActor* A, AActor* B)
{
	if (!A || !B)
	{
		return 0.0f;
	}

	const float CapsuleRadius = A->GetSimpleCollisionRadius() + B->GetSimpleCollisionRadius();
	const float Distance = (A->GetActorLocation() - B->GetActorLocation()).Size2D() - CapsuleRadius;
	return Distance;
}

void UFPCBlueprintLibrary::SetActorLocationOnGround(AActor* Actor, const FVector& NewLocation)
{
	if (!Actor)
	{
		return;
	}
	
	UWorld* World = Actor->GetWorld();
	TArray<FHitResult> OutHits;
	const FVector LineStart = NewLocation + FVector(0, 0, 1000);
	const FVector LineEnd = NewLocation - FVector(0, 0, 1000);
	FCollisionObjectQueryParams ObjectParams(FCollisionObjectQueryParams::InitType::AllStaticObjects);
	World->LineTraceMultiByObjectType(OutHits, LineStart, LineEnd, ObjectParams);

	for (const FHitResult& Hit : OutHits)
	{
		float ActorZ = NewLocation.Z;

		if (Hit.IsValidBlockingHit())
		{
			if (UCapsuleComponent* Capsule = Actor->FindComponentByClass<UCapsuleComponent>())
			{
				ActorZ = Hit.Location.Z + Capsule->GetScaledCapsuleHalfHeight();
			}
			else
			{
				FVector UnusedOrigin;
				FVector ActorBoxExtent;
				Actor->GetActorBounds(true, UnusedOrigin, ActorBoxExtent);
				ActorZ = Hit.Location.Z + ActorBoxExtent.Z;
			}
		}

		Actor->SetActorLocation(FVector(NewLocation.X, NewLocation.Y, ActorZ));
		break;
	}
}

FBox UFPCBlueprintLibrary::GetBoxIntersection(FBox A, FBox B)
{
	const FVector Min(
		FMath::Max(A.Min.X, B.Min.X),
		FMath::Max(A.Min.Y, B.Min.Y),
		FMath::Max(A.Min.Z, B.Min.Z));

	const FVector Max(
		FMath::Min(A.Max.X, B.Max.X),
		FMath::Min(A.Max.Y, B.Max.Y),
		FMath::Min(A.Max.Z, B.Max.Z));

	return FBox(Min, Max);
}

bool UFPCBlueprintLibrary::ProjectLocationOnGround(UObject* WorldContextObject, FVector Location, FVector& GroundLocation, double TraceDistance)
{
	const FVector LineStart = Location + FVector(0, 0, TraceDistance);
	const FVector LineEnd = Location - FVector(0, 0, TraceDistance);
	FCollisionObjectQueryParams ObjectParams(FCollisionObjectQueryParams::InitType::AllStaticObjects);

	FHitResult OutHit;
	if (WorldContextObject->GetWorld()->LineTraceSingleByObjectType(OutHit, LineStart, LineEnd, ObjectParams))
	{
		GroundLocation = OutHit.Location;
		return true; 
	}

	return false;
}

AActor* UFPCBlueprintLibrary::GetClosestActor(const FVector& Location, const TArray<AActor*>& Actors)
{
	TArray<AActor*> ActorsCopy = Actors;
	
	if (!Actors.Num())
	{
		return nullptr;
	}

	const auto Pred = [&Location](const AActor& ActorA, const AActor& ActorB)
	{
		const float DistA = FVector::DistSquared2D(ActorA.GetActorLocation(), Location);
		const float DistB = FVector::DistSquared2D(ActorB.GetActorLocation(), Location);
		return DistA < DistB;
	};

	ActorsCopy.Sort(Pred);
	return ActorsCopy[0];
}

void UFPCBlueprintLibrary::SortActorsByDistance(TArray<AActor*>& Actors, const FVector& Location, bool bClosest)
{
	const auto Pred = [&Location, &bClosest](const AActor& ActorA, const AActor& ActorB)
	{
		const float DistA = FVector::DistSquared2D(ActorA.GetActorLocation(), Location);
		const float DistB = FVector::DistSquared2D(ActorB.GetActorLocation(), Location);
		return bClosest ? (DistA < DistB) : (DistA > DistB);
	};

	Actors.Sort(Pred);
}

TArray<AActor*> UFPCBlueprintLibrary::GetActorsSlice(const TArray<AActor*>& Actors, int Start, int End)
{
	TArray<AActor*> OutActors;

	for (int i = Start; i < End; ++i)
	{
		if (Actors.IsValidIndex(i))
		{
			OutActors.Add(Actors[i]);
		}
		else
		{
			break;
		}
	}

	return OutActors;
}

AGameSession* UFPCBlueprintLibrary::GetGameSession(AGameModeBase* GameMode)
{
	return GameMode ? GameMode->GameSession : nullptr;
}

bool UFPCBlueprintLibrary::KickPlayer(AGameSession* GameSession, APlayerController* KickedPlayer, const FText& KickReason)
{
	return GameSession ? GameSession->KickPlayer(KickedPlayer, KickReason) : false;
}

bool UFPCBlueprintLibrary::BanPlayer(AGameSession* GameSession, APlayerController* BannedPlayer, const FText& BanReason)
{
	return GameSession ? GameSession->BanPlayer(BannedPlayer, BanReason) : false;
}

AActor* UFPCBlueprintLibrary::GetViewTarget(APlayerCameraManager* PlayerCameraManager)
{
	return PlayerCameraManager->GetViewTarget();
}

float UFPCBlueprintLibrary::GetCurrentTime(UUMGSequencePlayer* SequencePlayer)
{
	return SequencePlayer ? SequencePlayer->GetCurrentTime().AsSeconds() : 0.0f;
}

void UFPCBlueprintLibrary::RegisterComponentWithWorld(UObject* WorldContextObject, UActorComponent* ActorComponent)
{
	check(WorldContextObject)
	ActorComponent->RegisterComponentWithWorld(WorldContextObject->GetWorld());
}

UObject* UFPCBlueprintLibrary::GetClassDefaultObject(TSubclassOf<UObject> Class)
{
	if (!Class) return nullptr;
	return Class->GetDefaultObject();
}

void UFPCBlueprintLibrary::FPBlueprintBreakpoint()
{
	check(false);
	UE_LOG(LogTemp, Warning, TEXT("Hit breakpoint..."));
}

int32 UFPCBlueprintLibrary::GetNumWidgets(UCommonActivatableWidgetContainerBase* WidgetContainer)
{
	return WidgetContainer ? WidgetContainer->GetNumWidgets() : 0;
}

void UFPCBlueprintLibrary::ServerTravel(UObject* WorldContextObject, TSoftObjectPtr<UWorld> Level, bool bAbsolute)
{
	if (WorldContextObject && !Level.IsNull())
	{
		const FString LevelName = FPackageName::ObjectPathToPackageName(Level.ToString());
		WorldContextObject->GetWorld()->ServerTravel(LevelName, bAbsolute);
	}
}

APlayerController* UFPCBlueprintLibrary::GetPrimaryPlayerController(UObject* WorldContextObject)
{
	if (WorldContextObject)
	{
		if (auto World = WorldContextObject->GetWorld())
		{
			if (auto Inst = World->GetGameInstance())
			{
				return Inst->GetPrimaryPlayerController();
			}
		}
	}

	return nullptr;
}
