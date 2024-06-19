// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogTrigger.h"

void ADialogTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	SendDialogToHUD(GetWorld()->GetFirstPlayerController()->GetHUD(), PickDialog());
	SwitchTriggerState();
}

FDataTableRowHandle ADialogTrigger::PickDialog()
{
	return {};
}

void ADialogTrigger::SwitchTriggerState()
{
}
