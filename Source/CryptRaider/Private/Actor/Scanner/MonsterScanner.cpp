// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Scanner/MonsterScanner.h"

#include "Components/WidgetComponent.h"
#include "Actor/Scanner/ScannerWidget.h"
#include "AI/Common/BaseAICharacter.h"
#include "Kismet/GameplayStatics.h"


AMonsterScanner::AMonsterScanner()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Scanner Body");
	SetRootComponent(Mesh);

	Monitor = CreateDefaultSubobject<UWidgetComponent>("Scanner Monitor");
	Monitor->SetupAttachment(RootComponent);
	Monitor->SetWidgetClass(MonitorWidgetClass);

	MaxScanDistance = 10.f * 100.f; // 10 meters
	FieldOfView = 180.f;
}

void AMonsterScanner::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterScanner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PerformScan();
}

void AMonsterScanner::Enable()
{
	GetWorld()->GetTimerManager().SetTimer(ScanTimerHandle,
	                                       this, &AMonsterScanner::PerformScan,
	                                       ScanRate, true);
}

void AMonsterScanner::Disable()
{
	GetWorld()->GetTimerManager().ClearTimer(ScanTimerHandle);
}

void AMonsterScanner::PerformScan()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, ABaseAICharacter::StaticClass(), FoundActors);

	if (FoundActors.IsEmpty())
	{
		return;
	}

	const auto* Monster = FoundActors[0];
	const auto* Player = UGameplayStatics::GetPlayerCharacter(this, 0);

	const float DistanceToMonster = FVector::Distance(Monster->GetActorLocation(),
	                                                  Player->GetActorLocation());

	if (DistanceToMonster > MaxScanDistance)
		return;

	const FVector MonsterDirection = Monster->GetActorLocation() - Player->GetActorLocation();

	FVector2D RelativeLocation {
		FVector::DotProduct(MonsterDirection, Player->GetActorRightVector()),
		FVector::DotProduct(MonsterDirection, Player->GetActorForwardVector())
	};
	
	RelativeLocation = RelativeLocation.GetSafeNormal();
	RelativeLocation /= MaxScanDistance / DistanceToMonster;

	if (auto* MonitorWidget = Cast<UScannerWidget>(Monitor->GetWidget());
		IsValid(MonitorWidget))
	{
		MonitorWidget->ScanUpdate(RelativeLocation);
	}
}
