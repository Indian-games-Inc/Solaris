#include "Actor/Door/DoorButton.h"

#include "Actor/Door/Door.h"


ADoorButton::ADoorButton()
{
	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

void ADoorButton::Interact()
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

FString ADoorButton::HintMessage() const
{
	if (!Door)
	{
		UE_LOG(LogActor, Warning, TEXT("Failed to generate a hint, Door is not set"));
		return "Error";
	}
	
	return Door->IsClosed() ? "Open" : "Close";
}

bool ADoorButton::IsActive() const
{
	return true;
}
