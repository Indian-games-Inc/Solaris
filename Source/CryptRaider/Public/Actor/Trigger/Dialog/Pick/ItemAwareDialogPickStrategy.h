#pragma once

#include "CoreMinimal.h"
#include "ConditionalDialogPickStrategy.h"
#include "ItemAwareDialogPickStrategy.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UItemAwareDialogPickStrategy : public UConditionalDialogPickStrategy
{
	GENERATED_BODY()

public:
	virtual bool Check() override;

private:
	UPROPERTY(Category="ConditionalDialogPickStrategy", EditInstanceOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	FString ItemId;
};
