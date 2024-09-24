#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DialogStateStrategy.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDialogStateStrategy : public UInterface
{
	GENERATED_BODY()
};


class CRYPTRAIDER_API IDialogStateStrategy
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual bool IsActive() = 0; // Might be replaced with ENUM to extend trigger state statuses

	UFUNCTION()
	virtual void OnTrigger() = 0; // Used to notify strategy of trigger events
};
