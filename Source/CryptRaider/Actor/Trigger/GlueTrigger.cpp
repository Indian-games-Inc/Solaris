#include "GlueTrigger.h"

#include "../../Interface/BaseInteractable.h"
#include "Components/BoxComponent.h"
#include "CryptRaider/Player/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


AGlueTrigger::AGlueTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;

	Target = CreateDefaultSubobject<UStaticMeshComponent>(FName("Target"));
	Target->SetupAttachment(RootComponent);
	LadderBox = CreateDefaultSubobject<UBoxComponent>(FName("Ladder Box"));
	LadderBox->ShapeColor = FColor(0, 0, 255);
	LadderBox->SetupAttachment(RootComponent);

	LadderBox->SetGenerateOverlapEvents(true);

	FCollisionResponseContainer TriggerBoxCollisionResponses;
	TriggerBoxCollisionResponses.SetResponse(ECC_GameTraceChannel1, ECR_Overlap);
	TriggerBoxCollisionResponses.SetResponse(ECC_Pawn, ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannels(TriggerBoxCollisionResponses);

	FCollisionResponseContainer LadderBoxCollisionResponses;
	LadderBoxCollisionResponses.SetResponse(ECC_WorldDynamic, ECR_Ignore);
	LadderBoxCollisionResponses.SetResponse(ECC_Pawn, ECR_Overlap);
	LadderBox->SetCollisionResponseToChannels(LadderBoxCollisionResponses);
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

	// Register overlap events for MeshComponent
	LadderBox->OnComponentBeginOverlap.AddDynamic(this, &AGlueTrigger::OnBeginOverlap);
	LadderBox->OnComponentEndOverlap.AddDynamic(this, &AGlueTrigger::OnEndOverlap);
}

void AGlueTrigger::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	TriggerBox->SetVisibility(IsDebug);
	Target->SetVisibility(IsDebug);
	LadderBox->SetVisibility(IsDebug && IsClimbable);

	TriggerBox->SetHiddenInGame(!IsDebug);
	Target->SetHiddenInGame(!IsDebug);
	LadderBox->SetHiddenInGame(!(IsDebug && IsClimbable));
}

void AGlueTrigger::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);
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
			GluedObject = nullptr;
		}
	}
}

TSoftObjectPtr<ABaseInteractable> AGlueTrigger::GetOverlappingObject()
{
	if (!GluedObjectClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Please specify Glued item Class in GlueTrigger with name %s"), *GetName());
		return nullptr;
	}

	TArray<AActor*> Actors;
	TriggerBox->GetOverlappingActors(Actors, GluedObjectClass);

	if (Actors.IsEmpty())
	{
		return nullptr;
	}

	for (const auto& Actor : Actors)
	{
		if (!Actor->Tags.Contains(GrabbedTag))
		{
			return Cast<ABaseInteractable>(Actor);
		}
	}
	return nullptr;
}

void AGlueTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	if (IsClimbable)
	{
		if (auto* Character = Cast<ABaseCharacter>(OtherActor))
		{
			if (IsGlued)
			{
				Character->SetOnLadder(true);
			}
			else
			{
				Character->SetOnLadder(false);
				Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			}
		}
	}
}

void AGlueTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsClimbable)
	{
		if (auto* Character = Cast<ABaseCharacter>(OtherActor))
		{
			Character->SetOnLadder(false);
			Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		}
	}
	if (GluedObject.IsValid())
	{
		GluedObject->EnablePhysics();
	}
}
