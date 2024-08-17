#pragma once
#include "BaseTrigger.h"
#include "NoiseTrigger.generated.h"

UCLASS()
class CRYPTRAIDER_API ANoiseTrigger : public ABaseTrigger
{
	GENERATED_BODY()

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Loudness = 1.0F;
};
