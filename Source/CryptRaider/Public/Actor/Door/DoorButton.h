#pragma once

#include "CoreMinimal.h"
#include "../../Interface/BaseInteractable.h"
#include "GameFramework/Actor.h"
#include "DoorButton.generated.h"

UCLASS()
class CRYPTRAIDER_API ADoorButton : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	ADoorButton();

public:
	UFUNCTION(BlueprintCallable)
	virtual void Interact() override;

	virtual FString HintMessage() const override;

	virtual bool IsActive() const override;

protected:
	UPROPERTY(EditInstanceOnly)
	class ADoor* Door;
	
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;

private:
	USceneComponent* Root = nullptr;
};
