#pragma once

#include "CoreMinimal.h"
#include "ConditionalDialogPickStrategy.h"
#include "GrabberAwareDialogPickStrategy.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UGrabberAwareDialogPickStrategy : public UConditionalDialogPickStrategy
{
	GENERATED_BODY()

public:
	virtual bool Check() override;

private:
	UPROPERTY(Category="ConditionalDialogPickStrategy", EditInstanceOnly, BlueprintReadWrite,
		meta=(AllowPrivateAccess="true"))
	FString ItemName;
};
