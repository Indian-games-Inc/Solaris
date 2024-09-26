#pragma once

#include "CoreMinimal.h"
#include "DoorButton.h"
#include "Components/SpotLightComponent.h"
#include "Components/WidgetComponent.h"
#include "Interface/PinLock.h"
#include "DoorPinLock.generated.h"

class UPointLightComponent;
class UCameraComponent;

/**
 * Pin lock for door
 */
UCLASS()
class CRYPTRAIDER_API ADoorPinLock : public ADoorButton, public IPinLock
{
	GENERATED_BODY()
public:
	ADoorPinLock();

protected:
	virtual void BeginPlay() override;

public:
	virtual FString HintMessage() const override;
	virtual void Interact() override;
	virtual bool IsActive() const override;
	
	virtual void PressButton(const FString& BoneName);
	void SetLightPosition(const FVector& Position) const;
	void EnterCode() const;

public:
	UFUNCTION(BlueprintCallable)
	virtual EPinLockStatus Status() const override;

	UFUNCTION(BlueprintCallable)
	virtual FString EnteredCode() const override;

private:
	void HandleButtonPress(const FString& BoneName);
	
private:
	FString CodeBuffer;

	UPROPERTY(EditAnywhere)
	FString PinCode;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	int32 BufferSize = 4;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CloseUpCamera;
	UPROPERTY(EditAnywhere)
	UPointLightComponent* CursorLight;

	UPROPERTY(EditAnywhere)
	TMap<FString, UAnimSequence*> AnimationMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UWidgetComponent* Screen;
};
