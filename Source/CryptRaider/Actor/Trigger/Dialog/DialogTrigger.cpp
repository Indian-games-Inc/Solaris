// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogTrigger.h"

#include "CryptRaider/Actor/Trigger/State/BaseTriggerStateStrategy.h"
#include "CryptRaider/Player/BasePlayerController.h"

ADialogTrigger::ADialogTrigger()
{
	DialogStrategy = CreateDefaultSubobject<UBaseTriggerDialogStrategy>(TEXT("Dialog Strategy"));

	StateStrategy = CreateDefaultSubobject<UBaseTriggerStateStrategy>(TEXT("State Strategy"));
}

void ADialogTrigger::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (DialogStrategyClass)
	{
		DialogStrategy = NewObject<UBaseTriggerDialogStrategy>(this, DialogStrategyClass);
	}
	if (StateStrategyClass)
	{
		StateStrategy = NewObject<UBaseTriggerStateStrategy>(this, StateStrategyClass);
	}
}

void ADialogTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	const auto Controller = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());

	if (StateStrategy->IsActive())
	{
		SendDialog(Controller);
	}

	StateStrategy->OnTrigger();
}

void ADialogTrigger::SendDialog(ABasePlayerController* Controller)
{
	SendDialogToHUD(Controller->GetHUD(), DialogStrategy->GetDialog());
}
