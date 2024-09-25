#pragma once

#include "CoreMinimal.h"
#include "DoorButton.h"
#include "DoorItemLock.generated.h"

UCLASS()
class CRYPTRAIDER_API ADoorItemLock : public ADoorButton
{
	GENERATED_BODY()

public:
	virtual void Interact() override;
	virtual FString HintMessage() const override;

private:
	bool HasKey() const;
	
	UPROPERTY(EditAnywhere)
	FString ItemID;
};
