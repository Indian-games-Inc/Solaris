// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogTrigger.h"

#include "CryptRaider/Player/BasePlayerController.h"

void ADialogTrigger::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (DialogStrategyClass)
	{
		if (!DialogStrategy || DialogStrategy->GetClass() != DialogStrategyClass)
		{
			if (DialogStrategy)
			{
				DialogStrategy->ConditionalBeginDestroy();
				DialogStrategy->DestroyComponent();
			}
			DialogStrategy = NewObject<UBaseDialogPickStrategy>(this, DialogStrategyClass, "Dialog Strategy");
		}
	}

	if (StateStrategyClass)
	{
		if (!StateStrategy || StateStrategy->GetClass() != StateStrategyClass)
		{
			if (StateStrategy)
			{
				StateStrategy->ConditionalBeginDestroy();
				StateStrategy->DestroyComponent();
			}
			StateStrategy = NewObject<UBaseTriggerStateStrategy>(this, StateStrategyClass, "State Strategy");
		}
	}
}

void ADialogTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	if (!StateStrategy)
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogTrigger::OnBeginOverlap called, but StateStrategy is empty"));
		return;
	}

	if (StateStrategy->IsActive())
	{
		SendDialog();
	}

	StateStrategy->OnTrigger();
}

void ADialogTrigger::SendDialog()
{
	if (!DialogStrategy)
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogTrigger::SendDialog called, but DialogStrategy is empty"));
		return;
	}

	const auto Controller = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());
	SendDialogToHUD(Controller->GetHUD(), DialogStrategy->GetDialog());
}
