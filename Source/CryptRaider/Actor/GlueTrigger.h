// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "GlueTrigger.generated.h"


class AItem;
class UBoxComponent;

UCLASS()
class CRYPTRAIDER_API AGlueTrigger : public AActor
{
	GENERATED_BODY()

public:
	AGlueTrigger();

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	AItem* SelectOverlappingItems();

	/* Timeline events*/
	UFUNCTION()
	void MoveUpdate(float Alpha);
	UFUNCTION()
	void MoveFinished();

	/* Overlapping LadderBox events */
	UFUNCTION()
	void OnLadderComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                   const FHitResult& SweepResult);
	UFUNCTION()
	void OnLadderComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	USceneComponent* Root = nullptr;
	AItem* GluedItem = nullptr;
	FTimeline Timeline;
	bool IsGlued = false;
	const FName GrabbedTag = "Grabbed";

	/* Configurable values*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCurveFloat* FloatCurve;
	UPROPERTY(EditInstanceOnly)
	TSubclassOf<AActor> ItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* TriggerBox = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* LadderBox = nullptr;
	UPROPERTY(EditInstanceOnly)
	bool IsClimbable = false;
	UPROPERTY(EditInstanceOnly)
	bool IsDebug = false;
};
