// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/Door/DoorPinLock.h"

#include "Camera/CameraComponent.h"
#include "Components/PointLightComponent.h"

#include "Actor/Door/Door.h"
#include "Player/BaseCharacter.h"

ADoorPinLock::ADoorPinLock()
{
	CloseUpCamera = CreateDefaultSubobject<UCameraComponent>("CloseUpCamera");
	CloseUpCamera->SetupAttachment(RootComponent);
	CursorLight = CreateDefaultSubobject<UPointLightComponent>("CursorLight");
	CursorLight->SetupAttachment(RootComponent);

	Screen = CreateDefaultSubobject<UWidgetComponent>("Screen");
	Screen->SetupAttachment(RootComponent);
	Screen->SetVisibility(true);
}

FString ADoorPinLock::HintMessage() const
{
	if (!Door->IsClosed())
	{
		return "";
	}
	return "Insert code";
}

void ADoorPinLock::Interact()
{
	if (Status() != EPinLockStatus::OPEN)
	{
		const auto BaseCharacter = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		BaseCharacter->SetPinLock(BaseCharacter->IsInPinLock() ? nullptr : this);
	}
}

bool ADoorPinLock::IsActive() const
{
	return Status() != EPinLockStatus::OPEN;
}

void ADoorPinLock::HandleButtonPress(const FString& BoneName)
{
	if (BoneName.Equals("enter"))
	{
		EnterCode();
	}
	else if (BoneName.Equals("del"))
	{
		if (!CodeBuffer.IsEmpty())
		{
			CodeBuffer.RemoveAt(CodeBuffer.Len() - 1, 1);
		}
	}
	else if (BoneName.IsNumeric())
	{
		if (CodeBuffer.Len() < BufferSize)
		{
			UE_LOG(LogTemp, Warning, TEXT("Buffer len: %d"), CodeBuffer.Len());
			CodeBuffer.Append(BoneName);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Inserted PIN code is: %s"), *CodeBuffer);
}

void ADoorPinLock::PressButton(const FString& BoneName)
{
	if (AnimationMap.Contains(BoneName))
	{
		Mesh->PlayAnimation(AnimationMap[BoneName], false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Wrong animation passed to PIN lock %s"), *GetName());
	}

	HandleButtonPress(BoneName);
}

void ADoorPinLock::EnterCode() const
{
	if (CodeBuffer.Equals(PinCode) && Door)
	{
		Door->IsClosed() ? Door->Open() : Door->Close();
		const auto BaseCharacter = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		BaseCharacter->SetPinLock(nullptr);
	}
}

EPinLockStatus ADoorPinLock::Status() const
{
	if (Door->IsClosed())
	{
		return EPinLockStatus::CLOSED;
	}
	return EPinLockStatus::OPEN;
}

FString ADoorPinLock::EnteredCode() const
{
	return CodeBuffer;
}

void ADoorPinLock::SetLightPosition(const FVector& Position) const
{
	CursorLight->SetWorldLocation(Position);
}

void ADoorPinLock::BeginPlay()
{
	Super::BeginPlay();
	const FRandomStream RandomStream(FDateTime::Now().GetTicks());
	if (PinCode.IsEmpty())
	{
		PinCode = FString::Printf(TEXT("%04d"), RandomStream.RandRange(0, 9999));
	}
	UE_LOG(LogTemp, Warning, TEXT("Generated PIN for Door %s is: %s"), *Door->GetName(), *PinCode);
}
