#pragma once

#include "CoreMinimal.h"
#include "BaseDialogPickStrategy.h"
#include "ConditionalDialogPickStrategy.generated.h"


UCLASS(HideDropdown, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UConditionalDialogPickStrategy : public UBaseDialogPickStrategy
{
	GENERATED_BODY()

public:
	virtual bool Check();
	virtual FDataTableRowHandle GetDialog() override;

private:
	FDataTableRowHandle PickRandomDialog(TArray<FDataTableRowHandle> DialogList);
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	TArray<FDataTableRowHandle>	NegativeDialogList;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	TArray<FDataTableRowHandle>	PositiveDialogList;
};
