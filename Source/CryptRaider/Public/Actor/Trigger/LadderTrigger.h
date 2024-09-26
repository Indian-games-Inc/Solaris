#pragma once

#include "CoreMinimal.h"
#include "GlueTrigger.h"
#include "LadderTrigger.generated.h"

UCLASS()
class CRYPTRAIDER_API ALadderTrigger : public AGlueTrigger
{
	GENERATED_BODY()

public:
	ALadderTrigger();
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult) override;

	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* LadderBox = nullptr;
};
