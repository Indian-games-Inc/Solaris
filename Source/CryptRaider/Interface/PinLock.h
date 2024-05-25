// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CryptRaider/Data/PinLockStatus.h"
#include "PinLock.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPinLock : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CRYPTRAIDER_API IPinLock
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(NotBlueprintable)
	virtual EPinLockStatus Status() const = 0;
	
	UFUNCTION(NotBlueprintable)
	virtual FString EnteredCode() const = 0;
};
