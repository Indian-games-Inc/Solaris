// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CryptRaider/Data/DialogRow.h"
#include "GameFramework/Actor.h"
#include "DialogTrigger.generated.h"

UCLASS()
class CRYPTRAIDER_API ADialogTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADialogTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Dialog Trigger")
	FDataTableRowHandle DialogRow;

	/*If option checked, the trigger would produce sub only once*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite,
		Category="Dialog Trigger|Repeatable")
	bool IsPlayedOnce = true;
	/*If option checked, the trigger would produce sub every Play Back Cooldown (seconds) and will pick it from Dialog Row list, Dialog Row will be ignored*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite,
		Category="Dialog Trigger|Repeatable")
	bool IsRandomPicked;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite,
		Category="Dialog Trigger|Repeatable")
	float PlayBackCooldown;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite,
		Category="Dialog Trigger|Repeatable")
	TArray<FDataTableRowHandle> DialogRowList = {};

private:
	UPROPERTY()
	USceneComponent* Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* TriggerBox;
};
