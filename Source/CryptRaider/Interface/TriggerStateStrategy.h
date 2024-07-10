// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TriggerStateStrategy.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTriggerStateStrategy : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CRYPTRAIDER_API ITriggerStateStrategy
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual bool IsActive() = 0; // Might be replaced with ENUM to extend trigger state statuses

	UFUNCTION()
	virtual void OnTrigger() = 0; // Used to notify strategy of trigger events
};
