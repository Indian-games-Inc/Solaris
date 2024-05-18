// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorPinLock.h"

#include "Door.h"
#include "Camera/CameraComponent.h"
#include "Components/PointLightComponent.h"
#include "CryptRaider/Player/BaseCharacter.h"
#include "CryptRaider/Player/BasePlayerController.h"
#include "Kismet/KismetMathLibrary.h"

ADoorPinLock::ADoorPinLock()
{
	CloseUpCamera = CreateDefaultSubobject<UCameraComponent>("CloseUpCamera");
	CloseUpCamera->SetupAttachment(RootComponent);
	CursorLight = CreateDefaultSubobject<UPointLightComponent>("CursorLight");
	CursorLight->SetupAttachment(RootComponent);
}

FString ADoorPinLock::HintMessage() const
{
	if (CodeBuffer.Equals(PinCode))
	{
		return Door->IsClosed() ? "Unblock" : "Block";
	}
	return "Insert code";
}

void ADoorPinLock::Interact()
{
	if (CodeBuffer.Equals(PinCode) && Door)
	{
		Door->IsClosed() ? Door->Open() : Door->Close();
		return;
	}

	const auto BaseCharacter = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	BaseCharacter->SetPinLock(BaseCharacter->IsInPinLock() ? nullptr : this);
}

void ADoorPinLock::HandleButtonPress(const FString& BoneName)
{
	if (BoneName.Equals("enter"))
	{
		EnterCode();
	}
	else if (BoneName.Equals("del"))
	{
		if (CodeBuffer.Len() > 0)
			CodeBuffer.RemoveAt(CodeBuffer.Len() - 1, 1);
	}
	else if (BoneName.IsNumeric())
	{
		CodeBuffer.Append(BoneName);
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

void ADoorPinLock::SetLightPosition(FVector Position) const
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
