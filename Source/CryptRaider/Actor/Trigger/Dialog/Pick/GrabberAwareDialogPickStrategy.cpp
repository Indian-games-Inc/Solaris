// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberAwareDialogPickStrategy.h"

#include "CryptRaider/Component/Grabber.h"
#include "CryptRaider/Player/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

FDataTableRowHandle UGrabberAwareDialogPickStrategy::GetDialog()
{
	const FRandomStream RandomStream(FDateTime::Now().GetTicks());
	const auto Grabber = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetGrabber();

	FDataTableRowHandle Dialog = {};
	if (!Grabber->IsGrabbing())
	{
		if (NegativeDialogList.Num() > 0)
		{
			Dialog = NegativeDialogList[RandomStream.RandRange(0, NegativeDialogList.Num() - 1)];
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Name is %s"), *Grabber->GetGrabbedItemId());
		if (Grabber->GetGrabbedItemId() == ItemId && PositiveDialogList.Num() > 0)
		{
			Dialog = PositiveDialogList[RandomStream.RandRange(0, PositiveDialogList.Num() - 1)];
		}
	}
	return Dialog;
}
