#pragma once

#include "CoreMinimal.h"
#include "BaseTrigger.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "GlueTrigger.generated.h"


class ABaseInteractable;
class UBoxComponent;

UCLASS()
class CRYPTRAIDER_API AGlueTrigger : public ABaseTrigger
{
	GENERATED_BODY()

public:
	AGlueTrigger();
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;

	TSoftObjectPtr<ABaseInteractable> GetOverlappingObject();

	/* Timeline events*/
	UFUNCTION()
	void MoveUpdate(float Alpha);
	UFUNCTION()
	void MoveFinished();

	/* Overlapping LadderBox events */
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult) override;
	
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

public:
    virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(VisibleAnywhere)
	bool IsGlued = false;

	UPROPERTY(EditInstanceOnly)
	bool IsDebug = true;

private:
	UPROPERTY(EditInstanceOnly)
	TSubclassOf<AActor> GluedObjectClass;

	TSoftObjectPtr<ABaseInteractable> GluedObject = nullptr;

	FTimeline Timeline;
	const FName GrabbedTag = "Grabbed";

	/* Configurable values*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCurveFloat* FloatCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Target;
};
