#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Flashlight.generated.h"

UCLASS()
class CRYPTRAIDER_API AFlashlight : public AActor
{
	GENERATED_BODY()

public:
	AFlashlight();
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void Toggle();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Light, meta = (AllowPrivateAccess = "true"))
	class USpotLightComponent* SpotLight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Noise", meta=(AllowPrivateAccess = "true"))
	float ToggleLoudness = 0.1F;
};
