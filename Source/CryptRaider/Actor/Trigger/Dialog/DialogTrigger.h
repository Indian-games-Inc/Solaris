// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CryptRaider/Actor/Trigger/BaseTrigger.h"
#include "CryptRaider/Player/BasePlayerController.h"
#include "GameFramework/Actor.h"
#include "DialogTrigger.generated.h"

UCLASS()
class CRYPTRAIDER_API ADialogTrigger : public ABaseTrigger
{
	GENERATED_BODY()

	void SendDialog(ABasePlayerController* Controller);

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

	/** Functions used in OnBeginOverlap */
	virtual FDataTableRowHandle PickDialog();
	virtual void SwitchTriggerState();

	/** Enables to add condition related to the item */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Dialog Trigger")
	bool InventoryAware;

	/** If checked, then works only when player have an item, otherwise makes sure that player don't have item */
	UPROPERTY(EditInstanceOnly, Category="Dialog Trigger", meta=(EditCondition="InventoryAware"))
	bool HasItem;

	UPROPERTY(EditInstanceOnly, Category="Dialog Trigger", meta=(EditCondition="InventoryAware"))
	FString ItemId;
};
