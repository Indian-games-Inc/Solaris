#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/HandInteractionComponent.h"
#include "BaseHandInteractor.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UBaseHandInteractor : public UActorComponent, public IHandInteractor
{
	GENERATED_BODY()

public:
	virtual void Interact() override;
	virtual FText ConstructHint() const override;

protected:
	class UHand* GetHand() const;
	class ABasePlayerController* GetController() const;
};
