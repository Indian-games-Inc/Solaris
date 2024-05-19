// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DoorButton.h"
#include "Components/SpotLightComponent.h"
#include "DoorPinLock.generated.h"

class UPointLightComponent;
class UCameraComponent;

/**
 * Pin lock for door
 */
UCLASS()
class CRYPTRAIDER_API ADoorPinLock : public ADoorButton
{
	GENERATED_BODY()
	ADoorPinLock();

	virtual void BeginPlay() override;
	virtual FString HintMessage() const override;
	virtual void Interact() override;
	void HandleButtonPress(const FString& BoneName);

public:
	virtual void PressButton(const FString& BoneName);
	void SetLightPosition(FVector Position) const;
	void EnterCode() const;

private:
	FString CodeBuffer;

	UPROPERTY(EditAnywhere)
	FString PinCode;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CloseUpCamera;
	UPROPERTY(EditAnywhere)
	UPointLightComponent* CursorLight;

	UPROPERTY(EditAnywhere)
	TMap<FString, UAnimSequence*> AnimationMap;
};
