#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FPCSimpleAnimInstance.generated.h"

UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType, meta = (BlueprintThreadSafe), Within = SkeletalMeshComponent)
class FPCOMMON_API UFPCSimpleAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float Speed = 0;
	
	APawn* OwningPawn;
	
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
