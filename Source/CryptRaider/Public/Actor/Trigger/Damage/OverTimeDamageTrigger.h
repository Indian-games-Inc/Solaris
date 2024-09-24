#pragma once

#include "CoreMinimal.h"
#include "../BaseTrigger.h"
#include "GameFramework/Actor.h"
#include "OverTimeDamageTrigger.generated.h"

UCLASS()
class CRYPTRAIDER_API AOverTimeDamageTrigger : public ABaseTrigger
{
	GENERATED_BODY()

public:
	AOverTimeDamageTrigger();

public:
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult) override;
	
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
	UFUNCTION()
	void DealDamageTo(AActor* OtherActor);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Damage = 10.f;


	FTimerHandle DamageTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DamageDelay = 1.f;
};
