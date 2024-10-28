// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterScanner.generated.h"

UCLASS()
class CRYPTRAIDER_API AMonsterScanner : public AActor
{
	GENERATED_BODY()

public:
	AMonsterScanner();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Enable();
	void Disable();

private:
	UFUNCTION()
	void PerformScan();

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

	// TODO Create monitor Scanner UserWidget
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UWidgetComponent> Monitor;

	UPROPERTY()
	TSubclassOf<class UScannerWidget> MonitorWidgetClass;
	
	UPROPERTY(EditAnywhere, Category="Properties", meta=(AllowPrivateAccess = "true"))
	float MaxScanDistance;

	UPROPERTY(EditAnywhere, Category="Properties", meta=(AllowPrivateAccess = "true"))
	float FieldOfView;

	UPROPERTY(EditAnywhere, Category="Properties", meta=(AllowPrivateAccess = "true"))
	float ScanRate;

	UPROPERTY()
	bool bIsActive;

	FTimerHandle ScanTimerHandle;
};
