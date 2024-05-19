// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Door.generated.h"

class UCurveFloat;

UCLASS()
class CRYPTRAIDER_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Open();
	
	UFUNCTION(BlueprintCallable)
	void Close();

public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* OutDoorMesh;

	UPROPERTY(EditAnywhere, Category="Door Settings")
	float OpenedRotation = 110;

	UPROPERTY(EditAnywhere, Category="Door Settings")
	float ClosedRotation = 0;

	UPROPERTY(EditAnywhere, Category="Door Settings")
	UCurveFloat* MoveCurve;

	UFUNCTION(BlueprintCallable)
	bool IsClosed();
	
private:
	bool Closed = true;
	
	FTimeline MoveTimeLine;

	UFUNCTION()
	void MoveUpdate(float Alpha);
	
	UFUNCTION()
	void MoveFinished();
};
