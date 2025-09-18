#pragma once

#include "CoreMinimal.h"

#include "FPTopDownCameraPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS(Blueprintable)
class FPCOMMON_API AFPTopDownCameraPawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	FVector DesiredLocation;
	float DesiredArmLength;
	float DesiredOrthoWidth;

	UPROPERTY(EditDefaultsOnly)
	float bCanZoom = false;

	UPROPERTY(EditAnywhere)
	float ZoomInterpSpeed = 12.0f;

	UPROPERTY(EditAnywhere)
	float MovementInterpSpeed = 12.0f;

	UPROPERTY(EditAnywhere)
	float MinArmLength = 500;

	UPROPERTY(EditAnywhere)
	float MaxArmLength = 12000;

	UPROPERTY(EditAnywhere)
	float MinOrthoWidth = 512;

	UPROPERTY(EditAnywhere)
	float MaxOrthoWidth = 8192;

	UPROPERTY(EditAnywhere)
	float CameraSpeed = 1500;

	UFUNCTION(BlueprintCallable)
	void SetCameraLocation(const FVector& NewLocation);

	UFUNCTION(BlueprintCallable)
	void UpdateArmLength(float ZoomAxis);

	void MoveCamera(float DeltaTime, float ScreenX, float ScreenY);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void TeleportToNewLocation(FVector NewLocation, FRotator Rotation);

	virtual bool TeleportTo(const FVector& DestLocation, const FRotator& DestRotation, bool bIsATest, bool bNoCheck) override;

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaSeconds) override;
};
