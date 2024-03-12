// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactor.h"

#include "CryptRaider/Interface/Interactible.h"

void UInteractor::Interact(const FHitResult& HitResult)
{
	if (IInteractible* Actor = Cast<IInteractible>(HitResult.GetActor()))
	{
		Actor->Interact();
	}
}
