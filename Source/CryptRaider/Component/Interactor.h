// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UInteractor : public USceneComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void Interact(const FHitResult& HitResult);
};
