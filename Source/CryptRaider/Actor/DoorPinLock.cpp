// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorPinLock.h"

#include "Door.h"
#include "CryptRaider/Character/BaseCharacter.h"

ADoorPinLock::ADoorPinLock()
{
	PinMesh = CreateDefaultSubobject<USkeletalMeshComponent>("PinMesh");
	PinMesh->SetupAttachment(RootComponent);
}

FString ADoorPinLock::HintMessage() const
{
	return Door->IsClosed() ? "Insert code" : "Block";
}

void ADoorPinLock::Interact()
{
	const auto Player = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	Player->SetPinLock(this);
}

void ADoorPinLock::PressButton(const FString& AnimationKey)
{
	if (!AnimationMap.Contains(AnimationKey))
	{
		UE_LOG(LogTemp, Warning, TEXT("Wrong animation passed to PIN lock %s"), *GetName());
		return;
	}

	if (!AnimationKey.Equals("Enter") && !AnimationKey.Equals("Backspace"))
	{
		CodeBuffer.Append(AnimationKey);
	}

	PinMesh->PlayAnimation(AnimationMap[AnimationKey], false);
	UE_LOG(LogTemp, Warning, TEXT("Inserted PIN code is: %s"), *CodeBuffer);
}

void ADoorPinLock::RemoveLastChar()
{
	if (!CodeBuffer.IsEmpty())
	{
		CodeBuffer.RemoveAt(CodeBuffer.Len() - 1, 1);
		PressButton("Backspace");
	}
}

void ADoorPinLock::EnterCode()
{
	PressButton("Enter");
	if (CodeBuffer.Equals(PinCode) && Door)
	{
		Door->IsClosed() ? Door->Open() : Door->Close();
	}
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
