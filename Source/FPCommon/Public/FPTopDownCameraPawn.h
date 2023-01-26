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
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UCameraComponent* Camera;
	
	FVector DesiredLocation;
	float DesiredArmLength;

	UPROPERTY(EditDefaultsOnly)
	float bCanZoom = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float ZoomInterpSpeed = 12.0f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float MovementInterpSpeed = 12.0f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float MinArmLength = 500;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float MaxArmLength = 12000;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float CameraSpeed = 1500;

	UFUNCTION(BlueprintCallable)
	void SetCameraLocation(const FVector& NewLocation);

	void UpdateArmLength(float ZoomAxis);

	void MoveCamera(float DeltaTime, float ScreenX, float ScreenY);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void TeleportToNewLocation(FVector NewLocation, FRotator Rotation);

	virtual bool TeleportTo(const FVector& DestLocation, const FRotator& DestRotation, bool bIsATest, bool bNoCheck) override;
	
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaSeconds) override;
};