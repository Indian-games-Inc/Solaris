#include "GlueTrigger.h"

#include "Item.h"
#include "Components/BoxComponent.h"
#include "CryptRaider/Character/BaseCharacter.h"
#include "CryptRaider/Component/Grabber.h"
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
	//HERE IS THE PLACE WHERE HOPE ENDS
	//THIS PIECE OF CODE RUINED ENTIRE LIVES OF LOTS OF PEOPLE
	//I'M NOT AN EXCEPTION
	//I'M BROKEN, BUT I STILL ALIVE
	//I LOST EVERYTHING BUT I WILL TRY AGAIN
	//FUCKING ROTATION
	//https://forums.unrealengine.com/t/smoothly-rotate-character-180-degrees/431976/3
	//https://forums.unrealengine.com/t/rotate-problem-beyond-180-180-degrees-spins-the-long-way-round/614505/2
	// FRotator NewRotation = FMath::RInterpTo(FRotator(GluedItem->GetActorTransform().GetRotation()),
	//                                         FRotator(Target->GetComponentTransform().GetRotation()), Alpha, 0.1);


	// // Perform spherical linear interpolation (SLERP) between the rotations
	// FQuat InterpolatedRotation = FQuat::Slerp(GluedItem->GetActorTransform().GetRotation(), Target->GetComponentTransform().GetRotation(), Alpha);
	//
	// // Convert the interpolated rotation to Euler angles if needed
	// FRotator InterpolatedRotator = InterpolatedRotation.Rotator();
	// auto current = GluedItem->GetActorTransform().GetRotation().Z;
	// auto target = Target->GetComponentTransform().GetRotation().Z;
	// auto angle = FMath::RInterpTo(FRotator(current), FRotator(target), Alpha, 0.1);

	//FMath::RInterpTo
	// GluedItem->SetActorLocation(NewTransform);

	// auto rot = FMath::RInterpTo(GluedItem->GetActorRotation(), Target->GetComponentRotation(), Alpha, 0.1);
	FVector Location = FMath::Lerp(GluedItem->GetActorTransform().GetLocation(),
	                               Target->GetComponentTransform().GetLocation(), Alpha);
	FRotator Rotation = UKismetMathLibrary::RLerp(FRotator(GluedItem->GetActorTransform().GetRotation()),
	                                              FRotator(Target->GetComponentTransform().GetRotation()), Alpha,
	                                              true);
	GluedItem->SetActorLocationAndRotation(Location, Rotation);
}

void AGlueTrigger::MoveFinished()
{
	GluedItem->GetBody()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GluedItem->GetBody()->OnActorEnableCollisionChanged();
}

void AGlueTrigger::BeginPlay()
{
	Super::BeginPlay();
	Grabber = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter())->GetGrabber();

	if (!ItemClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Please specify Glued item Class in GlueTrigger with name %s"), *GetName());
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
	TriggerBox->SetVisibility(IsDebug, false);
	Target->SetVisibility(IsDebug, false);
	LadderBox->SetVisibility(IsDebug && IsClimbable, false);

	TriggerBox->SetHiddenInGame(!IsDebug, false);
	Target->SetHiddenInGame(!IsDebug, false);
	LadderBox->SetHiddenInGame(!(IsDebug && IsClimbable), false);
}

void AGlueTrigger::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);
	Timeline.TickTimeline(DeltaTime);

	if (Grabber->IsGrabbing())
	{
		IsGlued = false;
		Timeline.Stop();
	}
	else
	{
		SelectOverlappingItem();
		if (!IsGlued && GluedItem)
		{
			GluedItem->GetBody()->SetSimulatePhysics(false);
			GluedItem->GetBody()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			IsGlued = true;
			Timeline.PlayFromStart();
		}
	}
}

void AGlueTrigger::SelectOverlappingItem()
{
	TArray<AActor*> Actors;
	TriggerBox->GetOverlappingActors(Actors, ItemClass);
	if (Actors.IsEmpty())
	{
		if (!IsGlued)
		{
			GluedItem = nullptr;
		}
	}
	else
	{
		GluedItem = Cast<AItem>(Actors[0]);
	}
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
			GluedItem->GetBody()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
		GluedItem->GetBody()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}
