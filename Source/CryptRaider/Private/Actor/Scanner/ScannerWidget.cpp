// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Scanner/ScannerWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/NamedSlot.h"


void UScannerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ScanPointExtinctionInterpSpeed = 2.f;

	SetPointPosition({ 0.f, 0.f });
}

void UScannerWidget::ScanUpdate(const FVector2D& ScanPointPosition)
{
	// TODO Add image position update

	SetPointPosition(ScanPointPosition);
}

void UScannerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	// UpdatePointOpacity(InDeltaTime);
}

void UScannerWidget::SetPointPosition(const FVector2D& NewPosition)
{
	if (not IsValid(Scanner))
		return;

	FVector2D Position = FVector2D::ZeroVector;

	const auto* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Canvas);

	if (const auto* ScannerSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Scanner);
		IsValid(ScannerSlot))
	{
		const auto CanvasSize = Canvas->GetDesiredSize();
		const auto ScannerMargin = ScannerSlot->GetOffsets();

		// const FVector2D ScannerSize = {
		// 	CanvasSize.X - ScannerMargin.Left + ScannerMargin.Right,
		// 	CanvasSize.Y - ScannerMargin.Top + ScannerMargin.Bottom
		// };

		const FVector2D ScannerSize = { 250.f, 250.f };

		const FVector2D InRange { -1.f, 1.f };

		const float ScannerHalfWidth = ScannerSize.X / 2.f;
		const float ScannerHalfHeight = ScannerSize.Y / 2.f;

		const FVector2D OutRangeX { -ScannerHalfWidth, ScannerHalfWidth };
		const FVector2D OutRangeY { -ScannerHalfHeight, ScannerHalfHeight };

		Position.X = FMath::GetMappedRangeValueClamped(InRange, OutRangeX, NewPosition.X);
		Position.Y = FMath::GetMappedRangeValueClamped(InRange, OutRangeY, NewPosition.Y);

		Position.Y = -Position.Y;
	}

	if (auto* PositionPointSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(PositionPoint);
		IsValid(PositionPointSlot))
	{
		PositionPointSlot->SetPosition(Position);
	}
}

void UScannerWidget::UpdatePointOpacity(float DeltaTime)
{
	auto LinearColor = PointImage->GetColorAndOpacity();

	LinearColor.A = FMath::FInterpTo(LinearColor.A, 0.f, DeltaTime, ScanPointExtinctionInterpSpeed);

	PointImage->SetColorAndOpacity(LinearColor);
}
