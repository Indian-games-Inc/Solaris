// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactible.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteractible : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CRYPTRAIDER_API IInteractible
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void Interact() = 0;

	UFUNCTION()
	virtual FString HintMessage() const = 0;

	UFUNCTION()
	virtual bool IsActive() const = 0;

};
