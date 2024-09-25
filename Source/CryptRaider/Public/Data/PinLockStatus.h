#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType, Blueprintable)
enum class EPinLockStatus : uint8
{
	OPEN UMETA(DisplayName = "OPEN"),
	CLOSED UMETA(DisplayName = "CLOSED"),
	BLOCKED UMETA(DisplayName = "BLOCKED"),
};
