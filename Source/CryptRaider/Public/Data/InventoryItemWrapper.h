#pragma once

#include "CoreMinimal.h"
#include "Actor/Item/Item.h"
#include "ItemData.h"
#include "InventoryItemWrapper.generated.h"

/**
 * Structure for item data
 */
USTRUCT(BlueprintType)
struct CRYPTRAIDER_API FInventoryItemWrapper
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemData Data;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AItem> Class;
};
