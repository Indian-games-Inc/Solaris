// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/TerminalWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/NamedSlot.h"
#include "Components/WidgetInteractionComponent.h"
#include "GameFramework/Character.h"


void UTerminalWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	CursorMoveUpdate(InDeltaTime);
}

void UTerminalWidget::CursorMoveUpdate(const float& DeltaTime)
{
	const ACharacter* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();
	
	if (const auto* WidgetInteraction = PlayerCharacter->FindComponentByClass<UWidgetInteractionComponent>())
	{
		if (WidgetInteraction->IsOverHitTestVisibleWidget())
		{
			if (auto* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(MouseCursor); IsValid(CanvasSlot))
			{
				const auto CurrentPosition = CanvasSlot->GetPosition();
				const auto TargetPosition = WidgetInteraction->Get2DHitLocation();

				const auto NewPosition = FMath::Vector2DInterpTo(
					CurrentPosition,
					TargetPosition,
					DeltaTime, CursorInterpSpeed
				);
				CanvasSlot->SetPosition(NewPosition);
			}
		}
	}
}
