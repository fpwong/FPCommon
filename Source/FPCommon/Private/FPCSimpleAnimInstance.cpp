#include "FPCSimpleAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

void UFPCSimpleAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningPawn = TryGetPawnOwner();
}

void UFPCSimpleAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!OwningPawn)
	{
		return;
	}


	bool bIsInAir = OwningPawn->GetMovementComponent() && !OwningPawn->GetMovementComponent()->IsMovingOnGround();

	float TargetSpeed = bIsInAir ? 0.0f : OwningPawn->GetVelocity().Size2D();

	Speed = FMath::FInterpTo(Speed, TargetSpeed, DeltaSeconds, 10.0f);

	// Speed = FMath::FInterpTo(Speed, OwningPawn->GetVelocity().Size2D(), DeltaSeconds, 8.0f);

	// float NewSpeed = FMath::FInterpConstantTo(Speed, OwningPawn->GetVelocity().Size2D(), DeltaSeconds, 10.0f);
	// UE_LOG(LogTemp, Warning, TEXT("%f | %f | %f | %f"), Speed, NewSpeed, OwningPawn->GetVelocity().Size2D(), DeltaSeconds);
	// UE_LOG(LogTemp, Warning, TEXT("%f"), Speed);

	// Speed = FMath::FInterpConstantTo(Speed, OwningPawn->GetVelocity().Size2D(), DeltaSeconds, 1200.0f);
	// Speed = NewSpeed;
	// Speed =  OwningPawn->GetVelocity().Size2D();
}