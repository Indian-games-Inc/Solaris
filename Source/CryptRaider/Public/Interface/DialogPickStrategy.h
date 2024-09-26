#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DialogPickStrategy.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDialogPickStrategy : public UInterface
{
	GENERATED_BODY()
};


class CRYPTRAIDER_API IDialogPickStrategy
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual FDataTableRowHandle GetDialog() = 0;
};
