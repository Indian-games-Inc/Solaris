#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteractable : public UInterface
{
	GENERATED_BODY()
};


class CRYPTRAIDER_API IInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void Interact() = 0;

	UFUNCTION()
	virtual FString HintMessage() const = 0;

	UFUNCTION()
	virtual bool IsActive() const = 0;

};
