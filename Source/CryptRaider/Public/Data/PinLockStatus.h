// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType, Blueprintable)
enum class EPinLockStatus : uint8
{
	OPEN UMETA(DisplayName = "OPEN"),
	CLOSED UMETA(DisplayName = "CLOSED"),
	BLOCKED UMETA(DisplayName = "BLOCKED"),
};
