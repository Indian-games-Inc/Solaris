#include "GlueTrigger.h"

#include "Components/BoxComponent.h"


// Sets default values
AGlueTrigger::AGlueTrigger()
{
	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));	
	SetRootComponent(Root);
	
	//Trigger box
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Box"));
	TriggerBox->SetupAttachment(RootComponent);

	//Ladder box
	LadderBox = CreateDefaultSubobject<UBoxComponent>(FName("Ladder Box"));
	LadderBox->SetupAttachment(RootComponent);

	//Target
	// const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Content/Map/_GENERATED/DarkMinimum/Box_F5DA6FED.uasset"));
	Target = CreateDefaultSubobject<UStaticMeshComponent>(FName("Target"));
	Target->SetupAttachment(RootComponent);
	// Target->SetStaticMesh(MeshObj.Object);
}

void AGlueTrigger::OnConstruction(const FTransform& Transform)
{
	
	// TriggerBox->SetBoxExtent(TriggerArea, true);
	// LadderBox->SetBoxExtent(LadderArea, true);
	LadderBox->SetVisibility(IsDebug, true);
	TriggerBox->SetVisibility(IsDebug, true);

	Super::OnConstruction(Transform);
}
