#pragma once

#include "CoreMinimal.h"
#include "Engine/Classes/GameFramework/Actor.h"
#include "Terminal.generated.h"

UCLASS()
class CRYPTRAIDER_API ATerminal : public AActor
{
	GENERATED_BODY()

public:
	ATerminal();

private:
	UPROPERTY(EditDefaultsOnly, Category="Mesh", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, Category="Monitor", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> Monitor;
};
