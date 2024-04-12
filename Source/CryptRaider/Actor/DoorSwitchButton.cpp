// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorSwitchButton.h"
#include "Door.h"


// Sets default values
ADoorSwitchButton::ADoorSwitchButton()
{
	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

void ADoorSwitchButton::Interact()
{
	if (!Door)
	{
		UE_LOG(LogActor, Warning, TEXT("Failed to interact, Door is not set"));
		return;
	}

	if (Door->IsClosed())
	{
		Door->Open();
	}
	else
	{
		Door->Close();
	}
}

FString ADoorSwitchButton::HintMessage() const
{
	return Door->IsClosed() ? "Open" : "Close";
}
