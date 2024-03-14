// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GlueTrigger.generated.h"


class UBoxComponent;

UCLASS()
class CRYPTRAIDER_API AGlueTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGlueTrigger();
	//
	// protected:
	// 	// Called when the game starts or when spawned
	// 	virtual void BeginPlay() override;

	void OnConstruction(const FTransform& Transform) override;


private:
	USceneComponent* Root = nullptr;

	//List of the exposed values in UE
	UPROPERTY(EditInstanceOnly)
	class AItem* ItemClass;
	// UPROPERTY(EditInstanceOnly)
	// FVector TriggerArea;
	// UPROPERTY(EditInstanceOnly)
	// FTransform TargetTransform;
	// UPROPERTY(EditInstanceOnly)
	// FVector LadderArea;
	// UPROPERTY(EditInstanceOnly)
	// FTransform LadderTransform;
	UPROPERTY(EditInstanceOnly)
	bool IsClimbable;
	UPROPERTY(EditInstanceOnly)
	bool IsDebug;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* TriggerBox = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* LadderBox = nullptr;
};
