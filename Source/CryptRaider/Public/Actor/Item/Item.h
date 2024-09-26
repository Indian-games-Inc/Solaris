#pragma once

#include "CoreMinimal.h"
#include "Data/ItemData.h"
#include "Interface/BaseInteractable.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

struct FItemData;

UCLASS()
class CRYPTRAIDER_API AItem : public ABaseInteractable
{
	GENERATED_BODY()

public:
	AItem();

public:
	FItemData Pick();
	virtual FString HintMessage() const override;

private:
	// all item specs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FItemData ItemData;
};
