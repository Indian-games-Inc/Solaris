// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DoorSwitchButton.h"
#include "DoorLocker.generated.h"

UCLASS()
class CRYPTRAIDER_API ADoorLocker : public ADoorSwitchButton
{
	GENERATED_BODY()

public:
	virtual void Interact() override;
	virtual FString HintMessage() const override;

private:
	bool HasKey() const;
	
	UPROPERTY(EditAnywhere)
	FString ItemID;
};
