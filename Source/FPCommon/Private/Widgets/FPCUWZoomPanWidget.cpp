// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/FPCUWZoomPanWidget.h"

#include "Components/CanvasPanel.h"

FVector2D UFPCUWZoomPanWidget::ClampSides(const FGeometry& InGeometry, FVector2D ClampTo)
{
	const FVector2D GeometrySize = InGeometry.GetLocalSize();
	const FVector2D CanvasBounds = InnerCanvas->GetDesiredSize() * InnerCanvas->GetRenderTransform().Scale;

	const FVector2D Limit = (GeometrySize - CanvasBounds) * 0.5f;
	const FVector2D MinLimit = -1.0 * Limit;
	// UE_LOG(LogTemp, Warning, TEXT("LIMIT (%s) (%s)"), *MinLimit.ToString(), *Limit.ToString());

	return FVector2D(
		FMath::Clamp(ClampTo.X, MinLimit.X, Limit.X),
		FMath::Clamp(ClampTo.Y, MinLimit.Y, Limit.Y));
}

FReply UFPCUWZoomPanWidget::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	float WheelDelta = InMouseEvent.GetWheelDelta();

	if (WheelDelta != 0.0)
	{
		bool bIsZoomingIn = InMouseEvent.GetWheelDelta() > 0.0f;
		float ZoomFactor = 0.8f;
		float ZoomAmount = bIsZoomingIn ?  (1.0f / ZoomFactor) : ZoomFactor;
		float FinalZoomDelta = ZoomAmount - 1.0f;

		const auto& CurrentScale = InnerCanvas->GetRenderTransform().Scale;
		InnerCanvas->SetRenderScale(CurrentScale * ZoomAmount);

		FVector2D InnerTranslation = InnerCanvas->GetRenderTransform().Translation;

		FVector2D HalfSize = InGeometry.GetLocalSize() * 0.5;

		FVector2D CursorLocalSpace = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

		FVector2D CursorCentered = (CursorLocalSpace - HalfSize);

		const FVector2D& Delta = (CursorCentered - InnerTranslation) * FinalZoomDelta;

		FVector2D NewLocation = InnerTranslation - Delta;

		FVector2D ClampedLocation = ClampSides(InGeometry, NewLocation);

		// UE_LOG(LogTemp, Warning, TEXT("%f %s (%s) (%s)"), ZoomAmount, *Offset.ToString(), *NewLocation.ToString(), *InnerCanvas->GetRenderTransform().Translation.ToString());

		InnerCanvas->SetRenderTranslation(ClampedLocation);

		return FReply::Handled();
	}

	return Super::NativeOnMouseWheel(InGeometry, InMouseEvent);
}

FReply UFPCUWZoomPanWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	const FVector2D& Delta = InMouseEvent.GetCursorDelta();

	if (bIsPanning)
	{
		const FVector2D NewLocation = InnerCanvas->GetRenderTransform().Translation + Delta;
		const FVector2D ClampedLocation = ClampSides(InGeometry, NewLocation);
		InnerCanvas->SetRenderTranslation(ClampedLocation);

		return FReply::Handled();
	}

	return Super::NativeOnMouseMove(InGeometry, InMouseEvent);
}

FReply UFPCUWZoomPanWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		bIsPanning = true;
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

FReply UFPCUWZoomPanWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		bIsPanning = false;
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

void UFPCUWZoomPanWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	bIsPanning = false;
	Super::NativeOnMouseLeave(InMouseEvent);
}
