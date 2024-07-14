// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogTrigger.h"

#include "CryptRaider/Player/BasePlayerController.h"

ADialogTrigger::ADialogTrigger()
{
}

void ADialogTrigger::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (DialogStrategyClass)
	{
		if (!DialogStrategy || DialogStrategy->GetClass() != DialogStrategyClass)
		{
			DialogStrategy = NewObject<UBaseTriggerDialogStrategy>(this, DialogStrategyClass);
		}
	}

	if (StateStrategyClass)
	{
		if (!StateStrategy || StateStrategy->GetClass() != StateStrategyClass)
		{
			StateStrategy = NewObject<UBaseTriggerStateStrategy>(this, StateStrategyClass);
		}
	}
}

void ADialogTrigger::BeginPlay()
{
	Super::BeginPlay();
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
