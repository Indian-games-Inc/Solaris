// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TerminalWidget.generated.h"


UCLASS()
class CRYPTRAIDER_API UTerminalWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void CursorMoveUpdate(const float& Alpha);
	
protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UNamedSlot* MouseCursor;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* CursorImage;

private:
	UPROPERTY(EditAnywhere, Category="Cursor", DisplayName= "Interp Speed", meta = (AllowPrivateAccess = "true"))
	float CursorInterpSpeed = 10.f;
};
