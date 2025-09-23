#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FPCSimpleAnimInstance.generated.h"

UINTERFACE()
class UFPCAnimInstanceInterface : public UInterface
{
	GENERATED_BODY()
};

class FPCOMMON_API IFPCAnimInstanceInterface
{
	GENERATED_BODY()

public:
	virtual UBlendSpace* GetAnimInstBlendSpace() = 0;
};


UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType, meta = (BlueprintThreadSafe), Within = SkeletalMeshComponent)
class FPCOMMON_API UFPCSimpleAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float Speed = 0;

	UPROPERTY()
	APawn* OwningPawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBlendSpace* PawnBlendSpace;

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
