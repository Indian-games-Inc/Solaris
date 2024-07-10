// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTriggerDialogStrategy.h"
#include "CryptRaider/Actor/Trigger/State/BaseTriggerStateStrategy.h"
#include "CryptRaider/Actor/Trigger/BaseTrigger.h"
#include "CryptRaider/Player/BasePlayerController.h"
#include "GameFramework/Actor.h"
#include "DialogTrigger.generated.h"

UCLASS()
class CRYPTRAIDER_API ADialogTrigger : public ABaseTrigger
{
	GENERATED_BODY()


public:
	ADialogTrigger();
	virtual void OnConstruction(const FTransform& Transform) override;

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

	void SendDialog(ABasePlayerController* Controller);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UBaseTriggerDialogStrategy> DialogStrategyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog", meta=(AllowPrivateAccess = "true"))
	UBaseTriggerDialogStrategy* DialogStrategy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UBaseTriggerStateStrategy> StateStrategyClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State", meta=(AllowPrivateAccess = "true"))
	UBaseTriggerStateStrategy* StateStrategy;
};
