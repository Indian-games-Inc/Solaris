// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactor.h"

#include "CryptRaider/Interface/Interactable.h"

void UInteractor::Interact(const FHitResult& HitResult)
{
	if (IInteractable* Actor = Cast<IInteractable>(HitResult.GetActor()))
	{
		Actor->Interact();
	}
}
