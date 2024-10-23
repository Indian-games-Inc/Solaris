#include "Actor/Terminal/Terminal.h"

#include "Components/WidgetComponent.h"


ATerminal::ATerminal()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	Monitor = CreateDefaultSubobject<UWidgetComponent>("Monitor");
	Monitor->SetupAttachment(Mesh);
}
