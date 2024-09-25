#pragma once

#include "CoreMinimal.h"
#include "../BaseTrigger.h"
#include "DeathTrigger.generated.h"

UCLASS()
class CRYPTRAIDER_API ADeathTrigger : public ABaseTrigger
{
	GENERATED_BODY()

public:
	ADeathTrigger();

protected:
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
