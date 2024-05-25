#pragma once
#include "CoreMinimal.h"
#include "DialogRow.generated.h"

USTRUCT(BlueprintType)
struct CRYPTRAIDER_API FDialogRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Nickname;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Message;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateColor Color;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle NextDialog;
};
