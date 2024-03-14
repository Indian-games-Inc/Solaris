// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "WorldPartition/ContentBundle/ContentBundleLog.h"

// Sets default values
ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));

	OutDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OutDoor"));

	SetRootComponent(OutDoorMesh);
	DoorMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat ProgressUpdate;
	ProgressUpdate.BindUFunction(this, TEXT("MoveUpdate"));

	FOnTimelineEvent ProgressFinished;
	ProgressFinished.BindUFunction(this, TEXT("MoveFinished"));

	MoveTimeLine.AddInterpFloat(MoveCurve, ProgressUpdate);
	MoveTimeLine.SetTimelineFinishedFunc(ProgressFinished);

	if (DoorMesh)
		DoorMesh->SetRelativeRotation({0, ClosedRotation, 0});
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTimeLine.TickTimeline(DeltaTime);
}

void ADoor::Open()
{
	if (DoorMesh == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot open, Door static mesh wasn't set"));
		return;
	}

	MoveTimeLine.Play();
	Closed = false;
}

void ADoor::Close()
{
	MoveTimeLine.Reverse();
	Closed = true;
}

bool ADoor::IsClosed()
{
	return Closed;
}

void ADoor::MoveUpdate(float Alpha)
{
	FRotator NewDoorRotation = {0, FMath::Lerp(ClosedRotation, OpenedRotation, Alpha), 0,};
	
	if (DoorMesh)
		DoorMesh->SetRelativeRotation(NewDoorRotation);
}

void ADoor::MoveFinished()
{
}

