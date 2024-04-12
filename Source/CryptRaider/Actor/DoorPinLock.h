// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DoorSwitchButton.h"

#include "DoorPinLock.generated.h"
/**
 * Pin lock for door
 */
UCLASS()
class CRYPTRAIDER_API ADoorPinLock : public ADoorSwitchButton
{
	GENERATED_BODY()
	ADoorPinLock();

	virtual void BeginPlay() override;
	virtual FString HintMessage() const override;
	virtual void Interact() override;

public:
	virtual void PressButton(const FString& AnimationKey);
	void RemoveLastChar();
	void EnterCode();

private:
	FString CodeBuffer;

	UPROPERTY(EditAnywhere)
	FString PinCode;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* PinMesh;

	UPROPERTY(EditAnywhere)
	TMap<FString, UAnimSequence*> AnimationMap;
};
