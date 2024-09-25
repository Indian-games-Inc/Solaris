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
	ADoor();

protected:
	virtual void BeginPlay() override;

public:
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
