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
			DialogStrategy = NewObject<UBaseDialogPickStrategy>(this, DialogStrategyClass);
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
	if (StateStrategy->IsActive())
	{
		SendDialog();
	}

	StateStrategy->OnTrigger();
}

void ADialogTrigger::SendDialog()
{
	const auto Controller = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());
	SendDialogToHUD(Controller->GetHUD(), DialogStrategy->GetDialog());
}
