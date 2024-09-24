#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/PinLockStatus.h"
#include "PinLock.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPinLock : public UInterface
{
	GENERATED_BODY()
};


class CRYPTRAIDER_API IPinLock
{
	GENERATED_BODY()

public:
	UFUNCTION(NotBlueprintable)
	virtual EPinLockStatus Status() const = 0;
	
	UFUNCTION(NotBlueprintable)
	virtual FString EnteredCode() const = 0;
};
