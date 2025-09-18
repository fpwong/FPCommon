// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPTopDownCameraPawn.h"


#include "DrawDebugHelpers.h"
// #include "FPTopDownPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AFPTopDownCameraPawn::AFPTopDownCameraPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	SetRootComponent(DefaultSceneRoot);

	SpringArm = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	// SpringArm->AttachToComponent(DefaultSceneRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SpringArm->SetRelativeRotation_Direct(FRotator::MakeFromEuler(FVector(0.0f, -60.0f, 0.0f)));
	SpringArm->TargetArmLength = 5000.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Camera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->FieldOfView = 30.0f;

	PrimaryActorTick.bCanEverTick = true;
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	SetReplicates(true);
	AActor::SetReplicateMovement(true);
	SetNetUpdateFrequency(60.0f);
	NetPriority = 2.0f;

	ZoomInterpSpeed = 8.0f;
	MovementInterpSpeed = 18.0f;
}

void AFPTopDownCameraPawn::SetCameraLocation(const FVector& NewLocation)
{
	SetActorLocation(NewLocation);
	DesiredLocation = NewLocation;
}

void AFPTopDownCameraPawn::UpdateArmLength(const float ZoomAxis)
{
	if (bCanZoom)
	{
		float ZoomAmount = FMath::Pow(1.05f, -1 * ZoomAxis);
		const float NewArmLength = DesiredArmLength * ZoomAmount;
		DesiredArmLength = FMath::Clamp(NewArmLength, MinArmLength, MaxArmLength);

		const float NewWidth = DesiredOrthoWidth * ZoomAmount;
		DesiredOrthoWidth = FMath::Clamp(NewWidth, MinOrthoWidth, MaxOrthoWidth);
	}
}

void AFPTopDownCameraPawn::MoveCamera(float DeltaTime, float ScreenX, float ScreenY)
{
	const FVector CameraForward = Camera->GetForwardVector();
	FVector AdjustedForward(CameraForward.X, CameraForward.Y, 0.0f);
	AdjustedForward.Normalize();

	const FVector CameraRight = Camera->GetRightVector();

	FVector2D NormalizedMovement = FVector2D(ScreenX, ScreenY).GetSafeNormal();

	const FVector MoveRight = CameraRight * NormalizedMovement.X;
	const FVector MoveForward = AdjustedForward * NormalizedMovement.Y;

	const float DistanceScale = SpringArm->TargetArmLength / 3000.0f;
	float Speed = DeltaTime * DistanceScale * CameraSpeed;

	FVector DeltaX = MoveRight;
	FVector DeltaY = MoveForward;

	FVector Delta = DeltaX + DeltaY;
	Delta.Normalize();
	Delta *= Speed;

	DesiredLocation += Delta; // (DeltaX + DeltaY);

	// AActor* Focus = nullptr;
 //    int32 ViewportX;
 //    int32 ViewportY;
 //    
 //    if (AFPTopDownPlayerController* PC = Cast<AFPTopDownPlayerController>(GetWorld()->GetFirstPlayerController()))
 //    {
 //    	Focus = PC->GetFocusedSelection();
 //    	PC->GetViewpoFPTopDownize(ViewportX, ViewportY);
 //    }
 //
 //    if (Focus)
 //    {
 //    	FVector2D Center;
 //    	UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), Focus->GetActorLocation(), Center);
 //    
 //    	const float PaddingX = 0.1;
 //    	const bool bValidX = Center.X >= ViewportX * PaddingX && Center.X <= ViewportX * (1 - PaddingX);
 //    	if (!bValidX)
 //    	{
 //    		DeltaRight = FVector::ZeroVector;
 //    		// DesiredLocation.X = NewLocation.X;
 //    	}
 //    
 //    	const float PaddingY = 0.1;
 //    
 //    	const bool bValidY = Center.Y >= ViewportY * PaddingY && Center.Y <= ViewportY * (1 - PaddingY);
 //    	if (!bValidY)
 //    	{
 //    		NewLocation.Y = GetActorLocation().Y;
 //    		// DesiredLocation.Y = NewLocation.Y;
 //    	}
 //    }

	// DesiredLocation += MovementAxis * DistanceScale * CameraSpeed * DeltaTime;
}

bool AFPTopDownCameraPawn::TeleportTo(const FVector& DestLocation, const FRotator& DestRotation, bool bIsATest, bool bNoCheck)
{
	DesiredLocation = DestLocation;
	return Super::TeleportTo(DestLocation, DestRotation, bIsATest, bNoCheck);
}

void AFPTopDownCameraPawn::OnConstruction(const FTransform& Transform)
{
	DesiredLocation = Transform.GetLocation();
	DesiredArmLength = SpringArm->TargetArmLength;
	DesiredOrthoWidth = Camera->OrthoWidth;
}

void AFPTopDownCameraPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// AActor* Focus = nullptr;
	// int32 ViewportX;
	// int32 ViewportY;
	//
	// if (AFPTopDownPlayerController* PC = Cast<AFPTopDownPlayerController>(GetWorld()->GetFirstPlayerController()))
	// {
	// 	Focus = PC->GetFocusedSelection();
	// 	PC->GetViewpoFPTopDownize(ViewportX, ViewportY);
	// }
	//
	// if (Focus)
	// {
	// 	FVector2D Center;
	// 	UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), Focus->GetActorLocation(), Center);
	//
	// 	const float PaddingX = 0.1;
	// 	const bool bValidX = Center.X >= ViewportX * PaddingX && Center.X <= ViewportX * (1 - PaddingX);
	// 	// if (!bValidX)
	// 	// {
	// 	// 	DesiredLocation.X = Focus->GetActorLocation().X;
	// 	// }
	// 	// else
	// 	// {
	// 	// 	DesiredLocation.X = GetActorLocation().X;
	// 	// }
	// 	
	// 	const float PaddingY = 0.1;
	//
	// 	const bool bValidY = Center.Y >= ViewportY * PaddingY && Center.Y <= ViewportY * (1 - PaddingY);
	// 	// if (!bValidY)
	// 	// {
	// 	// 	DesiredLocation.Y = Focus->GetActorLocation().Y;
	// 	// }
	// 	// else
	// 	// {
	// 	// 	DesiredLocation.Y = GetActorLocation().Y;
	// 	// }
	//
	// 	if (!bValidX || !bValidY)
	// 	{
	// 		DesiredLocation = Focus->GetActorLocation();
	// 	}
	// 	else
	// 	{
	// 		DesiredLocation = GetActorLocation();
	// 	}
	// }
	//
	// const FVector NewLocation = FMath::VInterpTo(GetActorLocation(), DesiredLocation, DeltaSeconds, MovementInterpSpeed);
	// SetActorLocation(NewLocation);

	FVector NewLocation = FMath::VInterpTo(GetActorLocation(), DesiredLocation, DeltaSeconds, MovementInterpSpeed);
	SetActorLocation(NewLocation);

	const float NewArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, DesiredArmLength, DeltaSeconds, ZoomInterpSpeed);
	SpringArm->TargetArmLength = NewArmLength;

	const float NewWidth = FMath::FInterpTo(Camera->OrthoWidth, DesiredOrthoWidth, DeltaSeconds, ZoomInterpSpeed);
	Camera->OrthoWidth = NewWidth;
}
