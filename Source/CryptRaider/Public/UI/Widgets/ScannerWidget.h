// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScannerWidget.generated.h"


UCLASS()
class CRYPTRAIDER_API UScannerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ScanUpdate(const FVector2D& ScanPointPosition);

	void SetDrawSize(const FVector2D& Size);
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void SetPointPosition(const FVector2D& NewPosition);

	void UpdatePointOpacity(float DeltaTime);

	FVector2D CalculateRelativePosition(const FVector2D& NewPosition) const;

	FVector2D GetScannerSize() const;

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> Canvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> Scanner;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UNamedSlot> PositionPoint;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> PointImage;

private:
	UPROPERTY(EditAnywhere)
	float ScanPointExtinctionInterpSpeed;

	FVector2D DrawSize;
};
