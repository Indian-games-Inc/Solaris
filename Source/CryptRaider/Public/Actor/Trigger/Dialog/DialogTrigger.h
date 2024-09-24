#pragma once

#include "CoreMinimal.h"
#include "Pick/BaseDialogPickStrategy.h"
#include "State/BaseTriggerStateStrategy.h"
#include "Actor/Trigger/BaseTrigger.h"
#include "GameFramework/Actor.h"
#include "DialogTrigger.generated.h"

UCLASS()
class CRYPTRAIDER_API ADialogTrigger : public ABaseTrigger
{
	GENERATED_BODY()

public:
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
								const FHitResult& SweepResult) override;

	void SendDialog();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog|Pick Strategy", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UBaseDialogPickStrategy> DialogStrategyClass;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Dialog|Pick Strategy", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBaseDialogPickStrategy> DialogStrategy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog|State Strategy", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UBaseTriggerStateStrategy> StateStrategyClass;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Dialog|State Strategy",
		meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBaseTriggerStateStrategy> StateStrategy;
};
