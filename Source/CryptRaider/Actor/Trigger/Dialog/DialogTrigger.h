// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DialogTrigger.generated.h"

UCLASS()
class CRYPTRAIDER_API ADialogTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADialogTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	virtual FDataTableRowHandle PickDialog();
	UFUNCTION(BlueprintCallable)
	virtual void SwitchTrigger(bool State);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	USceneComponent* Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* TriggerBox;
};
