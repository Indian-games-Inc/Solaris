// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Scanner/MonsterScanner.h"

#include "Components/WidgetComponent.h"
#include "UI/Widgets/ScannerWidget.h"
#include "AI/Common/BaseAICharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


AMonsterScanner::AMonsterScanner()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Scanner Body");
	SetRootComponent(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);

	Monitor = CreateDefaultSubobject<UWidgetComponent>("Scanner Monitor");
	Monitor->SetupAttachment(RootComponent);
	Monitor->SetWidgetClass(MonitorWidgetClass);

	Monitor->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Monitor->SetCollisionResponseToAllChannels(ECR_Ignore);

	MaxScanDistance = 10.f * 100.f; // 10 meters
	FieldOfView = 180.f;

	ScanRate = 1.5f;
}

void AMonsterScanner::BeginPlay()
{
	Super::BeginPlay();

	if (auto* ScannerWidget = Cast<UScannerWidget>(Monitor->GetWidget()))
	{
		ScannerWidget->SetDrawSize(Monitor->GetDrawSize());
	}

	Enable();
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

void AMonsterScanner::PerformScan() const
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, ABaseAICharacter::StaticClass(), FoundActors);

	if (FoundActors.IsEmpty())
		return;

	const auto* Monster = FoundActors[0];
	const auto* Player = UGameplayStatics::GetPlayerCharacter(this, 0);

	if (not IsValid(Monster) or not IsValid(Player))
		return;

	const float DistanceToMonster = FVector::Distance(Player->GetActorLocation(), Monster->GetActorLocation());

	if (DistanceToMonster > MaxScanDistance)
		return;

	const FVector MonsterDirection = Monster->GetActorLocation() - Player->GetActorLocation();

	if (not InFieldOfView(Player->GetActorForwardVector(), MonsterDirection))
		return;

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

bool AMonsterScanner::InFieldOfView(const FVector& ForwardVector, const FVector& Direction) const
{
	if (const auto Rotation = UKismetMathLibrary::Quat_FindBetweenVectors(ForwardVector, Direction).Rotator();
		FMath::Abs(Rotation.Yaw) > FieldOfView / 2.f)
	{
		return false;
	}

	return true;
}
