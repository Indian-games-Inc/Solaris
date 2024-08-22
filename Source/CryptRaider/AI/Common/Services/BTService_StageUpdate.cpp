// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_StageUpdate.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTService_StageUpdate::UBTService_StageUpdate()
{
	StageUpdateInterval = 30.0f; // Default to 30 seconds between stage updates

	// Configure the service to notify when it becomes and ceases to be relevant
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;

	SavedStage = EMonsterStage::None;
}

FString UBTService_StageUpdate::GetStaticDescription() const
{
	return Super::GetStaticDescription();
}

void UBTService_StageUpdate::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	SavedStage = GetCurrentStage(&OwnerComp);
	ResetStageTimer(OwnerComp);
}

void UBTService_StageUpdate::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

	// Clear the timer when the service is no longer relevant
	OwnerComp.GetWorld()->GetTimerManager().ClearTimer(StageUpdateTimerHandle);
}

void UBTService_StageUpdate::UpdateStage(UBehaviorTreeComponent* OwnerComp)
{
	const EMonsterStage CurrentStage = GetCurrentStage(OwnerComp);

	EMonsterStage NextStage;
	switch (CurrentStage)
	{
	case EMonsterStage::Friendly:
		NextStage = EMonsterStage::Neutral;
		break;
	case EMonsterStage::Neutral:
		NextStage = EMonsterStage::Aggressive;
		break;
	case EMonsterStage::Aggressive:
		NextStage = EMonsterStage::Death;
		break;
	case EMonsterStage::Death:
		NextStage = EMonsterStage::Death; // Stay at max stage
		break;
	default:
		NextStage = EMonsterStage::Friendly; // Default stage
		break;
	}

	if (UBlackboardComponent* BlackboardComponent = OwnerComp->GetBlackboardComponent(); BlackboardComponent)
	{
		SavedStage = NextStage;
		BlackboardComponent->SetValueAsEnum(StageKey.SelectedKeyName, StaticCast<uint8>(NextStage));	
	}
}

void UBTService_StageUpdate::ResetStageTimer(UBehaviorTreeComponent& OwnerComp)
{
	OwnerComp.GetWorld()->GetTimerManager().ClearTimer(StageUpdateTimerHandle);
	
	FTimerDelegate UpdateStageDelegate;
	UpdateStageDelegate.BindUFunction(this, "UpdateStage", &OwnerComp);

	GetWorld()->GetTimerManager().SetTimer(StageUpdateTimerHandle,
										   UpdateStageDelegate,
										   StageUpdateInterval, true);
}

EMonsterStage UBTService_StageUpdate::GetCurrentStage(UBehaviorTreeComponent* OwnerComp) const
{
	if (const UBlackboardComponent* BlackboardComp = OwnerComp->GetBlackboardComponent(); BlackboardComp)
	{
		return StaticCast<EMonsterStage>(BlackboardComp->GetValueAsEnum(StageKey.SelectedKeyName));
	}

	return EMonsterStage::None;
}

void UBTService_StageUpdate::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (SavedStage != GetCurrentStage(&OwnerComp))
	{
		ResetStageTimer(OwnerComp);
	}
}
