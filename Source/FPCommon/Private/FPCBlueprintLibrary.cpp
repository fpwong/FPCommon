// Fill out your copyright notice in the Description page of Project Settings.

#include "FPCBlueprintLibrary.h"

#include "Animation/UMGSequencePlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameSession.h"

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