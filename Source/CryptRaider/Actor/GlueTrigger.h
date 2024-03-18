// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "GlueTrigger.generated.h"


class AItem;
class UGrabber;
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
	void SelectOverlappingItem();

	//timeline functions
	UFUNCTION()
	void MoveUpdate(float Alpha);
	UFUNCTION()
	void MoveFinished();
	//overlapping ladder function
	UFUNCTION()
	void OnLadderComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                   const FHitResult& SweepResult);
	UFUNCTION()
	void OnLadderComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UGrabber* Grabber = nullptr;
	USceneComponent* Root = nullptr;
	bool IsGlued = false;
	AItem* GluedItem = nullptr;
	FTimeline Timeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCurveFloat* FloatCurve;

	UPROPERTY(EditInstanceOnly)
	TSubclassOf<AActor> ItemClass;
	UPROPERTY(EditInstanceOnly)
	bool IsClimbable = false;
	UPROPERTY(EditInstanceOnly)
	bool IsDebug = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* TriggerBox = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* LadderBox = nullptr;
};
