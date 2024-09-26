#pragma once

#include "CoreMinimal.h"
#include "BaseHandInteractor.h"

#include "Interactor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UInteractor : public UBaseHandInteractor
{
	GENERATED_BODY()

public:
	virtual void Interact() override;
	virtual FText ConstructHint() const override;
};
