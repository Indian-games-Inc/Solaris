// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/ScannerWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/NamedSlot.h"


void UScannerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ScanPointExtinctionInterpSpeed = 5.f;

	SetPointPosition({ 0.f, 0.f });
	PointImage->SetOpacity(0.f);

	DrawSize = { 500.f, 500.f };
}

void UScannerWidget::ScanUpdate(const FVector2D& ScanPointPosition)
{
	SetPointPosition(ScanPointPosition);
}

void UScannerWidget::SetDrawSize(const FVector2D& Size)
{
	DrawSize = Size;
}

void UScannerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdatePointOpacity(InDeltaTime);
}

void UScannerWidget::SetPointPosition(const FVector2D& NewPosition)
{
	if (auto* PositionPointSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(PositionPoint);
		IsValid(PositionPointSlot))
	{
		PositionPointSlot->SetPosition(CalculateRelativePosition(NewPosition));
	}

	PointImage->SetOpacity(1.0);
}

void UScannerWidget::UpdatePointOpacity(float DeltaTime)
{
	const float Opacity = FMath::FInterpTo(PointImage->GetColorAndOpacity().A, 0.f,
	                                       DeltaTime,
	                                       ScanPointExtinctionInterpSpeed);

	PointImage->SetOpacity(Opacity);
}

FVector2D UScannerWidget::CalculateRelativePosition(const FVector2D& NewPosition) const
{
	if (not IsValid(Scanner))
		return {};

	const FVector2D ScannerSize = GetScannerSize();
	const FVector2D InRange { -1.f, 1.f };

	const FVector2D CoordBounds {
		ScannerSize.X / 2.f,
		ScannerSize.Y / 2.f
	};

	const FVector2D OutRangeX { -CoordBounds.X, CoordBounds.X };
	const FVector2D OutRangeY { -CoordBounds.Y, CoordBounds.Y };

	FVector2D Position {
		FMath::GetMappedRangeValueClamped(InRange, OutRangeX, NewPosition.X),
		FMath::GetMappedRangeValueClamped(InRange, OutRangeY, NewPosition.Y)
	};

	Position.Y = -Position.Y;

	return Position;
}

FVector2D UScannerWidget::GetScannerSize() const
{
	FVector2D ScannerSize = DrawSize;

	if (const auto* ScannerSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Scanner);
		IsValid(ScannerSlot))
	{
		const FMargin ScannerMargin = ScannerSlot->GetOffsets();

		ScannerSize.X -= ScannerMargin.Left + ScannerMargin.Right;
		ScannerSize.Y -= ScannerMargin.Top + ScannerMargin.Bottom;
	}

	if (const auto* PositionPointSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(PositionPoint);
		IsValid(PositionPointSlot))
	{
		const FVector2D PointImageSize = PositionPointSlot->GetSize();

		ScannerSize.X -= PointImageSize.Y;
		ScannerSize.Y -= PointImageSize.Y;
	}

	return ScannerSize;
}
