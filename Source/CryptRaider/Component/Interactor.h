// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractorHintUpdate, const FText&, Hints);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UInteractor : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractor();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Interact(const FHitResult& HitResult);

private:
	class UHand* GetHand() const;
	class ABasePlayerController* GetController() const;

	FText ConstructHintMessage() const;
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractorHintUpdate OnHintUpdated;
};
