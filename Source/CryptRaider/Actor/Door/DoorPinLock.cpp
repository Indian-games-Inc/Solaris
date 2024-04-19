// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorPinLock.h"

#include "Door.h"
#include "Camera/CameraComponent.h"
#include "Components/PointLightComponent.h"
#include "CryptRaider/Character/BaseCharacter.h"
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
	return Door->IsClosed() ? "Insert code" : "Block";
}

void ADoorPinLock::Interact()
{
	if (CodeBuffer.Equals(PinCode) && Door)
	{
		Door->IsClosed() ? Door->Open() : Door->Close();
		return;
	}

	const auto Player = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	Player->SetPinLock(Player->IsInPinLock() ? nullptr : this);
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
	else
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
		const auto Player = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		Player->SetPinLock(nullptr);
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
