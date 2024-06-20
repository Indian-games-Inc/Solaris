// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CryptRaider/Actor/Trigger/BaseTrigger.h"
#include "GameFramework/Actor.h"
#include "DialogTrigger.generated.h"

UCLASS()
class CRYPTRAIDER_API ADialogTrigger : public ABaseTrigger
{
	GENERATED_BODY()

protected:
	/** Pure Blueprint Event **/
	UFUNCTION(BlueprintImplementableEvent)
	void SendDialogToHUD(AHUD* HUD, FDataTableRowHandle DialogRowHandle);

	/**
	 * Base Begin overlap function for Dialog Triggers:
	 * all inheritors should implement PickDialog(), SwitchTriggerState()
	 */
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult);

	/** Functions used in OnBeginOverlap **/
	virtual FDataTableRowHandle PickDialog();
	virtual void SwitchTriggerState();
};
