#include "GlueTrigger.h"

#include "../../Interface/BaseInteractable.h"
#include "Components/BoxComponent.h"
#include "CryptRaider/Player/BaseCharacter.h"
#include "CryptRaider/Player/BasePlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


AGlueTrigger::AGlueTrigger()
{
	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Box"));
	TriggerBox->SetupAttachment(RootComponent);
	Target = CreateDefaultSubobject<UStaticMeshComponent>(FName("Target"));
	Target->SetupAttachment(RootComponent);
	LadderBox = CreateDefaultSubobject<UBoxComponent>(FName("Ladder Box"));
	LadderBox->ShapeColor = FColor(0, 0, 255);
	LadderBox->SetupAttachment(RootComponent);

	TriggerBox->SetGenerateOverlapEvents(true);
	LadderBox->SetGenerateOverlapEvents(true);

	FCollisionResponseContainer TriggerBoxCollisionResponses;
	TriggerBoxCollisionResponses.SetResponse(ECC_GameTraceChannel1, ECR_Overlap);
	TriggerBoxCollisionResponses.SetResponse(ECC_Pawn, ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannels(TriggerBoxCollisionResponses);

	FCollisionResponseContainer LadderBoxCollisionResponses;
	LadderBoxCollisionResponses.SetResponse(ECC_WorldDynamic, ECR_Ignore);
	LadderBoxCollisionResponses.SetResponse(ECC_Pawn, ECR_Overlap);
	LadderBox->SetCollisionResponseToChannels(LadderBoxCollisionResponses);


	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;
}

void AGlueTrigger::MoveUpdate(float Alpha)
{
	FVector Location = FMath::Lerp(GluedItem->GetActorTransform().GetLocation(),
	                               Target->GetComponentTransform().GetLocation(), Alpha);

	//TODO: Rotations should be picked for the closest angle 
	FRotator Rotation = UKismetMathLibrary::RLerp(FRotator(GluedItem->GetActorTransform().GetRotation()),
	                                              FRotator(Target->GetComponentTransform().GetRotation()), Alpha,
	                                              true);
	GluedItem->SetActorLocationAndRotation(Location, Rotation);
}

void AGlueTrigger::MoveFinished()
{
	GluedItem->EnablePhysics();
}

void AGlueTrigger::BeginPlay()
{
	Super::BeginPlay();
	if (!ItemClass)
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
	LadderBox->OnComponentBeginOverlap.AddDynamic(this, &AGlueTrigger::OnLadderComponentBeginOverlap);
	LadderBox->OnComponentEndOverlap.AddDynamic(this, &AGlueTrigger::OnLadderComponentEndOverlap);
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

	if (!GluedItem)
	{
		GluedItem = SelectOverlappingItems();
	}

	if (GluedItem)
	{
		if (!IsGlued)
		{
			GluedItem->DisablePhysics();
			IsGlued = true;
			Timeline.PlayFromStart();
		}

		if (GluedItem->Tags.Contains(GrabbedTag))
		{
			IsGlued = false;
			GluedItem = nullptr;
		}
	}
}

ABaseInteractable* AGlueTrigger::SelectOverlappingItems()
{
	if (!ItemClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Please specify Glued item Class in GlueTrigger with name %s"), *GetName());
		return nullptr;
	}

	TArray<AActor*> Actors;
	TriggerBox->GetOverlappingActors(Actors, ItemClass);

	if (Actors.IsEmpty())
	{
		return nullptr;
	}

	for (auto Actor : Actors)
	{
		if (!Actor->Tags.Contains(GrabbedTag))
		{
			return Cast<ABaseInteractable>(Actor);
		}
	}
	return nullptr;
}

void AGlueTrigger::OnLadderComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                 const FHitResult& SweepResult)
{
	if (IsClimbable)
	{
		auto* Character = Cast<ABaseCharacter>(OtherActor);
		if (IsGlued)
		{
			Character->SetOnLadder(true);
			// GluedItem->DisablePhysics();
		}
		else
		{
			Character->SetOnLadder(false);
			Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		}
	}
}

void AGlueTrigger::OnLadderComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsClimbable)
	{
		auto* Character = Cast<ABaseCharacter>(OtherActor);
		Character->SetOnLadder(false);
		Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		if (GluedItem)
		{
			GluedItem->EnablePhysics();
		}
	}
}
