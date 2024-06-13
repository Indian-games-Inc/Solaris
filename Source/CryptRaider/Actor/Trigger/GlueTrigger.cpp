#include "GlueTrigger.h"

#include "../../Interface/BaseInteractable.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"


AGlueTrigger::AGlueTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;

	Target = CreateDefaultSubobject<UStaticMeshComponent>(FName("Target"));
	Target->SetupAttachment(RootComponent);

	FCollisionResponseContainer TriggerBoxCollisionResponses;
	TriggerBoxCollisionResponses.SetResponse(ECC_GameTraceChannel1, ECR_Overlap);
	TriggerBoxCollisionResponses.SetResponse(ECC_Pawn, ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannels(TriggerBoxCollisionResponses);

	TriggerBox->SetVisibility(IsDebug);
	Target->SetVisibility(IsDebug);

	TriggerBox->SetHiddenInGame(!IsDebug);
	Target->SetHiddenInGame(!IsDebug);
}

void AGlueTrigger::MoveUpdate(float Alpha)
{
	FVector Location = FMath::Lerp(GluedObject->GetActorTransform().GetLocation(),
	                               Target->GetComponentTransform().GetLocation(), Alpha);

	//TODO: Rotations should be picked for the closest angle 
	FRotator Rotation = UKismetMathLibrary::RLerp(FRotator(GluedObject->GetActorTransform().GetRotation()),
	                                              FRotator(Target->GetComponentTransform().GetRotation()), Alpha,
	                                              true);
	GluedObject->SetActorLocationAndRotation(Location, Rotation);
}

void AGlueTrigger::MoveFinished()
{
	GluedObject->EnablePhysics();
}

void AGlueTrigger::BeginPlay()
{
	Super::BeginPlay();
	if (!GluedObjectClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Please specify Glued item Class in GlueTrigger with name %s"), *GetName());
	}
	if (!FloatCurve)
	{
		UE_LOG(LogTemp, Error, TEXT("Please specify FloatCurve in GlueTrigger with name %s"), *GetName());
	}

	FOnTimelineFloat ProgressUpdate;
	ProgressUpdate.BindUFunction(this, TEXT("MoveUpdate"));

	FOnTimelineEvent ProgressFinished;
	ProgressFinished.BindUFunction(this, TEXT("MoveFinished"));

	Timeline.AddInterpFloat(FloatCurve, ProgressUpdate);
	Timeline.SetTimelineFinishedFunc(ProgressFinished);
}

void AGlueTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timeline.TickTimeline(DeltaTime);

	if (!GluedObject.IsValid())
	{
		GluedObject = GetOverlappingObject();
	}

	if (GluedObject.IsValid())
	{
		if (!IsGlued)
		{
			GluedObject->DisablePhysics();
			IsGlued = true;
			Timeline.PlayFromStart();
		}

		if (GluedObject->Tags.Contains(GrabbedTag))
		{
			IsGlued = false;
			GluedObject.Reset();
		}
	}
}

TSoftObjectPtr<ABaseInteractable> AGlueTrigger::GetOverlappingObject()
{
	if (!GluedObjectClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Please specify Glued item Class in GlueTrigger with name %s"), *GetName());
		return {};
	}

	TArray<AActor*> Actors;
	TriggerBox->GetOverlappingActors(Actors, GluedObjectClass);

	if (Actors.IsEmpty())
	{
		return {};
	}

	for (const auto Actor : Actors)
	{
		if (!Actor->Tags.Contains(GrabbedTag))
		{
			return TSoftObjectPtr<ABaseInteractable> { Cast<ABaseInteractable>(Actor) };
		}
	}
	return {};
}

void AGlueTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
}

void AGlueTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
