// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HandInteractionComponent.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UHandInteractor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CRYPTRAIDER_API IHandInteractor
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void Interact() = 0;

	UFUNCTION()
	virtual FText ConstructHint() const = 0;
};
